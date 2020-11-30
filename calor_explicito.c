#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <time.h>


void arreglo(double *vector, double dx);


int main(){
	int i,j,k,n,m;
	double dx,dt,nu;
	double *vector_x, *vector_t;
	double **U;
	
	/************************** Discretizaci�n    ****************************** */
	dx=0.01;   // Discretizaci�n en el espacio
	n=1/dx;	 // n+1 es la cantidad de elementos en el array x
	
	
	//para convergencia debe darse que dt/dx^2 <=1/2 (en el expl�cito)
	//dt/(0.01)^2 <=0.5 ----> dt<=0.00005 
	
	dt=0.00005; //tenemos que poner n�meros menores que 0.00005
	m=1/dt;

	/****************Espacio para los vectores que tienen la discretizaci�n de x y t********************/
	vector_x = (double*)malloc((n+1)*sizeof(double)); //Asignar el tama�o del vector
	vector_t = (double*)malloc((m+1)*sizeof(double)); //Asignar el tama�o del vector
	
	//LLenamos los vectores X y T, discretizando el espacio con su respectivo dx y dt
	arreglo(vector_x,dx);
	arreglo(vector_t,dt);
	
	//Espacio en memoria para la matriz U, la cual tendr� la soluci�n num�rica
	U=(double**)calloc((n+1),sizeof(double*));
	if(U==NULL){
		printf("No se ha podido reservar espacio de memoria.\n");
		exit(1);
	}
	
	for(i=0;i<n+1;i++){
		U[i]=(double*)calloc((m+1),sizeof(double));
		if(U==NULL){
		printf("No se ha podido reservar espacio de memoria.\n");
		exit(1);
		}
	}
	
	
	//Condici�n inicial
	double x;
	for(i=0;i<n+1;i++){
		x=vector_x[i];
		U[i][0]=exp(x); //Condici�n inicial es U_0(x)=exp(x)
		//printf("U[%i][0]=%f\n ",i,U[i][0]);
	}
	
	//Condici�n de estabilidad para el m�todo expl�cito
	nu=dt/(dx*dx);	//En el m�todo expl�cito se nos pide que nu<=1/2 para que haya estabilidad
	
	
	//LLenado de la matriz soluci�n siguiendo el esquema num�rico de diferencias finitas expl�cito
	for(j=0;j<m;j++){
		
   		for(i=1;i<n;i++){
   			U[i][j+1]=nu*(U[i+1][j]+U[i-1][j])+(1-2*nu)*U[i][j]+dt*q(vector_x[i],vector_t[j]);
   		}
   	}
	
	
	/***************** Generamos el archivo datos_matriz en donde guardaremos la informaci�n para graficar *****************/
	FILE *fp= fopen ("datos_matriz.txt","w");
	if (fp == NULL){
    	printf("Error opening file!\n");
    	exit(1);
	}
	
	//Guardamos la informaci�n que queramos graficar
	int tiempo=0.1;  //Para ver la soluci�n num�rica en t=0.1
	int columna_graficar=20000*0.1; //debemos colocarnos en esta columna
   	for(i = 0; i <n+1;i++){
    	fprintf (fp,"%f %f",vector_x[i], U[i][columna_graficar]); //guardamos en el archivo tanto la discretizaci�n x, como la soluci�n num�rica...
    	fprintf(fp,"\n");                                         //...para un tiempo dado
   	}
 
   /* close the file*/  
   fclose (fp);    //cerramos el archivo
   return 0;
	
}


void arreglo(double *vector, double dx){
	int n=1/dx;
	int i;
	for(i=0;i<n+1;i++){
		*(vector+i)=i*dx; //es equivalente a poner vector[i] 
		printf("%f  ",*(vector+i));
	}
	printf("\n");
}

int q(double x, double t){
	double aux;

	aux=cos(atan(1)*4*t)*sin(2*atan(1)*4*x);   //funci�n q(x,t) propuesta en el deber
	return aux;
}

