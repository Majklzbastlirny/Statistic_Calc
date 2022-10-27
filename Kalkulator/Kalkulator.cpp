// Kalkulator.cpp: Definuje vstupní bod pro aplikaci.
//Author: Michal Basler (247094)

//Preffered platform: Windows

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

Postup: File input->import to memory->Analyser(zjistí jestli je to číslo nebo text)->formátování->výpočty->výstup do
terminálu ->výstup do souboru 
*/

#include "Kalkulator.h"
#include "stdio.h"
#include <regex>
#include <iostream>



using namespace std;
char UnformattedData[] = 1;
double FormatedNumbers = 1;
char FormatedWords = 1;
double datasize;
	

void Loader()
{
	char Filename = ' ';
	//Ask for file name in same directory as program
	printf("Zadej jmeno souboru: ");
	scanf("%s", &Filename);

	//look for file, if not found, ask again and again
	FILE* file;
	file = fopen(&Filename, "r");
	while (file == NULL)
	{
		printf("Soubor nebyl nalezen, zadej jmeno souboru znovu: ");
		scanf("%s", Filename);
		file = fopen(&Filename, "r");
		
	}
	//get size of file and allocate memory for data
	fseek(file, 0, SEEK_END);
	datasize = ftell(file);
	rewind(file);
	UnformattedData = malloc(datasize+1);

	//put all data from file to Unformated data
	fread(UnformattedData, 1, datasize, file);
	fclose(file);
}



int Analyser()
{
	float LetterOccurence = 0;
	float NumberOccurence = 0;
	//regex_t regex;

	//create regex for numbers
	//regex number("^[0-9]*$");
	//create regex for letters
	//regex letter("^[a-zA-ZáčďéěíňóřšťůúýžÁČĎÉĚÍŇÓŘŠŤŮÚÝŽ]*$");


	
	printf("Probíhá analýza dat...");

	//scan whole file and apply regex


}
void Formatter(int type)
{


	if (type == 1)
	{
		//format numbers
		//replace , with .
		//put numbers into new array


	}
	else if (type == 2)
	{
		//format letters
	}
	else
	{
		printf("Nastala chyba. Program se ukončí.");
	}
}

int Saver()
{
	char FileName[255];
	printf("Zadejte jméno souboru, do kterého se mají výsledky uložit: ");
	scanf("%s", FileName);
	FILE *file;
	file = fopen(FileName, "w");
}

void NumericAnalyser()
{
	double Prumer = 0;
	double Vazenyprumer = 0;
	double Rozptyl = 0;
	double SmrOdchylka = 0;
	double Median = 0;
	double Min = 0;
	double Max = 0;

	//1. Aplikace bude rozdělena do dvou statistických sekcí. První možností bude zpracování
	//číselných hodnot, nad kterými budou prováděny statistické operace (průměr, vážený průměr,
	//rozptyl, směrodatná odchylka, histogram, medián).
	/*
	//calculate average
	Prumer = for (int i = 0; i < sizeof(DATA); i++) { Prumer += DATA[i]; } Prumer = Prumer / sizeof(DATA);
	Vazenyprumer = for (int i = 0; i < sizeof(DATA); i++) { Vazenyprumer += DATA[i] * i; } Vazenyprumer = Vazenyprumer / sizeof(DATA);
	//calculate variance
	Rozptyl = for (int i = 0; i < sizeof(DATA); i++) { Rozptyl += (DATA[i] - Prumer) * (DATA[i] - Prumer); } Rozptyl = Rozptyl / sizeof(DATA);
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
//calculate histogram*/
}

void TextAnalyser()
{
	//2. Druhou částí budou statistické výpočty nad textem. Program bude umožňovat výpočet počtu
	//znaků, počtu slov, histogram písmen a délek slov.
	int PocetZnaku = 0;
	int PocetSlov = 0;
	/*
	PocetZnaku = sizeof(DATA);
	/calculate number of words
	for (int i = 0; i < sizeof(DATA); i++)
	{
		if (DATA[i] == " ")
		{
			PocetSlov++;
		}
	}*/
}
	
//put word in 2 dimentional array. First dimension is word, second is number of occurences in dataset
//if word is already in array, increase second dimension by 1
//if word is not in array, add it to array and set second dimension to 1

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
