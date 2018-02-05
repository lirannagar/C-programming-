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


void openAllocatedMemoryToTheHotel(hotel_t* hotel,int* numebrOfFloors,int* numberOfRooms)
{
	int i;
	hotel->numberOfFloors = *numebrOfFloors;
	hotel->numberOfRooms = *numberOfRooms;
	hotel->rooms = (room_t**)malloc(hotel->numberOfFloors*sizeof(room_t*));
	for(i=0; i<hotel->numberOfFloors; i++)
	{
		hotel->rooms[i] = (room_t*)malloc(hotel->numberOfRooms*sizeof(room_t));
		//Default values
		hotel->rooms[i]->attributes=0;
		hotel->rooms[i]->numberOfBeds=0;
	}
}
void initHotel(hotel_t* hotel,int* numebrOfFloors,int* numberOfRooms)
{
	int counterFloorHotel;
	int counterRoomHotel;
	for(counterFloorHotel =0; counterFloorHotel< hotel->numberOfFloors; counterFloorHotel++)
	{
		printf("Floor number #%d\n--------------------------------------------\n",counterFloorHotel);
		for(counterRoomHotel = 0; counterRoomHotel< hotel->numberOfRooms; counterRoomHotel++)
		{
			if(counterRoomHotel<MAX_TO_PRINT_ZERO)
				printf("Please init values for room number [%d0%d]\n",counterFloorHotel,counterRoomHotel);
			else
				printf("Please init values for room number [%d%d]\n",counterFloorHotel,counterRoomHotel);
			initRoom(&hotel->rooms[counterFloorHotel][counterRoomHotel]);	
		}
	}
}
int checkValidNumberOfFloors(int* numebrOfFloors)
{
	if( *numebrOfFloors> MAX_NUMBER_OF_FLOORS ||  *numebrOfFloors<=0)
		return FALSE;
	return TRUE;
}
int checkValidNumberOfRooms(int* numebrOfRooms)
{
	if( *numebrOfRooms> MAX_NUMBER_OF_ROOMS || *numebrOfRooms<=0)
		return FALSE;
	return TRUE;
}
int checkValidAttributeFromUser(int* attributeOption)
{
	if(0> *attributeOption  || *attributeOption> TV_BIT )
		return FALSE;
	return TRUE;
}
void showHotelStatus(hotel_t* hotel)
{
	int floorHotelCounter;
	int roomHotelCounter;

	printf("\n\nHotel details:\n");
	for(floorHotelCounter = 0; floorHotelCounter<hotel->numberOfFloors ; floorHotelCounter++)
	{
		printf("Floor number #%d\n------------------------------------------\n",floorHotelCounter);
		for(roomHotelCounter = 0; roomHotelCounter < hotel->numberOfRooms ;roomHotelCounter++ )
		{	
			if(roomHotelCounter<MAX_TO_PRINT_ZERO)
				printf("Room number [%d0%d]\n",floorHotelCounter,roomHotelCounter);
			else
				printf("Room number [%d%d]\n",floorHotelCounter,roomHotelCounter);
			//print rooms details
			printRoom(&hotel->rooms[floorHotelCounter][roomHotelCounter]);
		}
	}
}
void getAttributeFromTheFirstFloor(hotel_t* hotel)
{
	int numberAttribute = PORCH_BIT;

		if(hotel->numberOfRooms>=MAX_NUMBER_TO_CHECK_ROOM)	
			showRoomWithPorchAndAttribute(numberAttribute,&hotel->rooms[FIRST_FLOOR][FIRST_ROOM],&hotel->rooms[FIRST_FLOOR][SECOND_ROOM],&hotel->rooms[FIRST_FLOOR][THIRD_ROOM],NULL);
	
}
void encryptAndSaveToFileDetailsHotel(hotel_t* hotel)
{
	int floorHotelCounter;
	int roomHotelCounter;
	FILE* hotelDetailsFile =  fopen(HOTEL_NAME_SAVE_FILE ,"wb");
	fwrite(&hotel->numberOfFloors, sizeof(int), 1, hotelDetailsFile);
	fwrite(&hotel->numberOfRooms, sizeof(int), 1, hotelDetailsFile);
	for(floorHotelCounter = 0; floorHotelCounter<hotel->numberOfFloors ; floorHotelCounter++)
	{
		for(roomHotelCounter = 0; roomHotelCounter < hotel->numberOfRooms ;roomHotelCounter++ )
		{	
			hotel->rooms[floorHotelCounter][roomHotelCounter].attributes = encryptMethod(&hotel->rooms[floorHotelCounter][roomHotelCounter].attributes,sizeof(hotel->rooms[floorHotelCounter][roomHotelCounter].attributes));
			fwrite(&hotel->rooms[floorHotelCounter][roomHotelCounter], sizeof(room_t), 1, hotelDetailsFile);
		}
	}
	fclose(hotelDetailsFile);
}
void initAttributeToShowDetails(hotel_t* hotel)
{
	int attributeOption;
	do
	{
	printf("Please enter attribute number:\nTo show witch room available has veiw to the pool press 0\nTo show witch room available has porch press 1\nTo show witch room available has kettle press 2\nTo show witch room available has free wifi press 3\nTo show witch room available has extend couch press 4\nTo show witch room available has TV press 5\n\n\n\n");
	scanf("%d",&attributeOption);
	}while(checkValidAttributeFromUser(&attributeOption) == FALSE );
	printRoomAvalibleWithAttribute(hotel,attributeOption);
}
void importHotelDetailsFromFlie(hotel_t* hotel,char* nameFile)
{

	FILE* hotelDetailsFile =  fopen(nameFile, "rb");	
	int floorHotelCounter;
	int roomHotelCounter;
	fread(&hotel->numberOfFloors, sizeof(int), 1, hotelDetailsFile);
	fread(&hotel->numberOfRooms, sizeof(int), 1, hotelDetailsFile);
	openAllocatedMemoryToTheHotel(hotel,&hotel->numberOfFloors,&hotel->numberOfRooms);
	for(floorHotelCounter = 0; floorHotelCounter< hotel->numberOfFloors ; floorHotelCounter++)
	{
		for(roomHotelCounter = 0; roomHotelCounter < hotel->numberOfRooms ;roomHotelCounter++ )
		{	
			fread(&hotel->rooms[floorHotelCounter][roomHotelCounter], sizeof(room_t), 1, hotelDetailsFile);
			hotel->rooms[floorHotelCounter][roomHotelCounter].attributes = decryptMethod(&hotel->rooms[floorHotelCounter][roomHotelCounter].attributes,sizeof(hotel->rooms[floorHotelCounter][roomHotelCounter].attributes) );
		}
	}
	fclose(hotelDetailsFile);
}
void initFloorsAndRooms(int* numebrOfFloors,int* numberOfRooms)
{
	do
	{
		printf("Please eneter numebr of floors:\n");
		scanf("%d",numebrOfFloors);
	}
	while(checkValidNumberOfFloors(numebrOfFloors)==FALSE);
	do
	{
		printf("Please eneter numebr of rooms:\n");
		scanf("%d",numberOfRooms);
	}
	while(checkValidNumberOfRooms(numberOfRooms)==FALSE);
}
void freeAllocatedMemoryForHotel(hotel_t* hotel)
{
	int i;
	for(i=0; i<hotel->numberOfFloors; i++)
		free(hotel->rooms[i]);
	free(hotel->rooms);
	printf("Bye bye\n");
	system("pause");
}

