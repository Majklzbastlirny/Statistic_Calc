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
#include "dynarray.h"
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <regex>
#include <iostream>



using namespace std;

//char* FormatedNumbers = (char*)malloc(1);
//char* FormatedWords = (char*)malloc(1);
size_t total = 0;


double datasize;
char* UnformattedData = (char*)malloc(1);


int Loader(char* dragndrop)
{
#define LOWER 1024
#define UPPER 65536

	char name[255];
	FILE* file;

	printf("\nNyni se soubor nacte\n");
	if (dragndrop == NULL) {
		printf("Zadej jmeno souburu ve stejne slozce jako executable nebo cestu.\n");
		scanf("%s", &name);
		file = fopen(name, "r");
	}
	else {
		file = fopen(dragndrop, "r");
		
	}
	

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
	total = 0;


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
		printf("Chyba pri cteni ze souboru!\n");
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

	fclose(file);

	datasize = 0;
	for (int i = 0; i < total; i++)
	{
		if (UnformattedData[i] == '\n' || UnformattedData[i] == ' ' || UnformattedData[i] == EOF)
		{
			datasize++;
		}
	}

	printf("Pocet invidualnich veci v souboru: %.0lf\n", datasize);


	return 0;

}



int Analyser()
{
	float LetterOccurence = 0;
	float NumberOccurence = 0;
	float Other = 0;
	printf("Probiha analyza dat...\n");

	//checks, how many characters are numbers and how many are letters
	for (int i = 0; i < total; i++)
	{
		if (isdigit(UnformattedData[i]))
		{
			NumberOccurence++;
		}
		else if (isalpha(UnformattedData[i]) && UnformattedData[i] != '\0')
		{
			LetterOccurence++;
		}
		else {
		Other++;
		}
	}

	printf("Soubor obsahuje %.0f cisel %.0f pismen a %.0f ostatnich znaku.\n", NumberOccurence, LetterOccurence, Other);
	double test;
	scanf("%lf", &test);
	if (LetterOccurence == 0)
	{
		//printf("The file contains more numbers than letters.\n");
		//FormatedWords = (char*)malloc(total);


		//free(UnformattedData);
		return 1;
	}
	else if (NumberOccurence == 0)
	{
		//printf("The file contains more letters than numbers.\n");
		//FormatedNumbers = (char*)malloc(total);


		//free(UnformattedData);
		return 2;
	}
	else
	{
		//printf("The file contains the same amount of numbers and letters.\n");
		return 0;
	}



	//regex_t regex;
	//create regex for numbers
	//regex number("^[0-9]*$");
	//create regex for letters
	//regex letter("^[a-zA-ZáčďéěíňóřšťůúýžÁČĎÉĚÍŇÓŘŠŤŮÚÝŽ]*$");








}
void Formatter(int type)
{
	//https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
	/*
	if (type == 1)
	{
		//format numbers
		//replace , with .
		//put numbers into new array
		
		//create new array with the number of columns same as datasize variable (dynamically allocated)
		




	for (int i = 0; i < total; i++)
	{
		if (isdigit(UnformattedData[i]))
		{
			FormatedNumbers[i] = UnformattedData[i];
		}
		else if (UnformattedData[i] == ',')
		{
			FormatedNumbers[i] = '.';
		}
		else
		{
			FormatedNumbers[i] = 0;
		}
	}
	}
	else if (type == 2)
	{
		
		char FormatedWords[datasize];
		for (int i = 0; i < total; i++)
		{
			if (isalpha(UnformattedData[i]))
			{
				FormatedWords[i] = UnformattedData[i];
			}
			else
			{
				FormatedWords[i] = 0;
			}
		}
	}
	else
	{
		printf("Chyba pri formatovani dat!\n");
	}*/
}

int Saver()
{
	char FileName[255];
	printf("Zadejte jmeno souboru, do ktereho se maji vysledky ulozit: ");
	scanf("%s", FileName);
	FILE* file;
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
	
	//calculate average

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

int main(int argc, char* argv[]) {

	printf("Vitejte v kalkulacce\n");
	printf("Verze 0.0.1\n");
	printf("Autor: Michal Basler (247094)\n");
	//load data from file
	if (argc == 2) {
		printf("Program dostal soubor.\n");
	}


	switch (Loader((argv[1])))
	{
	case 1:
		printf("Program se ukonci.");
		return 0;

	default:
		break;
	}


	switch (Analyser())
	{
	case 1:
		printf("Program indentifikoval data jako: čísla\n");
		Formatter(1);
		NumericAnalyser();
		break;
	case 2:
		printf("Program indentifikoval data jako: znaky\n");
		Formatter(2);
		TextAnalyser();
		break;
	default:
		printf("Program obsahuje jak cisla, tak i znaky. To ale bohuzel nemuzu analyzovat");
		printf("Program se ukonci.");
		return 0;

	}

	return 0;
}
