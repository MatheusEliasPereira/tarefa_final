#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

#define N 50
#define a 2
#define b 4

typedef double (*sistfunc)();

double z0(double y[], double t)
{	return y[1];
}

double z1(double y[], double t)
{	return (-2.0/t)*z0(y,t) + 0*y[0];
}

double z2(double y[], double t)
{	return z1(y,t) - 0*t;
}

double *multiplica(double u[], double h)
{	int i;
	double *v;
	
	v = (double*)malloc(2*sizeof(double));
	
	for(i=0;i<=1;i++)
		v[i] = u[i]*h;
	
	return v;
}
		
double *soma(double y[], double u[], double h)
{	int i;
	double *g, *r;
	
	g = (double*)malloc(2*sizeof(double));
	r = (double*)malloc(2*sizeof(double));
	
	r = multiplica(u,h);
	
	for(i=0;i<=1;i++)
		g[i] = y[i]+r[i];
		
	return g;
}

double rungekutta(sistfunc equacoes[], double y[], double t)
{	int i = 0;
	double k1[2], k2[2], k3[2], k4[2], h = (b-a)/(double)N;
	
	
	
	for(i=0;i<=1;i++)
		k1[i] = equacoes[i](y,t);
	
	for(i=0;i<=1;i++)
		k2[i] = equacoes[i](soma(y,k1,h/2.0),t + h/2.0);
	
	for(i=0;i<=1;i++)
		k3[i] = equacoes[i](soma(y,k2,h/2.0),t + h/2.0);
	
	for(i=0;i<=1;i++)
		k4[i] = equacoes[i](soma(y,k3,h),t + h);
		

	
	for(i=0;i<=1;i++)
	{	y[i] = y[i] + h*(k1[i] + 2*k2[i] + 2*k3[i] + k4[i])/6.0;
		printf("\nk1[%d] = %lf\tk2[%d] = %lf\tk3[%d] = %lf\tk4[%d] = %lf\n", i,k1[i],i, k2[i],i, k3[i],i, k4[i]);
	}
	
	return y[0];
}

void main()
{	sistfunc equacoes1[] = {z0,z1}, equacoes2[] = {z0,z2};
	double y1[] = {110,0}, y2[] = {0,1}, t = a, h = (b-a)/(double)N, beta = 0, solucao1[N], solucao2[N], solucao_geral[N];
	int i = 0;
	FILE *p;
	
	do{
		solucao1[i] = rungekutta(equacoes1, y1, t);
		solucao2[i] = rungekutta(equacoes2, y2, t);
		printf("\nSolução1[%d]: %lf\tSolução2[%d]: %lf\n", i, solucao1[i], i, solucao2[i]);
		i++;
		t+=h;
	}while(t<=b);
	
	for(i=0;i<N;i++)
		solucao_geral[i] = solucao1[i] + solucao2[i]*(beta - solucao1[N-1])/(double)solucao2[N-1];
	
	p = fopen("dados_11.1_7.dat", "w");
	t = a;
	for(i=0;i<N;i++)
	{	fprintf(p, "%d\t%lf\t%lf\t%lf\t%lf\n", i, t, solucao1[i], solucao2[i], solucao_geral[i]);
		t+=h;
	}
	fclose(p);
}
