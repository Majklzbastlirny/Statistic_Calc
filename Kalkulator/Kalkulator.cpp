// Kalkulator.cpp: Definuje vstupní bod pro aplikaci.
//Author: Michal Basler (247094)
/*
16) Statistická kalkulačka (průměr, rozptyl, histogramy)
Úkolem bude vytvoření aplikace pro statistické výpočty. Jako vstupní parametry budou sloužit data
získaná z textového souboru či vstup z konzole.
Základní parametry programu:
1. Aplikace bude rozdělena do dvou statistických sekcí. První možností bude zpracování
číselných hodnot, nad kterými budou prováděny statistické operace (průměr, vážený průměr,
rozptyl, směrodatná odchylka, histogram, medián).
2. Druhou částí budou statistické výpočty nad textem. Program bude umožňovat výpočet počtu
znaků, počtu slov, histogram písmen a délek slov.
3. Výsledky bude možné uložit do textového souboru.
Bonusový úkol: Implementujte možnost vykreslení histogramu a gaussova rozložení do konzole
*/

#include "Kalkulator.h"
#include "stdio.h"
#include <regex>
#include <iostream>



using namespace std;
char DATA[];

void Loader()
{

//Ask for file name in same directory as program
printf("Zadej jmeno souboru: ");
scanf("%s", DATA);

//look for file, if not found, ask again and again
FILE *file;
file = fopen(DATA, "r");
while (file == NULL)
{
printf("Soubor nebyl nalezen, zadej jmeno souboru znovu: ");
scanf("%s", DATA);
file = fopen(DATA, "r");
}
printf("Soubor nalezen. Nyní se uloží data do paměti.");
realloc(DATA, sizeof(DATA) + sizeof(char));
fgets(DATA, sizeof(DATA), file);
printf("Data byla úspěšně načtena. Nyní můžete provádět statistické výpočty.");
fclose(file);
}




int Analyser()
{


	char NUMBERS[] = "^[0-9]*$";
	char LETTERS[] = "^[a-zA-ZáčďéěíňóřšťůúýžÁČĎÉĚÍŇÓŘŠŤŮÚÝŽ]*$";

	printf("Probíhá analýza dat...");

if (regex_match(DATA, NUMBERS))
{
	printf("Data obsahují pouze čísla. Nyní můžete provádět statistické výpočty nad číselnými daty.");
	return 1;
}
else if (regex_match(DATA, LETTERS)){
	printf("Data obsahují pouze text. Nyní můžete provádět statistické výpočty nad textovými daty.");
	return 2;
}
else
{
	printf("Data obsahují jak čísla, tak text. Tento program s tímto typem dat pracovat ještě neumí.");
	return 0;
}
}


int Saver()
{
	char FileName[1];
	printf("Zadejte jméno souboru, do kterého se mají výsledky uložit: ");
	scanf("%s", FileName);
	FILE *file;
	file = fopen(FileName, "w");
}

void NumericAnalyser()
{
	double Prumer;
	double Vazenyprumer;
	double Rozptyl;
	double SmrOdchylka;
	double Median;
	double Min;
	double Max;

	

	
//1. Aplikace bude rozdělena do dvou statistických sekcí. První možností bude zpracování
//číselných hodnot, nad kterými budou prováděny statistické operace (průměr, vážený průměr,
//rozptyl, směrodatná odchylka, histogram, medián).

//calculate average
Prumer = for (int i = 0; i < sizeof(DATA); i++) { Prumer += DATA[i]; } Prumer = Prumer / sizeof(DATA);
Vazenyprumer = for(int i = 0; i < sizeof(DATA); i++) { Vazenyprumer += DATA[i] * i; } Vazenyprumer = Vazenyprumer / sizeof(DATA);
//calculate variance
Rozptyl = for(int i = 0; i < sizeof(DATA); i++) { Rozptyl += (DATA[i] - Prumer) * (DATA[i] - Prumer); } Rozptyl = Rozptyl / sizeof(DATA);
//calculate standard deviation
SmrOdchylka = sqrt(Rozptyl);
//calculate median
if (sizeof(DATA) % 2 == 0)
{
	Median = (DATA[sizeof(DATA) / 2] + DATA[sizeof(DATA) / 2 + 1]) / 2;
}
else
{
	Median = DATA[sizeof(DATA) / 2];

}

//calculate min and max
Min = DATA[0];
Max = DATA[0];
for (int i = 0; i < sizeof(DATA); i++)
{
	if (DATA[i] < Min)
	{
		Min = DATA[i];
	}
	if (DATA[i] > Max)
	{
		Max = DATA[i];
	}
}
//calculate histogram
}

void TextAnalyser()
{
	//2. Druhou částí budou statistické výpočty nad textem. Program bude umožňovat výpočet počtu
//znaků, počtu slov, histogram písmen a délek slov.
	int PocetZnaku;
	int PocetSlov = 0;

	PocetZnaku = sizeof(DATA);
//calculate number of words
	for (int i = 0; i < sizeof(DATA); i++)
	{
		if (DATA[i] == " ")
		{
			PocetSlov++;
		}
	}

int main(){
	printf("Vítejte v kalkulačce");
	//load data from file
	Loader();
	//determine type of data
	switch (Analyser())
	{
	case 1:
		NumericAnalyser();
		break;
	case 2:
		TextAnalyser();
		break;
	default:
	 printf("Program se ukončí.");
	 return 0;

}

return 0;
}
