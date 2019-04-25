#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct uchitel
{
    char kod[256];
    char familiya[256];
    char imya[256];
    char otchestvo[256];
    int pol;
    char data[256];
    char address[256];
    char tel[256];
    char predmet[256];
    int staj;
};

struct uchitel *uchitels;
int len;

void GetUchitels(void)
{
	uchitels = (struct uchitel*) malloc(0);
	len = 0;
	FILE *f = fopen("uchitels.bin","rb");
	struct uchitel *buchitel;
	buchitel = (struct uchitel*) malloc(sizeof(struct uchitel));
	if(f)
    {
        while(fread(buchitel, sizeof(struct uchitel), 1, f) == 1)
        {
			len++;
			uchitels = (struct uchitel*) realloc(uchitels,len*sizeof(struct uchitel));
			uchitels[len-1] = *buchitel;
        }
        fclose(f);
    }
    free(buchitel);
}

void FreeUchitels(void)
{
    free(uchitels);
    len = 0;
}

void AddNewUchitel(void)
{
	system("cls");
	GetUchitels();
	struct uchitel cuhitel;
	printf("Noviy uchitel\n");
	int f=0;
	do {
		printf("Vvedite kod: ");
		gets(cuhitel.kod);
		for (int i=0;i<len;i++)
			if (strcmp(uchitels[i].kod,cuhitel.kod) == 0)
			{
				f = 1;
				printf("Uchitel s takim kodom uje est\n");
				break;
			} else f = 0;
	} while (f);
	printf("Vvedite familiyu: ");
	gets(cuhitel.familiya);
	printf("Vvedite imya: ");
	gets(cuhitel.imya);
	printf("Vvedite otchestvo: ");
	gets(cuhitel.otchestvo);
	printf("Vvedite pol muj/jen (1/0): ");
	scanf("%d",&cuhitel.pol);
	getchar();
	printf("Vvedite datu rojdeniya (DD.MM.YYYY): ");
	gets(cuhitel.data);
	printf("Vvedite adress: ");
	gets(cuhitel.address);
	printf("Vvedite telefon: ");
	gets(cuhitel.tel);
	printf("Vvedite predmet: ");
	gets(cuhitel.predmet);
	printf("Vvedite staj raboti: ");
	scanf("%d",&cuhitel.staj);
	getchar();
    FreeUchitels();
	FILE *fl = fopen("uchitels.bin","ab");
	fwrite(&cuhitel, sizeof(struct uchitel), 1, fl);
    fclose(fl);
}

void SearchFamK(void)
{
	system("cls");
	GetUchitels();
	printf("Poisk informatsii o uchitelyah, familii kotorih nachinautsya na 'K':\n");
	for (int i=0;i<len;i++)
		if (uchitels[i].familiya[0] == 'K')
			printf(" %s %s %s, %s, %s\n",uchitels[i].familiya,uchitels[i].imya,uchitels[i].otchestvo,uchitels[i].address,uchitels[i].tel);
    FreeUchitels();
	_getch();
}

void SearchMM40(void)
{
	system("cls");
	GetUchitels();
	printf("Poisk informatsii o uchitelyah mujskogo pola s vozrastom menie 40 let:\n");
	for (int i=0;i<len;i++)
	{
		if (uchitels[i].pol)
		{
			char DD[3];
			strncpy(DD,uchitels[i].data,2);
			char MM[3];
			strcpy(MM,&strncpy(MM,uchitels[i].data,5)[3]);
			char YYYY[5];
			strcpy(YYYY,&uchitels[i].data[6]);
			time_t rawtime;
			struct tm *timeinfo;
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			if ((timeinfo[0].tm_year*365+timeinfo[0].tm_yday-atoi(DD)-atoi(MM)*30-(atoi(YYYY)-1900)*365)/365 < 40)
				printf(" %s %s %s, %s, %d\n",uchitels[i].familiya,uchitels[i].imya,uchitels[i].otchestvo,uchitels[i].predmet,uchitels[i].staj);
		}
	}
    FreeUchitels();
	_getch();
}

void Print(void)
{
	system("cls");
	GetUchitels();
	printf("Spisok uchiteley:\n");
	for (int i=0;i<len;i++)
	{
		printf("uchitel #%d\n Kod: %s\n FIO: %s %s %s\n",i,uchitels[i].kod,uchitels[i].familiya,uchitels[i].imya,uchitels[i].otchestvo);
		if (uchitels[i].pol)
			printf(" Pol: mujskoy\n");
		else printf(" Pol: jenskiy\n");
		printf(" Data rojdeniya: %s\n Adress: %s\n Telefon: %s\n Predmet: %s\n Staj: %d\n\n",uchitels[i].data,uchitels[i].address,uchitels[i].tel,uchitels[i].predmet,uchitels[i].staj);
	}
    FreeUchitels();
	_getch();
}

void CountStajB10s(void)
{
	system("cls");
	int x=0;
	GetUchitels();
	printf("Opredelenie kol-va uchiteley so stajem raboti boleye 10 let: ");
	for (int i=0;i<len;i++)
		if (uchitels[i].staj > 10)
			x++;
	printf("%d\n",x);
    FreeUchitels();
	_getch();
}

void AvrgAge(void)
{
	system("cls");
	GetUchitels();
	printf("Sredniy vozrast uchiteley: ");
	int x=0;
	for (int i=0;i<len;i++)
	{
		char DD[3];
		strncpy(DD,uchitels[i].data,2);
		char MM[3];
		strcpy(MM,&strncpy(MM,uchitels[i].data,5)[3]);
		char YYYY[5];
		strcpy(YYYY,&uchitels[i].data[6]);
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		x+=(timeinfo[0].tm_year*365+timeinfo[0].tm_yday-atoi(DD)-atoi(MM)*30-(atoi(YYYY)-1900)*365)/365;
	}
	printf("%f\n",float(x / len));
    FreeUchitels();
	_getch();
}

int main()
{
	while (1)
	{
	system("cls");
	printf("1) Dobavlenie informatsii o novom uchitele\n2) Poisk informatsii o uchitelyah, familii kotorih nachinautsya na 'K'\n3) Poisk informatsii o uchitelyah mujskogo pola s vozrastom menie 40 let\n4) Otobradjenie informatsii o uchitelyah\n5) Opredelenie kol-va uchiteley so stajem raboti boleye 10 let\n6) Opredelenie srednego vozrasta uchiteley\ne) Exit");
	char c = _getch();
	if (c == '1')
		AddNewUchitel();
	else if (c == '2')
		SearchFamK();
	else if (c == '3')
		SearchMM40();
	else if (c == '4')
		Print();
	else if (c == '5')
		CountStajB10s();
	else if (c == '6')
		AvrgAge();
	else if ((c == 'E') or (c == 'e'))
		exit(0);
	}
}
