#include "DefinseValues.h"
#include "RoomStruct.h"
#include "HotelStruct.h"
#include "FanctionDecleretions.h"

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>  

char encryptMethod(void*  genaralVariable, int numberOfBytes )
{
	int randomNumber = getRandomNumber();
	unsigned char *variable = (unsigned char*) genaralVariable;
	saveNumberToFile(randomNumber);
	//Swap
	*variable = swapVariableWithRandomNumber(variable,randomNumber);
	//Xor
	xorTheValue(variable,numberOfBytes);
	//Shift right circle
	shiftRightCircle(variable,numberOfBytes,randomNumber);
   
	return *variable;
}
char decryptMethod(void* genaralVariable, int numberOfBytes)
{	
	int randomNumber =0 ;
	unsigned char* variable = (unsigned char*) genaralVariable;
	importNumberFromFile(&randomNumber);
	//Shift left circle
	shiftLeftCircle(variable,numberOfBytes,randomNumber);
	//Xor
	xorTheValue(variable,numberOfBytes);	
	//Swap
	*variable = swapVariableWithRandomNumber(variable,randomNumber);
	return *variable;
}
void saveNumberToFile(int number)
{
	FILE* f=  fopen(NAME_TEXT_FOR_RANDOM_NUMBER ,"w+");
	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		exit(0);
	}
	fprintf(f,"%d\n",number);
	fclose(f);
}
char swapVariableWithRandomNumber(unsigned char* variable,int randomNumber )
{
	int tmpBit = getAttributeOrGetBitFromRight(*variable,randomNumber);
	*variable=setAttributeOrBitFromRight(*variable,randomNumber,getAttributeOrGetBitFromRight(*variable,randomNumber+1));
	if(randomNumber+1>MAX_BIT_INDEX_TO_SET_ZERO)
	*variable=setAttributeOrBitFromRight(*variable,randomNumber+1,0);
	else
	*variable = setAttributeOrBitFromRight(*variable,randomNumber+1,tmpBit);
	return *variable;
}
void shiftLeftCircle(void* genaralVariable , size_t const size,int randomNumber )
{
	int i,j;
    unsigned char *byte= (unsigned char*) genaralVariable;
	int tmpBit;
	for (i = 0; i < randomNumber; i++)
	{
		tmpBit = getAttributeOrGetBitFromRight(byte[size-1],BYTE_LENGTH-1);
		for(j = 0; j < (int)size ; j++)
		   byte[j] = byte[j] << 1;
	    byte[0] = setAttributeOrBitFromRight(byte[0],0,tmpBit);
	}
	
}
void shiftRightCircle(void* genaralVariable, size_t const size,int randomNumber )
{
	int i,j;
	unsigned char *byte= (unsigned char*) genaralVariable;
	int tmpBit;
	
	for(i = 0; i < randomNumber; i++)
	{
		tmpBit = getAttributeOrGetBitFromRight(*byte,0);
		for(j = 0; j < (int)size ; j++)
		   byte[j] = byte[j] >> 1;
	    byte[size-1] = setAttributeOrBitFromRight(byte[size-1],BYTE_LENGTH-1,tmpBit);
	}
}
void xorTheValue(void* genaralVariable, size_t const size)
{
	unsigned char *b = ( unsigned char*) genaralVariable;
    int byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=BYTE_LENGTH-1;j>=0;j--)
        {
            byte = getAttributeOrGetBitFromRight(b[i],j);
			byte = byte ^1;
			b[i] = setAttributeOrBitFromRight(b[i],j,byte);
        }
    }
}
int getRandomNumber()
{
	int ran ;
    srand ((int)time(NULL) );
	ran = rand()%MAX_RANDOM_NUMBER+MIN_RANDOM_NUMBER;
	return ran;
}
void importNumberFromFile(int* number)
{

	FILE* f=  fopen(NAME_TEXT_FOR_RANDOM_NUMBER ,"r+");
	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		exit(0);
	}
	fscanf(f,"%d",number);
    fclose(f);
	
}
void invokeArgumentAndImportFile(char*  argv[],hotel_t* hotel)
{
	char* nameFile =(char*)argv[ARGUMENT_INDEX];
	importHotelDetailsFromFlie(hotel,nameFile);
}

