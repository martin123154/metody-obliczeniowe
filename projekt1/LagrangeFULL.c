#include <stdio.h>
#include <math.h>

int potega;
float *tabwspf;
float tabwspft[4];

float przedzialA;
float przedzialB;
int iloscP;

float *tabX;
float *tabY;

typedef struct wielomian
{
	float *wsp;//tablica wspolczynnikow
	int D;//dlugosc
} W;

W *tabL;

W mnoz(W x, W y)
{
	int i,j;
	
	W zwrot;
	zwrot.D=x.D+y.D;
	zwrot.wsp=(float*)malloc( (zwrot.D+1)*sizeof(float));
	
	for (i=0;i<=zwrot.D;i++)//zerowanie wspolczynnikow wielomianu
	{
		zwrot.wsp[i]=0;
	}
	for (i=0;i<=x.D;i++)
	{
		for(j=0;j<=y.D;j++)
		{
			zwrot.wsp[i+j]=zwrot.wsp[i+j]+x.wsp[i]*y.wsp[j];
		}
	}
	
	return zwrot;
}

W dod(W x, W y)
{
	W zwrot;
	if(x.D>=y.D)
	{
		zwrot=x;
	}
	else
	{
		zwrot=y;
	}
	
	int i, g;
	if(x.D>=y.D)
	{
		g=y.D;
	}
	else
	{
		g=x.D;
	}	
	
	for (i=0;i<=g;i++)
	{
		zwrot.wsp[i]=x.wsp[i]+y.wsp[i];
	}
	
	return zwrot;
}

float pot(float b, float p)
{
	float w=1;
	int i;
	for(i=0;i<p;i++)
	{
		w=w*b;
	}
	return w;
}

int main()
{
	int i;
	int j;
	float w;

	
	//Wprowadzanie funkcji
	tabwspft[0]=0;
	tabwspft[1]=0;
	tabwspft[2]=0;
	tabwspft[3]=0;
	
	printf("Wprowadz funkcje. Jaka bedzie najwyzsza potega?\n");
	scanf("%d", &potega);
	tabwspf=(float*)malloc(potega*sizeof(float));
	for (i=0;i<=potega;i++)
	{
		printf("Podaj wspolczynnik przy potedze %d\n",i);
		scanf("%f", &w);
		tabwspf[i]=w;
	}
	printf("Czy chcesz uzyc trygonometrii? (1-tak/0-nie)\n");
	int odp;
	scanf("%d",&odp);
	if (odp==1)
	{
		printf("Wprowadz wspolczynnik przy sin(x)\n");
		scanf("%f", &w);
		tabwspft[0]=w;
		
		printf("Wprowadz wspolczynnik przy cos(x)\n");
		scanf("%f", &w);
		tabwspft[1]=w;
		
		printf("Wprowadz wspolczynnik przy tg(x)\n");
		scanf("%f", &w);
		tabwspft[2]=w;
		
		printf("Wprowadz wspolczynnik przy ctg(x)\n");
		scanf("%f", &w);
		tabwspft[3]=w;
	}
		
	//END
	
	//Wprowadzanie przedzialu i ilosci punktow
	printf("Wprowadz dolna granice przedzialu\n");
	scanf("%f", &w);
	przedzialA=w;
	printf("Wprowadz gorna granice przedzialu\n");
	scanf("%f", &w);
	while(w<=przedzialA)
	{
		printf("Za mala gorna granica! Wprowadz jeszcze raz\n");
		scanf("%f", &w);
	}
	przedzialB=w;
	printf("Wprowadz ilosc punktow do interpolacji\n");
	scanf("%d", &iloscP);
	//END
	
	//Ustalanie argumentow i wartosci funkcji
	tabX=(float*)malloc(iloscP*sizeof(float));
	tabY=(float*)malloc(iloscP*sizeof(float));	
	
	tabX[0]=przedzialA;
	tabX[iloscP-1]=przedzialB;
	float il=(float)iloscP;
	float interwal=(przedzialB-przedzialA)/(il-1);
	
	for(i=0;i<iloscP-1;i++)
	{
		tabX[i]=przedzialA+i*interwal;
	}
	
	float sumaY;
	for(i=0;i<iloscP;i++)//dla kazdego X
	{
		sumaY=0;
		for(j=0;j<=potega;j++)//pozbieraj w sume wartosc Y
		{
			sumaY=sumaY+(pot(tabX[i],j))*(tabwspf[j]);
		}
		tabY[i]=sumaY+
		tabwspft[0]*(float)sin((double)tabX[i])+
		tabwspft[1]*(float)cos((double)tabX[i])+
		tabwspft[2]*(float)tan((double)tabX[i])+
		tabwspft[3]*( (float)cos((double)tabX[i]) / (float)sin((double)tabX[i]) );
	}
	//END
	
	//TEST
	printf("interwal: %f\n", interwal);
	for(i=0;i<iloscP;i++)
	{
		printf("x=%f F(x)=%f\n", tabX[i], tabY[i]);
	}	
	//TEST
	
	//Obliczanie wspolczynnikow Lagrange'a
	tabL=(W*)malloc(iloscP*sizeof(W));
	
	for(i=0;i<iloscP;i++)
	{
		W baza;
		baza.D=0;
		baza.wsp=(float*)malloc( (baza.D+1)*sizeof(float));
		baza.wsp[0]=1;
		
		j=0;
		while(j<iloscP)
		{
			if(j!=i)
			{
				W czynnik;
				W iloczyn;
				czynnik.D=1;
				czynnik.wsp=(float*)malloc( (baza.D+1)*sizeof(float));
				
				float mianownik=tabX[i]-tabX[j];
				czynnik.wsp[1]=1/mianownik;
				czynnik.wsp[0]=(-tabX[j])/mianownik;
				
				iloczyn=mnoz(czynnik, baza);
				baza = iloczyn;
			}
			j++;
		}
		tabL[i]=baza;
	}
	//END
	
	//Wypisanie wspolczynnikow Lagrange'a i przemnozenie ich przez Y
	for(i=0;i<iloscP;i++)
	{
		printf("L%d=",i);
		for(j=0;j<=tabL[i].D;j++)
		{
			printf("%f*x^%d ",tabL[i].wsp[j], j);
			tabL[i].wsp[j]=tabL[i].wsp[j]*tabY[i];
		}
		printf("\n");
	}
	//END
	
	//Dodanie wspolczynnikow w wielomian interpolacyjny
	W P;
	P.D=iloscP-1;
	P.wsp=(float*)malloc( (P.D+1)*sizeof(float));
	
	for(i=0;i<iloscP;i++)
	{
		float sumaP=0;
		for(j=0;j<iloscP;j++)
		{
			sumaP=sumaP+tabL[j].wsp[i];
		}
		P.wsp[i]=sumaP;
	}
	//Wypisanie wielomianu interpolacyjnego do pliku
	FILE *plik;
	plik=fopen("wielomianP.txt","w");
	fprintf(plik,"P(x)=");
	for(i=0;i<P.D;i++)
	{
		fprintf(plik,"(%f)*x^%d+",P.wsp[i],i);
	}
	i=P.D;
	fprintf(plik,"(%f)*x^%d",P.wsp[i],i);
	
	fclose(plik);
	//END	
	getchar();
	return 0;
}

