#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <time.h>

int main(){
	int j,k;
	int a=0;
	int b=1;
	double PI = acos(-1.0);
	int i, j, fila, columna,n,m;
	//fila=10000;
	//columna=10000;
	double *xx, *tt;
	double **T=NULL;
	/*double **P=NULL;
	double **N=NULL;*/
	double **A=NULL;
	float dx,dt;
	float coef;
	
	/************************** Discretización    ****************************** */
	dx=0.01;   // Discretización en el espacio
	n=1/dx;	 // n+1 es la cantidad de elementos en el array x
	
	dt=0.001;
	m=1/dt;
	
	coef = dt*n*n
	
	
	/* the pointers are inizilized */
	xx = NULL;
	tt = NULL;
	T = NULL;
	/*N = NULL;
	P = NULL;*/
	A = NULL;


	T = (double * *) malloc((n+1)*sizeof(double) );
	if(T == NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	for(j=0;j<n+1;i++){
		T[j]=(double *) malloc((m+1)*sizeof(double))
		if(T[j]==NULL){
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}
	
	q = (double * *) malloc((n+1)*sizeof(double) );
	if(q == NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	for(j=0;j<n+1;i++){
		q[j]=(double *) malloc((m+1)*sizeof(double))
		if(q[j]==NULL){
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}	
	/*
	P = (double * *) malloc((n+1)*sizeof(double) );
	if(P == NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	for(j=0;j<n+1;i++){
		P[j]=(double *) malloc((n+1)*sizeof(double))
		if(P[j]==NULL){
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}
	
	N = (double * *) malloc((n+1)*sizeof(double) );
	if(N == NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	for(j=0;j<n+1;i++){
		N[j]=(double *) malloc((n+1)*sizeof(double))
		if(N[j]==NULL){
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}
	*/
	A = (double * *) malloc((n+1)*sizeof(double) );
	if(A == NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	for(j=0;j<n+1;i++){
		A[j]=(double *) malloc((n+1)*sizeof(double))
		if(A[j]==NULL){
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}	
	/* Allocating memory space for the arrays */
	xx = (double *) malloc((size_t) (n+1) * sizeof(double) );
	tt = (double *) malloc((size_t) (m+1) * sizeof(double) );
	

	for(j=1;j<n;j++){
		xx[j] = j*dx;
		T[j][0] = exp(xx[j]);
	}
	for(k=0;k<=m;k++){
		tt[k] = k*dt;
		T[0][k] = 0;
		T[n][k] = 0;
	}
	for(j=0;j<=n;j++){
		for(k=0;k<=m;k++){
			q[j][k]=cos(PI*tt[k])*sin(PI*xx[j]);
		}
		A[j][j]= 1+2*coef
		//N[j][j] = 1+2*coef
	}
	for(j=0;j<n;j++){
		A[j][j+1]= -coef
		A[j+1][j]= -coef
		//N[j][j+1]= -coef
		//P[j+1][j]= coef
	}
	
	
	//printf("%f" % q);
}

