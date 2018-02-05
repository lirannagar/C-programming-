
#include "DefinseValues.h"
#include "RoomStruct.h"
#include "HotelStruct.h"
#include "FanctionDecleretions.h"


#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>




void main(int  argc, char*  argv[])
{
	hotel_t hotel;
	int numberOfFloor=0;
	int numberOfRooms=0;
	int option;
	
	printf("**********************WELCOME TO THE HOTEL ! ! ! **********************\n");
    if(argc == ARGUMENT_NUMBER)
		invokeArgumentAndImportFile(argv,&hotel);
	else
	{
		//Init number floors and rooms
		initFloorsAndRooms(&numberOfFloor,&numberOfRooms);
		//Allocate memory
		openAllocatedMemoryToTheHotel(&hotel,&numberOfFloor,&numberOfRooms);
		//User init hotel
		initHotel(&hotel,&numberOfFloor,&numberOfRooms);
	}
	//Check specific attribute for three room on the first floor
	getAttributeFromTheFirstFloor(&hotel);
	//Start manu
	while(TRUE)
	{
		printf("\nPlease choose one of the aboves: \n  1) Print details of hotel\n  2) Print hotel available rooms with attribute\n -1) to Exit\n");
		scanf("%d",&option);
		switch(option)
		{   
		case FIRST_OPETION_NUMBER:
			showHotelStatus(&hotel);
			break;
		case SECOND_OPETION_NUMBER:
			initAttributeToShowDetails(&hotel);	
			break;
		case EXIT_OPETION_NUMBER:
			encryptAndSaveToFileDetailsHotel(&hotel);
			freeAllocatedMemoryForHotel(&hotel);
			return;
		}
	}
}