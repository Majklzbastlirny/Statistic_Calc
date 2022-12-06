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

#include "IsAlphaPlus.h"
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <regex>
#include <iostream>



using namespace std;



size_t total = 0;

char name[255];
double datasize;
char* UnformattedData = (char*)malloc(1);
//array for output data. dynamic, 2 columns (1st is Name, 2nd is Value)
char** OutputData = (char**)malloc(1);

int Loader(char* dragndrop)
{
#define LOWER 1024
#define UPPER 65536

	
	FILE* file;

	printf("\nNyni se nactou data\n");
	if (dragndrop == NULL) {
		printf("Zadej jmeno souburu ve stejne slozce jako executable nebo cestu.\n");
		
		scanf("%s", &name);
		file = fopen(name, "r");
	}
	else {
		file = fopen(dragndrop, "r");
		
	}
	//format filename to make it windows compliant
	//
	

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

	
	return 0;

}



int AnalyseAndFormat()
{
	float LetterOccurence = 0;
	float NumberOccurence = 0;
	float Other = 0;
	printf("Probiha analyza dat...\n");
	
	datasize = 0;
	for (int i = 0; i < total; i++)
	{
		if (UnformattedData[i] == '\n' || UnformattedData[i] == ' ' || UnformattedData[i] == EOF)
		{
			datasize++;
		}
	}

	printf("Pocet invidualnich veci v souboru: %.0lf\n", datasize);


	//checks, how many characters are numbers and how many are letters
	for (int i = 0; i < total; i++)
	{
		if (isdigit(UnformattedData[i]))
		{
			NumberOccurence++;
		}
		else if (IsAlphaPlus(UnformattedData[i]) && UnformattedData[i] != '\0')
		{
			LetterOccurence++;
		}
		else {
		Other++;
		}
	}

	printf("Soubor obsahuje %.0f cisel %.0f pismen a %.0f ostatnich znaku.\n", NumberOccurence, LetterOccurence, Other);
	//double test;
	//scanf("%lf", &test);
	if (LetterOccurence == 0)
	{
		//go through the whole array. if it's a number or decimal point, add it to buffer. if it's not, convert buffer to double and add it to output array. Log the number of whole numbers in output array.
		
		return 1;
	}
	else if (NumberOccurence == 0)
	{
		//create new array, 
		return 2;
	}
	else
	{
		//printf("The file contains the same amount of numbers and letters.\n");
		return 0;
	}


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
	
	double PocetCisel = 0;
	double PocetInvCisel = 0;

	//allocate array of doubles
	for (long i = 0; i < total; i++)
	{
		if (isdigit(UnformattedData[i]))
		{
			PocetInvCisel++;
		}
	}

	printf("Pocet invidualnich cisel v souboru: %lf\n", PocetInvCisel);

	//count number of words. Word is defined as a sequence of letters.
	for (long i = 0; i < total; i++)
	{
		if (isdigit(UnformattedData[i]) && UnformattedData[i + 1] != '.' && UnformattedData[i + 1] != '-')
		{
			PocetCisel++;
		}

	}

	printf("Pocet formatovanych cisel v souboru: %lf\n", PocetCisel);



	//list all words
	char* buffer = (char*)malloc(1);
	double bufferindex = 0;
	double outputindex = 0;
	bool lastchar = 0;
	//create array FormattedWords with size PocetSlov
	/*
	double** array = new double* [rows];
	for (int i = 0; i < rows; i++)
	{
		array[i] = new double[columns];
	}*/

	//create array with PocetSlov number of rows and 3 columns
	//first row is for word, second is for number of letters, third is for number of occurences
	double** FormattedNumbers = (double**)malloc(datasize * sizeof(long*));
	for (long i = 0; i < datasize; i++)
	{
		FormattedNumbers[i] = (double*)malloc(sizeof(long));
	}


	for (long i = 0; i < total; i++)
	{
		if (isdigit(UnformattedData[i]) || UnformattedData[i] == '-' || UnformattedData[i] == '.')
		{
			//buffer[bufferindex] = UnformattedData[i];
			bufferindex++;
			buffer = (char*)realloc(buffer, bufferindex + 1);
			lastchar = 1;
		}
		else
		{
			if (lastchar == 1)
			{
				//read all characters from buffer, combine them into single word, add it to FormattedWords array and extend it by 1, reset buffer
				//printf("Word found: ");
				long i;
				for (i = 0; i < bufferindex; i++)
				{
					//printf("%c", buffer[i]);
					//join buffer[i] to FormattedWords[outputindex][0]
					//FormattedNumbers[outputindex][i] = buffer[i];




				}
				//FormattedNumbers[outputindex][i] = 0;

				//printf("\n");
				//append word to FormattedWords array


				//Fx;	IX THIS SHIT
				//add word to FormattedWords array
				//FormattedWords[outputindex][0] = buffer;
				//printf("added to buffer");
				//FormattedWords[outputindex][1] = bufferindex;
				//printf("added the number of letters in the word");
				//FormattedWords[outputindex][2] = 1;
				outputindex++;
				//buffer = 0;
				bufferindex = 0;
				lastchar = 0;
			}

		}
	}

	printf("These numbers were found:\n");
	for (long i = 0; i < PocetCisel; i++)
	{
		printf("%lf\n", FormattedNumbers[i]);
	}
}

void TextAnalyser()
{
	//2. Druhou částí budou statistické výpočty nad textem. Program bude umožňovat výpočet počtu
	//znaků, počtu slov, histogram písmen a délek slov.
	int PocetPismen = 0;
	int PocetSlov = -1;
	int ShortestWordLengh = 9999;
	int AverageWordLengh = 0;
	int LongestWordLengh = 0;
	
	//create ints from LetA to LetZ
	int LetA = 0, LetB = 0, LetC = 0, LetD = 0, LetE = 0, LetF = 0, LetG = 0, LetH = 0, LetI = 0, LetJ = 0, LetK = 0, LetL = 0, LetM = 0, LetN = 0, LetO = 0, LetP = 0, LetQ = 0, LetR = 0, LetS = 0, LetT = 0, LetU = 0, LetV = 0, LetW = 0, LetX = 0, LetY = 0, LetZ = 0;
	
	
	//count number of letters
	for (int i = 0; i < total; i++)
	{
		if (IsAlphaPlus(UnformattedData[i]))
		{
			PocetPismen++;
		}
	}
	printf("Pocet pismen v souboru: %d\n", PocetPismen);
	
	//count number of words. Word is defined as a sequence of letters.
	for (int i = 0; i < total; i++)
	{
		if (IsAlphaPlus(UnformattedData[i]) && !IsAlphaPlus(UnformattedData[i + 1]))
		{
			PocetSlov++;
		}
	}
	
	printf("Pocet slov v souboru: %d\n", PocetSlov);

	
	
	
	//list all words
	char* buffer = (char*)malloc(1);
	int bufferindex = 0;
	int outputindex = 0;
	bool lastchar = 0;
	//create array FormattedWords with size PocetSlov
	/*
	double** array = new double* [rows];
	for (int i = 0; i < rows; i++)
	{
		array[i] = new double[columns];
	}*/
	
	//create array with PocetSlov number of rows and 3 columns
	//first row is for word, second is for number of letters, third is for number of occurences
	char** FormattedWords = (char**)malloc(PocetSlov * sizeof(char*));
	for (int i = 0; i < PocetSlov; i++)
	{
		FormattedWords[i] = (char*)malloc(45 * sizeof(char));
	}
	

	for (int i = 0; i < total; i++)
	{
		if (isalpha(UnformattedData[i]) || UnformattedData[i] == '-' || UnformattedData[i] == '\'')
		{	//BOILERPLATE GARBARE. FIX IT!
			if (UnformattedData[i] == 'A' || UnformattedData[i] == 'a')
			{
				LetA++;
			}
			if (UnformattedData[i] == 'B' || UnformattedData[i] == 'b')
			{
				LetB++;
			}
			if (UnformattedData[i] == 'C' || UnformattedData[i] == 'c')
			{
				LetC++;
			}
			if (UnformattedData[i] == 'D' || UnformattedData[i] == 'd')
			{
				LetD++;
			}
			if (UnformattedData[i] == 'E' || UnformattedData[i] == 'e')
			{
				LetE++;
			}
			if (UnformattedData[i] == 'F' || UnformattedData[i] == 'f')
			{
				LetF++;
			}
			if (UnformattedData[i] == 'G' || UnformattedData[i] == 'g')
			{
				LetG++;
			}
			if (UnformattedData[i] == 'H' || UnformattedData[i] == 'h')
			{
				LetH++;
			}
			if (UnformattedData[i] == 'I' || UnformattedData[i] == 'i')
			{
				LetI++;
			}
			if (UnformattedData[i] == 'J' || UnformattedData[i] == 'j')
			{
				LetJ++;
			}
			if (UnformattedData[i] == 'K' || UnformattedData[i] == 'k')
			{
				LetK++;
			}
			if (UnformattedData[i] == 'L' || UnformattedData[i] == 'l')
			{
				LetL++;
			}
			if (UnformattedData[i] == 'M' || UnformattedData[i] == 'm')
			{
				LetM++;
			}
			if (UnformattedData[i] == 'N' || UnformattedData[i] == 'n')
			{
				LetN++;
			}
			if (UnformattedData[i] == 'O' || UnformattedData[i] == 'o')
			{
				LetO++;
			}
			if (UnformattedData[i] == 'P' || UnformattedData[i] == 'p')
			{
				LetP++;
			}
			if (UnformattedData[i] == 'Q' || UnformattedData[i] == 'q')
			{
				LetQ++;
			}
			if (UnformattedData[i] == 'R' || UnformattedData[i] == 'r')
			{
				LetR++;
			}
			if (UnformattedData[i] == 'S' || UnformattedData[i] == 's')
			{
				LetS++;
			}
			if (UnformattedData[i] == 'T' || UnformattedData[i] == 't')
			{
				LetT++;
			}
			if (UnformattedData[i] == 'U' || UnformattedData[i] == 'u')
			{
				LetU++;
			}
			if (UnformattedData[i] == 'V' || UnformattedData[i] == 'v')
			{
				LetV++;
			}
			if (UnformattedData[i] == 'W' || UnformattedData[i] == 'w')
			{
				LetW++;
			}
			if (UnformattedData[i] == 'X' || UnformattedData[i] == 'x')
			{
				LetX++;
			}
			if (UnformattedData[i] == 'Y' || UnformattedData[i] == 'y')
			{
				LetY++;
			}
			if (UnformattedData[i] == 'Z' || UnformattedData[i] == 'z')
			{
				LetZ++;
			}
			
			
			buffer[bufferindex] = UnformattedData[i];
			bufferindex++;
			buffer = (char*)realloc(buffer, bufferindex + 1);
			lastchar = 1;
		}
		else
		{
			if (lastchar == 1)
			{
				//read all characters from buffer, combine them into single word, add it to FormattedWords array and extend it by 1, reset buffer
				//printf("Word found: ");
				int i;
				for ( i = 0; i < bufferindex; i++)
				{
					//printf("%c", buffer[i]);
					//join buffer[i] to FormattedWords[outputindex][0]
					FormattedWords[outputindex][i] = buffer[i];
					
					
					
					
				}
				FormattedWords[outputindex][i] = 0;

				//printf("\n");
				//append word to FormattedWords array
				
				
				//Fx;	IX THIS SHIT
				//add word to FormattedWords array
				//FormattedWords[outputindex][0] = buffer;
				//printf("added to buffer");
				//FormattedWords[outputindex][1] = bufferindex;
				//printf("added the number of letters in the word");
				//FormattedWords[outputindex][2] = 1;
				outputindex++;
				//buffer = 0;
				bufferindex = 0;
				lastchar = 0;
			}
			
		}
	}
	//printf("These words were found:\n");
	//for (int i = 0; i < PocetSlov; i++)
	//{
	//	printf("%s\n", FormattedWords[i]);
	//}
	
	//calculate average word length, longest word and shortest word
	long long wordlength2 = 0;
	for (int i = 0; i < PocetSlov; i++) {
		
		wordlength2 += strlen(FormattedWords[i]);
		//printf("The lengh of the word %s is %d\n", FormattedWords[i], strlen(FormattedWords[i]));
		
		
		int wordlength = strlen(FormattedWords[i]);
		if (wordlength > LongestWordLengh)
		{
			LongestWordLengh = wordlength;
			
		}
		if (wordlength < ShortestWordLengh)
		{
			ShortestWordLengh = wordlength;
			
		}
	}
	AverageWordLengh = wordlength2 / PocetSlov;
	printf("The average word length is %d\n", AverageWordLengh);
	printf("The longest word is %d characters long\n", LongestWordLengh);
	printf("The shortest word is %d characters long\n", ShortestWordLengh);



	printf("The letter A was found %d times\n", LetA);
	printf("The letter B was found %d times\n", LetB);
	printf("The letter C was found %d times\n", LetC);
	printf("The letter D was found %d times\n", LetD);
	printf("The letter E was found %d times\n", LetE);
	printf("The letter F was found %d times\n", LetF);
	printf("The letter G was found %d times\n", LetG);
	printf("The letter H was found %d times\n", LetH);
	printf("The letter I was found %d times\n", LetI);
	printf("The letter J was found %d times\n", LetJ);
	printf("The letter K was found %d times\n", LetK);
	printf("The letter L was found %d times\n", LetL);
	printf("The letter M was found %d times\n", LetM);
	printf("The letter N was found %d times\n", LetN);
	printf("The letter O was found %d times\n", LetO);
	printf("The letter P was found %d times\n", LetP);
	printf("The letter Q was found %d times\n", LetQ);
	printf("The letter R was found %d times\n", LetR);
	printf("The letter S was found %d times\n", LetS);
	printf("The letter T was found %d times\n", LetT);
	printf("The letter U was found %d times\n", LetU);
	printf("The letter V was found %d times\n", LetV);
	printf("The letter W was found %d times\n", LetW);
	printf("The letter X was found %d times\n", LetX);
	printf("The letter Y was found %d times\n", LetY);
	printf("The letter Z was found %d times\n\n", LetZ);
	//Save
	//printf("Do you wish to save the results to a file? (Y/N)\n");
	//char SaveToFile;
	//scanf("%c", &SaveToFile);
	//SaveToFile = toupper(SaveToFile);
	//if (SaveToFile == 'Y')
	//{
		printf("Enter the name of the file you wish to save the results to:\n");
		char FileName[100];
		scanf("%s", FileName);
		FILE* f = fopen(FileName, "w");
		
		fprintf(f, "The analysed file is %s\n", name);
		fprintf(f, "%d words\n", PocetSlov);
		fprintf(f, "%d letters\n", PocetPismen);
		fprintf(f, "The average word length is %d\n", AverageWordLengh);
		fprintf(f, "The longest word is %d characters long\n", LongestWordLengh);
		fprintf(f, "The shortest word is %d characters long\n\n", ShortestWordLengh);
		fprintf(f, "Number of letters:\n");
		fprintf(f, "A: %d\n", LetA);
		fprintf(f, "B: %d\n", LetB);
		fprintf(f, "C: %d\n", LetC);
		fprintf(f, "D: %d\n", LetD);
		fprintf(f, "E: %d\n", LetE);
		fprintf(f, "F: %d\n", LetF);
		fprintf(f, "G: %d\n", LetG);
		fprintf(f, "H: %d\n", LetH);
		fprintf(f, "I: %d\n", LetI);
		fprintf(f, "J: %d\n", LetJ);
		fprintf(f, "K: %d\n", LetK);
		fprintf(f, "L: %d\n", LetL);
		fprintf(f, "M: %d\n", LetM);
		fprintf(f, "N: %d\n", LetN);
		fprintf(f, "O: %d\n", LetO);
		fprintf(f, "P: %d\n", LetP);
		fprintf(f, "Q: %d\n", LetQ);
		fprintf(f, "R: %d\n", LetR);
		fprintf(f, "S: %d\n", LetS);
		fprintf(f, "T: %d\n", LetT);
		fprintf(f, "U: %d\n", LetU);
		fprintf(f, "V: %d\n", LetV);
		fprintf(f, "W: %d\n", LetW);
		fprintf(f, "X: %d\n", LetX);
		fprintf(f, "Y: %d\n", LetY);
		fprintf(f, "Z: %d\n", LetZ);

		fclose(f);
		printf("The data was successfully saved to output.txt\n");

		//save the data to a file
	//}
	
	
	

	
}



int main(int argc, char* argv[]) {

	printf("Vitejte v kalkulacce\n");
	printf("Verze 0.0.3\n");
	printf("Autor: Michal Basler (247 094), Oldrich Hana (247 113)\n");
	printf("Dulezite: Program podporuje pouze ascii znaky (a-zA-Z).\nKnihovna IsAlphaPlus mela tohle resit, ale nefunguje.\n");
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


	switch (AnalyseAndFormat())
	{

	case 1:
		printf("Program indentifikoval data jako: cisla\n");
		NumericAnalyser();
		break;
	case 2:
		printf("Program indentifikoval data jako: znaky\n");
		TextAnalyser();
		break;
	default:
		printf("Program obsahuje jak cisla, tak i znaky. To ale bohuzel nemuzu analyzovat");
		printf("Program se ukonci.");
		return 0;

	}
	printf("To end the program, press any key.\n");
	getchar();
	
	return 0;
}
