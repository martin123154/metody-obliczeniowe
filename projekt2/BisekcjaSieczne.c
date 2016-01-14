#include <stdio.h>
#include <math.h>

double funkcja(double arg)
{
	double x=arg;
	if(x==0)
	{
		x=x+0.00000001;	
	}
	double w=0;
	w=693*(pow(x,6))-945*(pow(x,4))+315*(pow(x,2))-15;
	return w;
}

int main()
{
	double pA; 
	double pB;
	double epsilon;
	double srodek;
	
	printf("Metoda bisekcji\n");
	printf("Podaj dolna granice przedzialu\n");
	scanf("%lf", &pA);
	printf("Podaj gorna granice przedzialu\n");
	scanf("%lf", &pB);
	printf("Podaj dokladnosc\n");
	scanf("%lf", &epsilon);
	int LOB = 0;
	
	while( (fabs(pB-pA))>epsilon )
	{
		LOB++;
		srodek=(pA+pB)/2;
		printf("%lf\n", srodek);
		
		if( (funkcja(pA)*funkcja(srodek))<0 )
		{
			pB=srodek;
		}
		else if( (funkcja(pB)*funkcja(srodek))<0 )
		{
			pA=srodek;
		}
	}
	printf("%lf\n",(pA+pB)/2);
	printf("Ilosc iteracji przy metodzie bisekcji: %d\n", LOB);
	
	printf("Metoda siecznych\n");
	double Z=0.238619186083;
	double xm2;
	double xm1;
	double xn;
	int LOS = 0;
	
	printf("Podaj pierwsza wartosc poczatkowa\n");
	scanf("%lf", &xm2);
	printf("Podaj druga wartosc poczatkowa\n");
	scanf("%lf", &xm1);
	
	do
	{
		xn=( xm2*funkcja(xm1)-xm1*funkcja(xm2) )/ ( funkcja(xm1)-funkcja(xm2) );
		xm2=xm1;
		xm1=xn;
		printf("%lf\n",xn);
		LOS++;
	}
	while(fabs(xn-Z)>epsilon);
	printf("Ilosc iteracji przy metodzie siecznych: %d\n", LOS);
	
	return 0;
}
