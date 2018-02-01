
#define _CRT_SECURE_NO_WARNINGS 
#define LENGTH_STRING 4
#define TRUE  1
#define MAX_OPTION 5
#define MIN_OPTION 1
#define EXIT_OPTION -1
#define ARRAY_SIZE 10
#define MATRIX_ROW_AND_COL 10
#define TRAVERSE_ROWS_FIRST 0
#define TRAVERSE_COLUMN_FIRST 1
#define STRING_LENGTH 10


#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "QuestionsMethods.h"


void main()
{
	int numberQuestion;
	while(TRUE)
	{
		printf("Please choose one's of the opetion %d - %d:\n(1) - to Question number one\n(2) - to question number two\n(3) - to question number three\n(4) - "
			"to question number four\n(5) - to question number five\n(-1) - Exit\n", MIN_OPTION,MAX_OPTION);
		scanf("%d", &numberQuestion);
		if(numberQuestion <= MAX_OPTION && numberQuestion >= EXIT_OPTION) //Chack valid input from user
		{
			switch(numberQuestion)
			{
			case 1:
				questionOne();
				break;
			case 2:
				questionTwo();
				break;
			case 3:
				questionThree();
				break;
			case 4:
				questionFour();
				break;
			case 5:
				questionFive();
				break;
			case -1:
				printf("Bye bye!\n");
					system("pause");
					return;
				
			}
		}
		else
			printf("Option must be between %d and %d\n",MIN_OPTION ,MAX_OPTION);
	}

}

void questionOne()
{
	int matix[MATRIX_ROW_AND_COL][MATRIX_ROW_AND_COL];
	int arr[ARRAY_SIZE];
	int jumpSize = 0;
	int number = 0;
	int i;
	char option;
	do
	{
	printf("Please choose section (A/B)\n");
	getchar(); //clean the buffer
	scanf("%c", &option);
	}while(!(('A'==option)|| ('B'==option) || ('a'==option)|| ('b'==option) )); //Chack valid input from user
	switch(option){
	case 'A':
	case 'a':
		printf("Please enter number:\n");
		scanf("%d",&number);
		printf("Please enter jump number:\n");
		scanf("%d",&jumpSize);
		//Init array with values in jump places
		initArray(arr ,jumpSize,number,ARRAY_SIZE);
		break;
	case 'B':
	case 'b':
		//Init matrix with values
		for(i = 0; i<MATRIX_ROW_AND_COL ; i++)
		{
			initArray(*(matix+i),1,i,MATRIX_ROW_AND_COL);
		}
		//Print the Matrix
		printIntMatrix((int*)matix, MATRIX_ROW_AND_COL, MATRIX_ROW_AND_COL, TRAVERSE_COLUMN_FIRST);
		break;

	}


}

void questionTwo()
{	
	int matrix[MATRIX_ROW_AND_COL][MATRIX_ROW_AND_COL];
	int i,j=0,k=0;
	int size = MATRIX_ROW_AND_COL;
	//Fill the matrix with zeros
	for(i = 0; i<MATRIX_ROW_AND_COL ; i++)
	{
		initArray(*(matrix+i),1,0,size);
	}
	//Fill the matrix with values
	for(i = 0; i <MATRIX_ROW_AND_COL; i++ )
	{
		initArray(*(matrix+i)+i, 1, (i+1),size);
		size--;
	}

	//Print the Matrix
	printIntMatrix((int*)matrix, MATRIX_ROW_AND_COL, MATRIX_ROW_AND_COL, TRAVERSE_ROWS_FIRST);






}

void questionThree()
{

	char str[STRING_LENGTH];
	char tav;
	printf("Please eneter a String\n" );
	scanf("%s", str);
	getchar();//clean the buffer
	printf("Please enter a Char\n");
	scanf("%c", &tav);
	printIndexOfNumbersChar(str,tav);
	
}

void questionFour()
{
	char* strArray[LENGTH_STRING] = {{"adam"},{"gavrieli"},{"liran"},{"nagar"}};
	printf("Strings before sorting\n");
	printStringArray(strArray,LENGTH_STRING);
	sortStringArray(strArray);
	printf("Strings after sorting\n");
	printStringArray(strArray,LENGTH_STRING);
}

void questionFive()
{
	char str[] = "$hello  world";
	char delimiters[] = "$ ";
	char *token;
	token = myStrtok(str,delimiters);
	while(token != NULL)
	{
		printf( "%s\n", token );
		token = myStrtok(NULL, delimiters);
	}

}

char* myStrtok(char* str, char* delimiters)
{
	static char *permanentStr; 
	static int positionIndex =0 ; 
	int j,start=positionIndex; 
	if(str!=NULL) 
		permanentStr=str; 
	while(permanentStr[positionIndex]!='\0') 
	{ 
		j=0; 
		while(delimiters[j]!='\0') 
		{ 
			if(permanentStr[positionIndex]==delimiters[j]) 
			{ 
				permanentStr[positionIndex]= '\0'; 
				positionIndex++; 
				if(permanentStr[start]!='\0') 
					return &permanentStr[start]; 
				else 
				{ 
					start=positionIndex; 
					positionIndex--; 
					break; 
				} 
			} 
			j++; 
		} 
		positionIndex++; 
	} 
	permanentStr[positionIndex]='\0'; 
	if(permanentStr[start]=='\0') 
	{
		//End the method and reset the static values for the next entery
		*permanentStr =' ';
		positionIndex =0;
		return NULL; 
	}
	else 
		return &permanentStr[start]; 
}

void initArray(int* arr,int jumpSize,int number, int size)
{
	int *p;
	int index=0;
	for(p =arr; p <arr+size; p++)
	{
		if(index%jumpSize ==0)
		{
			*p = number;
		}
		index++;
	}
}



void printIndexOfNumbersChar(char str[], char tav)
{
	char* pos = str;
	int index = 0;
	while(TRUE)
	{ 
		pos = strchr(str, tav);
		//when there is no char in the String end the loop
		if(pos == NULL)
			break;
		index += (pos-str)+1;
		printf("The char %c preformed at index: %d\n",tav,index);
		strcpy(str, pos);
		str++;
	}
	//if the char not found in this String
	if(index==0)
		printf("The char %c is not in this String\n",tav );
}

void sortStringArray(char** strArray )
{
	char *tmp;
	int i=0, j =0;
	int secondLength;
	int firstLength;
	while(i != LENGTH_STRING)
	{
		firstLength = strlen(*(strArray+i));
		j = i+1;
		while(j != LENGTH_STRING)
		{
			secondLength = strlen(*(strArray+j));
			if(firstLength > secondLength)
			{
				 tmp = *(strArray+i);
				*(strArray+i) = *(strArray+j);
				*(strArray+j) = tmp;
			}
			j++;
			secondLength=0;
		}
		j=0;
		i++;
	}
}

void printStringArray(char** str,int size)
{
	int i=0;
	while(i != size)
	{
		printf("%s\n",*(str+i));
		i++;
	}


}

void printIntMatrix(int *matrix_start, int amount_rows, int amount_columns, int traverse_order)
{
	int row_index = 0, column_index = 0;

	if (traverse_order == TRAVERSE_ROWS_FIRST)
	{
		for (; row_index < amount_rows; row_index++)
		{
			for (; column_index < amount_columns; column_index++)
			{
				printf_s("%d ", matrix_start[row_index * amount_rows + column_index]);
			}
			column_index = 0;

			printf_s("\n");
		}
	}

	else
	{
		for (; column_index < amount_columns; column_index++)
		{
			for (; row_index < amount_rows; row_index++)
			{
				printf_s("%d ", matrix_start[row_index * amount_rows + column_index]);
			}
			row_index = 0;

			printf_s("\n");
		}
	}
}