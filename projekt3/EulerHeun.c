#include <stdio.h>
#include <math.h>

double *X;
double *YE;
double *YH;
double *R;
double *BE;
double *BH;

double f(double x, double y)
{
	double w;
	w=y-x-sin(x)+cos(x)+1;
	return w;
}

double r(double x)
{
	return x+pow(2.71828183,x)+sin(x);
}

int main()
{
	double b;
	double h;
	double N;
	
	double x;
	double y;
	
	printf("Podaj b:\n");
	scanf("%lf",&b);
	printf("Podaj h:\n");
	scanf("%lf",&h);
	N=b/h;
	X=(double*)malloc((N+1)*sizeof(*X));
	YE=(double*)malloc((N+1)*sizeof(*YE));
	YH=(double*)malloc((N+1)*sizeof(*YH));
	R=(double*)malloc((N+1)*sizeof(*R));
	BE=(double*)malloc((N+1)*sizeof(*BE));
	BH=(double*)malloc((N+1)*sizeof(*BH));
	
	int i;
	FILE *fp;
	fp=fopen("EH.txt", "w");
	
	fprintf(fp,"Wartosci X:\n");
	for(i=0;i<N;i++)
	{
		X[i]=i*h;
		fprintf(fp,"%lf\n",X[i]);
	}
	X[i]=b;
	fprintf(fp,"%lf\n",X[i]);
	fprintf(fp,"\n");
	
	fprintf(fp,"Wyniki metody Eulera:\n");
	YE[0]=1;
	fprintf(fp,"%lf\n",YE[0]);
	for(i=1;i<=N;i++)
	{
		x=X[i-1];
		y=YE[i-1];
		YE[i]=y+h*f(x,y);
		fprintf(fp,"%lf\n",YE[i]);
	}
	fprintf(fp,"\n");
	
	fprintf(fp,"Wyniki metody Heuna:\n");
	YH[0]=1;
	fprintf(fp,"%lf\n",YH[0]);
	for(i=1;i<=N;i++)
	{
		x=X[i-1];
		y=YH[i-1];
		YH[i]=y+(h/2)*( f(x,y)+f(x+h,y+h*f(x,y)) );
		fprintf(fp,"%lf\n",YH[i]);
	}
	fprintf(fp,"\n");
	
	fprintf(fp,"Rozwiazanie:\n");
	for(i=0;i<=N;i++)
	{
		R[i]=r(X[i]);
		fprintf(fp,"%lf\n",R[i]);
	}
	fprintf(fp,"\n");
	
	fprintf(fp,"Blad bezwzgledny metody Eulera:\n");
	for(i=0;i<=N;i++)
	{
		BE[i]=fabs(R[i]-YE[i]);
		fprintf(fp,"%lf\n",BE[i]);
	}
	fprintf(fp,"\n");
	
	fprintf(fp,"Blad bezwzgledny metody Heuna:\n");
	for(i=0;i<=N;i++)
	{
		BH[i]=fabs(R[i]-YH[i]);
		fprintf(fp,"%lf\n",BH[i]);
	}
	fprintf(fp,"\n");
	
	fclose (fp);
	
	
	return 0;
}
