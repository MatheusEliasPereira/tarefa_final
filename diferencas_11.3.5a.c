#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define N 9
#define a 0.0
#define b 1.0
double y_i(double x)
{	return 1.0;
}

double y_f(double x)
{	return exp(-10.0);
}

double q(double x)
{	return 100.0;
}

double p(double x)
{	return 0.0;
}

double r(double x)
{	return 0.0; 
}

void imprime(double **A, int diml, int dimc)
{	int i, j;
	
	for(i=0;i<diml;i++)
	{	for(j=0;j<dimc;j++)
			printf("%.4lf\t",A[i][j]);
	  
		puts("");
	}
	printf("\n------------------\n");	
}

void troca(double *c, double *d, int dimc)
{	double aux;
	int i;
	
	for(i=0;i<dimc;i++)
	{	aux = c[i];
		c[i] = d[i];
		d[i] = aux;
	}
}

double **cria(double h, double x) //x0 = a+h
{	double **R, e1, e2, e3;
	int i, j;

	R = (double**)malloc(N*sizeof(double*));

	for(i=0;i<N;i++)
		R[i] = (double*)malloc((N+1)*sizeof(double));
	
	for(i=0;i<N;i++)
		for(j=0;j<(N+1);j++)
			R[i][j] = 0;
			
	R[0][N] = -1*pow(h,2)*r(x) + (1 + (h/2.0)*p(x))*y_i(a);
	
	x+=h; //pois o loop começa em x = 1, então devemos incrementar manualmente da primeira vez
	
	for(i=1;i<(N-1);i++)
	{	e1 =  -1 - (h/2.0)*p(x);
		e2 = 2 + pow(h,2)*q(x);
		e3 = -1 + (h/2.0)*p(x);
		
		R[i][N] = -1*pow(h,2)*r(x);

		for(j=1;j<(N+1);j++)
		{	if(i==j)
			{	R[i][i] = e2;
				R[i][i-1] = e1;
				R[i][i+1] = e3;
				
			}	
		}
		x+=h;
	}
	
	R[0][0] = e2;
	R[0][1] = e3;
	R[i][i] = e2;
	R[i][i-1] = e1;
	R[i][N] = -1*pow(h,2)*r(x) + (1 - (h/2.0)*p(x))*y_f(b);
	
	return R;
}

double **copia(double **M, int diml, int dimc)
{	double **U;
	int i, j;
	
	U = (double**)malloc(diml*sizeof(double*));
	for(i=0;i<diml;i++)
		U[i] = (double*)malloc((dimc)*sizeof(double));
	
	for(i=0;i<diml;i++)
		for(j=0;j<dimc;j++)
			U[i][j] = M[i][j]; //copia matriz
	
	return U;
}

double **triangula(double **M, int diml, int dimc, int *cont)
{
 	int i, j, k, h, p = -1;
 	double aux;
 	
 	for(k=0;k<diml;k++) // função que faz triangular superior
 	{	for(h=k;h<diml;h++)
 			if(M[k][k]<fabs(M[h][k]))
				p = h;
 		
 		if(p!=-1)
		{	troca(M[k],M[p],dimc);
 			puts("Matriz trocada");
 			imprime(M,diml,dimc);
 			*cont++;
		}
	 	
	 	p = -1;
 		
 		for(i=k+1;i<diml;i++)
 		{	
 			aux = (M[i][k]/M[k][k]);
 
 			for(j=k;j<=dimc;j++)
 				M[i][j] = M[i][j] - aux*M[k][j];
 		}
 		
 		printf("\nPasso %d\n", k+1);
 		imprime(M,diml,dimc);	
 	}
		
	return M;
}

void substituicao(double **M, double *raizes, int diml)
{	int i, j;
	double d[diml], soma[diml], aux;
	
	for(i=diml-1;i>=0;i--)
	{	soma[i] = 0;
	
		for(j=i;j<=diml;j++)
			soma[i] = soma[i] + M[i][j-1]*raizes[j-1];
		
		aux = M[i][diml];
		d[i] = aux - soma[i];
		raizes[i] = (double)d[i]/M[i][i];
		
		//printf("\nRaizes[%d] = %lf\n", i+1, raizes[i]);
	}
}

void main()
{
	double **M, **I, **T, **C, *X, h = (b-a)/(double)(N+1), s = a;
	int i, j, diml = N, dimc = N+1, cont = 0;
	FILE *p;
	
	M = cria(h,a+h);
	printf("\nMatriz lida:\n");
	imprime(M,diml,dimc);
	
	C = copia(M,diml,dimc);
	
	M = triangula(M,diml,dimc,&cont);
	printf("\n==========ESCALONAMENTO==========:\n");
	imprime(M,diml,dimc);
	
	printf("\n==========SOLUÇÃO PELO MÉTODO DA ELIMINAÇÃO DE GAUSS COM PIVOTAMENTO PARCIAL=========\n\n");
			
	X = (double*)malloc(diml*sizeof(double));
	*X = 0;
	substituicao(M,X,diml);
	
	p = fopen("dados_11.3_5a.dat", "w+");
	
	printf("\n%lf\t%lf\n",s, y_i(a));
	fprintf(p,"\n%lf\t%lf\n",s, y_i(a));
	
	for(i=0;i<diml;i++)
	{	printf("\n%lf\t%lf\n", s+h, X[i]);
		fprintf(p,"\n%lf\t%lf\n", s+h, X[i]);
		s+=h;
	}
	
	printf("\n%lf\t%lf\n",s+h, y_f(b));
	fprintf(p,"\n%lf\t%lf\n",s+h, y_f(b));
	
	fclose(p);	
	free(X);
	
	return;
}
