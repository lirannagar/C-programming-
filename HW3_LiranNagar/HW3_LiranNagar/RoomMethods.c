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



void printRoom(room_t* room)
{
	printf("Number of beds; %d \n", room->numberOfBeds);
	//Print if taken
	if( getAttributeOrGetBitFromRight(room->attributes,AVAILABLE_BIT)== TRUE)
		printf("The room is available\n");
	else
		printf("The room is not available\n");
	//Print if thare is TV
	if( getAttributeOrGetBitFromRight(room->attributes,TV_BIT)== TRUE)
		printf("Thare is TV in this room\n");
	else
		printf("Thare is no TV in this room\n");
	//Print if couch
	if( getAttributeOrGetBitFromRight(room->attributes,EXTENT_COUCH)== TRUE)
		printf("Thare is extend couch in this room\n");
	else
		printf("Thare is no extend couch in this room\n");
	//Print if taken
	if(getAttributeOrGetBitFromRight(room->attributes,FREE_WIFI_BIT)== TRUE)
		printf("Thare is free wifi in this room\n");
	else
		printf("Thare is no free wifi in this room\n");
	//Print if kettle
	if(getAttributeOrGetBitFromRight(room->attributes,KETTLE_BIT)== TRUE)
		printf("Thare is  kettle in this room\n");
	else
		printf("Thare is no kettle in this room\n");
	//Print if porch
	if(getAttributeOrGetBitFromRight(room->attributes,PORCH_BIT)== TRUE)
		printf("Thare is a porch in this room\n");
	else
		printf("Thare is no porch in this room\n");
	//Print if veiw to the pool
	if(getAttributeOrGetBitFromRight(room->attributes,VIEW_BIT)== TRUE)
		printf("Thare is a veiw to the pool in this room\n");
	else
		printf("Thare is no veiw to the pool in this room\n");
}
void initRoom(room_t* room)
{
	int numberBeds =0;
	int ifVeiwToThePool  = 0;
	int ifThareIsPorch = 0;
	int ifThareIsKettle= 0;
	int ifThareIsFreeWifi= 0;
	int ifThareIsExtendCouch = 0;
	int ifThareIsTV= 0;
	int ifTaken = 0;
	
	do
	{
	printf("Please enter how many beds in the room\n");
	scanf("%d",&numberBeds);
	room->numberOfBeds = numberBeds;
	printf("Please press 1 if thare is veiw to the pool or 0 if not\n");
	scanf("%d",&ifVeiwToThePool);
	room->attributes= setAttributeOrBitFromRight(room->attributes,VIEW_BIT,ifVeiwToThePool);
	printf("Please press 1 if thare is a porch or 0 if not\n");
	scanf("%d",&ifThareIsPorch);
	room->attributes = setAttributeOrBitFromRight(room->attributes,PORCH_BIT,ifThareIsPorch);
	printf("Please press 1 if thare is a kettle or 0 if not\n");
	scanf("%d",&ifThareIsKettle);
	room->attributes = setAttributeOrBitFromRight(room->attributes,KETTLE_BIT,ifThareIsKettle);
	printf("Please press 1 if thare is free wifi or 0 if not\n");
	scanf("%d",&ifThareIsFreeWifi);
	room->attributes = setAttributeOrBitFromRight(room->attributes,FREE_WIFI_BIT,ifThareIsFreeWifi);
	printf("Please press 1 if thare is extend couch or 0 if not\n");
	scanf("%d",&ifThareIsExtendCouch);
	room->attributes = setAttributeOrBitFromRight(room->attributes,EXTENT_COUCH,ifThareIsExtendCouch);
	printf("Please press 1 if the room is  available 0 if not\n");
	scanf("%d",&ifTaken);
	room->attributes = setAttributeOrBitFromRight(room->attributes,AVAILABLE_BIT,ifTaken);
	printf("Please press 1 if the room is  TV in the room or  0 if not\n");
	scanf("%d",&ifThareIsTV);
	room->attributes = setAttributeOrBitFromRight(room->attributes,TV_BIT,ifThareIsTV);
	}while(checkValidInputsRoom(&ifVeiwToThePool,&ifThareIsPorch,&ifThareIsKettle,&ifThareIsFreeWifi,&ifThareIsExtendCouch,&ifThareIsTV,&ifTaken, &numberBeds) == FALSE);
}
int checkValidInputsRoom(int* ifVeiwToThePool, int* ifThareIsPorch, int* ifThareIsKettle, int* ifThareIsFreeWifi, int* ifThareIsExtendCouch, int* ifThareIsTV, int* ifTaken, int* numberBeds)
{

	//CheckIfOneOfTheValuesWhong
	if(((*ifVeiwToThePool != 0) && (*ifVeiwToThePool != 1))
		||((*ifThareIsPorch != 0) && (*ifThareIsPorch != 1)) 
		||((*ifThareIsKettle != 0) && (*ifThareIsKettle != 1)) 
		||((*ifThareIsFreeWifi != 0) && (*ifThareIsFreeWifi != 1)) 
		||((*ifThareIsExtendCouch != 0) && (*ifThareIsExtendCouch != 1)) 
		||((*ifThareIsTV != 0) && (*ifThareIsTV != 1))
		||((*ifTaken != 0) && (*ifTaken != 1))  
		||(numberBeds<=0) )
	{
		printf("Whorng input!\nPlease try again...\n\n");
		return FALSE;
	}
	return TRUE;
}
void printRoomAvalibleWithAttribute(hotel_t* hotel,int attribute)
{
	int floorHotelCounter;
	int roomHotelCounter;
	int counterIfNoFoundRoom = 0;
	printf("\n\nHotel details:\n");
	for(floorHotelCounter = 0; floorHotelCounter<hotel->numberOfFloors ; floorHotelCounter++)
	{
		printf("Floor number #%d\n------------------------------------------\n",floorHotelCounter);
		for(roomHotelCounter = 0; roomHotelCounter < hotel->numberOfRooms ;roomHotelCounter++ )
		{	
			//check if thare is available room and a positive attribute
			if( ifThareIsAttributesAndAvailableRoom(hotel->rooms[floorHotelCounter][roomHotelCounter].attributes,attribute) == TRUE)
			{
				if(roomHotelCounter<MAX_TO_PRINT_ZERO)
					printf("Room number [%d0%d]\n",floorHotelCounter,roomHotelCounter);
				else
					printf("Room number [%d%d]\n",floorHotelCounter,roomHotelCounter);
				counterIfNoFoundRoom++;
			}
		}
	}
	if(counterIfNoFoundRoom == 0)
		printf("No room found!\n\n");
}
int ifThareIsAttributesAndAvailableRoom(unsigned char attributeChecker,int attribute)
{
	if((getAttributeOrGetBitFromRight(attributeChecker, AVAILABLE_BIT) ==  AVAILABLE_ROOM) &&  (getAttributeOrGetBitFromRight(attributeChecker, attribute)==TRUE))
		return TRUE;
	return FALSE;
}
void showRoomWithPorchAndAttribute( int attribute ,room_t* room,...)
{
	va_list allRooms = NULL;
	room_t* currentRoom =  NULL;
	int counterList = 0;
	va_start(allRooms,room);
	currentRoom = room;
	while (currentRoom != NULL)	
	{	
		if(getAttributeOrGetBitFromRight(currentRoom->attributes,attribute) == TRUE )
			printf("Room number #%d in the list has a porch\n",counterList);
		counterList++;
		currentRoom = va_arg(allRooms, room_t*);
	}
	va_end(allRooms);
}
int getAttributeOrGetBitFromRight(unsigned char ch, int index)
{
	unsigned char mask = 1; 
	mask = mask << index;

	if ((ch & mask) == 0)
		return 0;
	else 
		return 1;
}
char setAttributeOrBitFromRight(unsigned char ch, int index, int value)
{
	unsigned char mask = 1; 
	unsigned char result;
	mask  <<= index;

	if (value == 1)
		result = ch | mask;
	else
	{
		mask = ~mask;
		result = ch & mask;
	}
	return result ;
}


