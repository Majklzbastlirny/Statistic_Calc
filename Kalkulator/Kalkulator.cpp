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
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <regex>
#include <iostream>



using namespace std;
//char UnformattedData[] = 1;
double FormatedNumbers = 1;
char FormatedWords = 1;
double datasize;
char* UnformattedData = (char*)malloc(255);


int Loader()
{
#define LOWER 1024
#define UPPER 65536

	char name[1];
	printf("Zadej jmeno souburu ve stejne slozce jako executable nebo cestu.\n");
	scanf("%s", &name);

	FILE* file;


	file = fopen(name, "r");


	if (file == NULL)
	{
		printf("Chyba pri otevirani souboru!\n");
		return 1;
	}
	printf("Soubor nalezen. Probiha nacitani...\n");
	// increase will keep track of the size by which to increase the dynamically
	// allocated block of memory
	size_t increase = LOWER;

	// allocated will keep track of the total size of the dynamically allocated
	// block of memory
	size_t allocated = increase;

	// Initially allocate a block of memory of size equal to our lower bound
	UnformattedData = (char*)malloc(allocated);

	// total will keep track of the total number of characters in the file
	size_t total = 0;


	while (!feof(file) && !ferror(file))
	{

		UnformattedData[total] = fgetc(file);
		total++;


		if (total >= allocated)
		{

			if (increase >= UPPER) increase = UPPER;

			allocated += increase;

			UnformattedData = (char*)realloc(UnformattedData, allocated);


			increase *= 2;
		}
	}

	// If there has been an error reading from the file, exit with an error
	// message and status
	if (ferror(file))
	{
		printf("Error reading from file!\n");
		return 1;
	}

		// It's most likely that we have more space allocated than we actually need
		// to store the string, e.g. if realloc() is never we'll have allocated
		// 1024 chars/bytes worth of space (or whatever our lower limit was) for
		// a string that might only be 50 characers long.  This would be a lot of
		// unused memory, so we use realloc() to decrease the size of the block of
		// memory down to exactly the number of chars requires (total).
	UnformattedData = (char*)realloc(UnformattedData, total);

		// Set the null terminator as the last char in the string to termiante
		// the string.
	UnformattedData[total - 1] = '\0';

		// Close the file as we are done working with it now.
		fclose(file);

		// Output the string containing the file contents
		printf("File Contents:\n\n");
		//printf("%s\n", UnformattedData);

		// Free the dynamically allocated string as we are done working with it too.
		//free(string);

		return 0;
	
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


	
	printf("Probíhá analýza dat...\n");
	printf("%s\n", UnformattedData);

	//scan whole file and apply regex


	return 0;
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
	return 0;
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

	printf("Vítejte v kalkulačce\n");
	//load data from file
	Loader() ? printf("gud") : printf("bad");
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
