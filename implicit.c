#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <time.h>
// implicit method
int main(){
	// start variables
	int i,j,k,n,m,d;
	int a=0;
	int b=1;
	int steps=10;
	double PI = acos(-1.0);
	double *xx, *tt, *bb, *NPx, *Nb;
	double **q=NULL;
	double **T=NULL;
	double **P=NULL;
	double **N=NULL;
	double **NP=NULL;
	//double **Nb=NULL;
	
	//double **A=NULL;
	float dx,dt,coef,op,up,u;
	
	/************************** Discretización    ****************************** */
	dx=0.01;   // Discretización del espacio
	n=1/dx;	 // n+1 es la cantidad de elementos en el array x
	
	dt=0.01; // Discretización del tiemppo
	m=1/dt;
	
	coef = dt*n*n;
	u = 1/(1+2*coef);
	
	
	/* the pointers are inizilized */
	xx = NULL; //space 
	tt = NULL; //time 
	NPx= NULL; 
	Nb= NULL; 
	T = NULL; //Numerical solution
	N = NULL; //
	P = NULL;
	NP = NULL;
	//A = NULL;

	
	/* Allocating memory space for the matrices */
	T = (double * *) calloc((n+1)*sizeof(double),(m+1)*sizeof(double));
	if(T == NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	/*for(j=0;j<n+1;i++){
		T[j]=(double *) calloc((m+1)*sizeof(double));
		if(T[j]==NULL){
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}*/
	
	q = (double * *) malloc((n+1)*sizeof(double) );
	if(q == NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	for(j=0;j<n+1;i++){
		q[j]=(double *) malloc((m+1)*sizeof(double));
		if(q[j]==NULL){
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}	
	/***** AQUI hay un error. Si tu dato es un apuntador a apuntadores, tu arreglo es de apuntadores *****/
	/** Seria P = (double * *) malloc((n)*sizeof(* double) );  **/
	P = (double * *) malloc((n)*sizeof(double) );
	if(P == NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	for(j=0;j<n;i++){
		P[j]=(double *) malloc((n)*sizeof(double));
		if(P[j]==NULL){
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}
	/****** LO MISMO AQUI *****/
	N = (double * *) malloc((n)*sizeof(double) );
	if(N == NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	for(j=0;j<n;i++){
		N[j]=(double *) malloc((n)*sizeof(double));
		if(N[j]==NULL){
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}
	
	NP = (double * *) malloc((n)*sizeof(double) );
	if(NP == NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	for(j=0;j<n;i++){
		NP[j]=(double *) malloc((n)*sizeof(double));
		if(NP[j]==NULL){
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}
	
	
	/* Allocating memory space for the arrays */
	xx = (double *) malloc((size_t) (n+1) * sizeof(double) );
	tt = (double *) malloc((size_t) (m+1) * sizeof(double) );
	bb = (double *) malloc((size_t) (n) * sizeof(double) );
	Nb = (double *) malloc((size_t) (n) * sizeof(double) );
	NPx = (double *) malloc((size_t) (n) * sizeof(double) );
	
	/* filling the arrays-matrices */
	for(j=0;j<=n;j++){
		xx[j] = j*dx;
		T[j][0] = exp(xx[j]);
	}
	for(k=0;k<=m;k++){
		tt[k] = k*dt;
	}
	for(j=0;j<=n;j++){
		for(k=0;k<=m;k++){
			q[j][k]=cos(PI*tt[k])*sin(PI*xx[j]);
		}
	}
	
	/* 
	to aproximate x=inv(A)b with Gauss Seidel, 
	we make A = N-P so 
	x_i+1 = inv(N)b+inv(N)P*x_i
	*/
	// fill the P lower triangular matrix
	for(j=0;j<n;j++){
		printf("%d %d",j+1,j);
		P[j+1][j]= coef;
	}
	
	// filling the N upper bidiagonal matrix
	op=u;
	for(d=0;d<n;d++){
		up=n-d;
		for(i=0;i<up;i++){
			//printf("%d %d",i,i+d);
			N[i][i+d]=op;
		}
		op*=coef;
	}
	
	//fill inv(N)*P // matrix product
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			NP[i][j]=0.0E+0;
			for(k=0;k<n;k++){
				NP[i][j]+=N[i][k]*P[k][j];
			}
		}
	}
	// start the numerical procedure Tk+1 = inv(A)*b
	for(k=0;k<n;k++){
		//fill the b vector 
		for(j=0;j<n;k++){
			bb[j] = T[j+1][k]+q[j+1][k+1]*dt;
		}
		//do the product inv(N)*b
		for(i=0;i<=n;i++){
			Nb[i]=0.0E+0;
			for(j=0;j<=n;j++){
				Nb[i]+=N[i][j]*bb[j];
			}
		}
		// start Gauss Seidel 
		for(i=0;i<=steps;i++){
			// i is the number of iterations
			//Calculate inv(N)PTk+1
			for(j=0;j<n;j++){
				NPx[j]=0.0E+0;
				for(i=0;i<=n;i++){
					NPx[j]+=NP[j][i]*T[j+1][k+1];
				}
			}
			//save Tk+1_i= inv(N)b+inv(N)PTk+1
			for(j=0;j<=n;j++){
				T[j][k+1]=Nb[j]+NPx[j];
			}
		}
	}
	/* EXPORT DATA */
	FILE *fp= fopen("datos_matriz.txt","w");
	if(fp==NULL){
		printf("ERROR OPENING FILE!\n");
		exit(1);
	}
	for(i=0;i<=n;i++){
		fprintf(fp,"%f %f \n",xx[i],T[i][m/2]);
	}
	fclose(fp);
	return 0;
}

