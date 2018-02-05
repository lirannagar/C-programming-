#include "DefinesValues.h"
#include "RoomStruct.h"
#include "HotelStruct.h"
#include "CustomerStruct.h"
#include "ReservationStruct.h"
#include "Functions.h"

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>


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
			//If the room taken print the details of the room
			printfValuesOfTheRoomIfTaken(&hotel->rooms[floorHotelCounter][roomHotelCounter]);
		}
	}
}
void initHotel(hotel_t* hotel,int* numebrOfFloors,int* numberOfRooms)
{
	int i;
	hotel->numberOfFloors = *numebrOfFloors;
	hotel->numberOfRooms = *numberOfRooms;
	hotel->rooms = (room_t**)malloc(hotel->numberOfFloors*sizeof(room_t*));
	for(i=0; i<hotel->numberOfFloors; i++)
	{
		hotel->rooms[i] = (room_t*)malloc(hotel->numberOfRooms*sizeof(room_t));
		hotel->rooms[i]->ifTaken =  CHECK_OUT;//Default 
	}
}
costomer_t addCustomer(int id, char* name,char numberCraditCard[] ,int yearValidCreditCard ,int monthValidCraditCard)
{
	//Create costomer
	costomer_t c ;
	c.idCostomer = id;
	c.name =  (char*)malloc(LENGTH_STRING* sizeof(char)); 
	checkMemoryState(c.name);
	strcpy(c.name,name);
	strcpy(c.numberCraditCard, numberCraditCard);
	c.yearValidCreditCard = yearValidCreditCard;
	c.monthValidCraditCard = monthValidCraditCard;
	return c;
}
void checkIn(hotel_t* hotel , reservation_t* res,costomer_t* costomer, int* counterCostomers,int* counterReservation)
{
	int i;
	int ifFound = FALSE;
	int IDCheck;
	char userOption; 
	int maxCustomer = hotel->numberOfFloors*hotel->numberOfRooms;
	costomer_t* tmpCostomer = costomer;
	//show all costomers in reservoir
	showAllCostomerInTheReservoir(counterCostomers,tmpCostomer );
	if(checkifThareIsNoCostomersAndAddCostomer(counterCostomers,costomer,&maxCustomer) == TRUE)
	{
		//When the user finish to add new costomer return to the manu
		printf("Returning to the manu...\n\n\n");
		return;
	}
	//User enter the costomer in the hotel
	printf("Please enter ID of costomer: \n");
	scanf("%d", &IDCheck);
	for(i = 0 ; i<(*counterCostomers) ; i++)
	{
		if(checkIfNameExistAndAddToReservation(res,&IDCheck,counterCostomers,costomer) ==  FALSE)
			costomer++;
		else
		{
			ifFound = TRUE;
			if(maxCustomer == *counterReservation)
				res = (reservation_t*)realloc(res,	((*counterReservation)+1) *sizeof(reservation_t));
			chackAvailableAndInsertReservation(res,hotel);
			(*counterReservation)++;
			break;
		}
	}
	//If the costomer not found the user need to choose if to add new one
	if(ifFound == FALSE)
	{
		printf("The costomer not found!\ndo you want to add it to the costomers list? (y/n)\n");
		getchar();//Clean the buffer
		scanf("%c",&userOption);
		initCostomer(costomer,counterCostomers,userOption,&maxCustomer);
	}	
}
void initCostomer(costomer_t* c,int* counterCostomers,char userOption, int* maxCustomers)
{
	int id=0;
	char* name = (char*)malloc(LENGTH_STRING* sizeof(char));
	char craditCardNumber[NUMBER_CRADIT_CARD];
	int validYearNumber = 0;
	int validMonthNumber = 0;
	
	checkMemoryState(name);
	if(*maxCustomers == *counterCostomers)
		c =(costomer_t*)realloc(c,((*counterCostomers)+1)*sizeof(costomer_t));
	switch(userOption)
	{
	case 'y':
	case 'Y':
		printf("Please enter number of ID:\n");
		scanf("%d",&id);
		printf("Please enter your name:\n");
		getchar();//Clean the buffer
		gets(name);		
		do
		{
			printf("Please enter your craditcard (number must be 12 digis):\n");
			scanf("%s",craditCardNumber);
		}
		while(checkValidCraditCard(craditCardNumber)== FALSE);
		do
		{
			printf("Please enter valid year craditcard (must be number between 2010-2020):\n");
			scanf("%d",&validYearNumber);
		}
		while(checkValidYear(&validYearNumber) == FALSE);
		do
		{
			printf("Please enter valid year month craditcard\n");
			scanf("%d",&validMonthNumber);
		}
		while(checkValidMonth(&validMonthNumber)==FALSE);
		*(c+(*counterCostomers)) = addCustomer(id,name,craditCardNumber,validYearNumber,validMonthNumber);
		free(name);
		(*counterCostomers)++;
		printf(".\n.\n.\n.\n.\nCostomer added successfully!\n\n\n");
		break;
	case 'n':
	case 'N':
		//return to the main
		printf("\nReturning to the manu...\n\n\n");
		break;
	}
}
int checkIfNameExistAndAddToReservation(reservation_t* r,int* IDChek,int* counterCostomers,costomer_t* costomer)
{
	//If the ID found, check him in
	if( *IDChek ==costomer->idCostomer )
	{
		printf("ID found!\n");
		do
		{
			printf("Please enter number of people inside room\n");
			scanf("%d",&r->numberOfPeopleInsideRoom);
		}
		while(checkValidNumberInsideRoom(&r->numberOfPeopleInsideRoom) == FALSE);
		do
		{
			printf("Please enter number of people that will eat breakfast\n");
			scanf("%d",&r->numberOfPeopleThatWillEatBreakfast);
		}
		while(checkValidNumberBreakfast(&r->numberOfPeopleThatWillEatBreakfast,&r->numberOfPeopleInsideRoom) == FALSE);
		r->ifChackOut = CHECK_IN;
		r->costomerPointer = *costomer;
		return TRUE;
	}
	return FALSE;
}
int checkifThareIsNoCostomersAndAddCostomer(int* counterCostomers,costomer_t* costomer,int* maxCustomer)
{
	char userOption; 
	if(*counterCostomers ==0)
	{
		printf("Thare is no costomers in the reservation list\ndo you want to add new One? (y/n)\n");
		getchar();//Clean the buffer
		scanf("%c",&userOption);
		initCostomer(costomer,counterCostomers,userOption,maxCustomer);
		return TRUE;
	}
	return FALSE;
}
void showAllCostomerInTheReservoir(int* counter,costomer_t* tmpCostomer )
{
	int i = 0; 
	while(i != *counter)
	{
		printf("ID: %d\n",tmpCostomer->idCostomer);
		toUpperCaseFirstChar(tmpCostomer->name);
		printf("Name: %s\n",tmpCostomer->name);
		printf("Cradit card: %s\n",tmpCostomer->numberCraditCard);
		printf("Year and month valid of cradit card: %d/%d\n",tmpCostomer->monthValidCraditCard, tmpCostomer->yearValidCreditCard);
		printf("--------------------------------------------------------\n");
		tmpCostomer++;
		i++;
	}
}
void chackAvailableAndInsertReservation(reservation_t* res,hotel_t* hotel)
{
	int floorHotelCounter;
	int roomHotelCounter;
	int numberOfFloor = hotel->numberOfFloors;
	int numberOfRooms = hotel->numberOfRooms;
	int counterForCheckIfTheHotelFull = 0;
	int maxRooms = hotel->numberOfFloors*hotel->numberOfRooms;

	for(floorHotelCounter = 0; floorHotelCounter<numberOfFloor ; floorHotelCounter++)
	{
		for(roomHotelCounter = 0; roomHotelCounter< numberOfRooms ;roomHotelCounter++ )
		{	
			//If the room not taken put the reservation inside the room and mark the room as taken
			if(hotel->rooms[floorHotelCounter][roomHotelCounter].ifTaken != CHECK_IN)
			{
				hotel->rooms[floorHotelCounter][roomHotelCounter].numberPeopleInsideRoom = res ->numberOfPeopleInsideRoom;
				hotel->rooms[floorHotelCounter][roomHotelCounter].numberPeopleRegisteredBreakfast = res ->numberOfPeopleThatWillEatBreakfast;
				hotel->rooms[floorHotelCounter][roomHotelCounter].ifTaken = CHECK_IN;
				if(roomHotelCounter < MAX_TO_PRINT_ZERO)
					printf("\nThe costomer added to the room - [%d0%d] \n",floorHotelCounter,roomHotelCounter);
				else
					printf("\nThe costomer added to the room - [%d%d] \n",floorHotelCounter,roomHotelCounter);
				//break becouse no need to chack the aether rooms
				return;
			}else
				counterForCheckIfTheHotelFull++;
		}
	}
	//If all rooms are full print this message
	if(counterForCheckIfTheHotelFull == maxRooms)
		printf("Thare is no availble room in this hotel\n");
}
void toUpperCaseFirstChar(char str[])
{
	//Check if the first latter is LowerCase and then switch to UpperCase
	if(MIN_ASCII_NUMBER_LOWER_CASE <= str[0] &&  str[0]<= MAX_ASCII_NUMBER_LOWER_CASE )
		str[0]= str[0] - NUMBER_TO_UPDATE_FIRST_CHAR_STRING;
}
void printfValuesOfTheRoomIfTaken(room_t* roomChecker)
{
	int numberPersons;
	int numberOfPersonRegisteredBreakfast;

	if(roomChecker->ifTaken  == CHECK_IN)
	{
		printf("The room  taken!\n");
		numberPersons = roomChecker->numberPeopleInsideRoom;
		numberOfPersonRegisteredBreakfast =  roomChecker->numberPeopleRegisteredBreakfast;
		//Print how many persons in the room and how many registered breakfast
		printf("%d persons in the room\n", numberPersons);
		printf("%d persons who registered breakfast\n",numberOfPersonRegisteredBreakfast);
		
	}
	else
		printf("The room not taken!\n");
	printf("\n\n");
}
void  checkOut(hotel_t* hotel)
{
	int numberOfFloor;
	int numberOfRoom;
	
	do
	{
	printf("Please enter number of the floor:\n");
	scanf("%d",&numberOfFloor);
	}
	while(numberOfFloor>hotel->numberOfFloors);
	do
	{
	printf("Please enter numebe of room:\n");
	scanf("%d",&numberOfRoom);
	}
	while(numberOfRoom> hotel->numberOfRooms);	
	if( hotel->rooms[numberOfFloor][numberOfRoom].ifTaken  !=  CHECK_OUT)
	{
	hotel->rooms[numberOfFloor][numberOfRoom].ifTaken = CHECK_OUT;
	printf("Action succeeded!\n\n");
	}
	else
		printf("This room is already empty!\n\n");
}
void printRoomDetails(hotel_t* hotel, reservation_t* res)
{
	int numberOfFloor;
	int numberOfRoom;
	
	printf("Please enter number of the floor:\n");
	scanf("%d",&numberOfFloor);
	printf("Please enter numebe of room:\n");
	scanf("%d",&numberOfRoom);
	
	if(hotel->rooms[numberOfFloor][numberOfRoom].ifTaken == CHECK_OUT)
	{
		if(numberOfRoom<MAX_TO_PRINT_ZERO)
			printf("Room number %d0%d is empty!\n",numberOfFloor,numberOfRoom );
		else
			printf("Room number %d%d is empty!\n",numberOfFloor,numberOfRoom );
	}
	else
	{
		res->roomPointer = hotel->rooms[numberOfFloor][numberOfRoom];
		printf("Number of persons inside the room is: %d\n", hotel->rooms[numberOfFloor][numberOfRoom].numberPeopleInsideRoom);
		printf("Number of persons registered breakfast the room is: %d\n", hotel->rooms[numberOfFloor][numberOfRoom].numberPeopleRegisteredBreakfast);
		printf("The room owner is:\n");
		printf("ID: %d\n",res->costomerPointer.idCostomer);
		printf("Name: %s\n",res->costomerPointer.name);
		printf("CraditCard: %s\n",res->costomerPointer.numberCraditCard);
		printf("Valid : %d/%d\n\n",res->costomerPointer.monthValidCraditCard,res->costomerPointer.yearValidCreditCard);
	}

}
costomer_t* findSubstringName(char str[], costomer_t* costomer,int* counterCostomer,int* costomerSubstingCounter)
{
	int i;
	costomer_t* substringCus =NULL;
	
	if(*counterCostomer == 0)
	{
		printf("Thare is no customers in the hotel!\nReturning to manu...\n\n");
		return NULL;
	}
	substringCus = (costomer_t*)calloc(*counterCostomer, sizeof(costomer_t));
	checkMemoryState(substringCus);
	if(*counterCostomer == *counterCostomer )
	{
		substringCus =(costomer_t*)realloc(substringCus,((*counterCostomer)+1) *sizeof(costomer_t));
	}
	for(i = 0; i< *counterCostomer; i++)
	{
		char *value = strstr((costomer+i)->name ,str);
		if(value != NULL)
		{
			*(substringCus+*costomerSubstingCounter) = 	*(costomer+i);
			(*costomerSubstingCounter)++;
		}
	}
	return substringCus;
}
void printfCostomerSubstring( costomer_t* costomerSubsting,int* costomerSubstingCounter)
{
	int i;
	
	printf("The list of the costomers are:\n");
	for(i = 0; i < *costomerSubstingCounter; i++)
	{
		printf("ID: %d\n",(costomerSubsting+i)->idCostomer);
		printf("Name: %s\n",(costomerSubsting+i)->name);
	}
	(*costomerSubstingCounter)= 0;// Reset the counter of the substring customers
	

}
void checkMemoryState(void* allocatedArray)
{
	if(!allocatedArray)// (allocatedArray == NULL) --> allocaton didn't succeed
	{
		printf("ERROR! Out of memory!\n");
		return;
	}
}
int checkValidCraditCard(char craditCardNumberChecker[])
{
	int numberDigits = strlen(craditCardNumberChecker);
	if(numberDigits == (NUMBER_CRADIT_CARD-1))
		return TRUE;
	return FALSE;
}
int checkValidYear(int* validYearNumberChecker)
{
	if(MIN_VALID_YEAR <= *validYearNumberChecker && *validYearNumberChecker <= MAX_VALID_YEAR)
		return TRUE;
	return FALSE;
}
int checkValidMonth(int* validMonthNumberChecker)
{
	if(MIN_VALID_MONTH <= *validMonthNumberChecker && *validMonthNumberChecker <= MAX_VALID_MONTH)
		return TRUE;
	return FALSE;
}
int checkValidNumberInsideRoom(int* numberPersonsInsideRoomChecker)
{
	if(MIN_NUMBER_OF_PERSONS<= *numberPersonsInsideRoomChecker && *numberPersonsInsideRoomChecker <=MAX_NUMBER_OF_PERSONS)
		return TRUE;
	return FALSE;
}
int checkValidNumberBreakfast(int* numberPersonsBreakfastChecker,int* numberInsideTheRoom)
{
	if(MIN_REGISTERED_BREAKFAST <= *numberPersonsBreakfastChecker && *numberPersonsBreakfastChecker <= *numberInsideTheRoom)
		return TRUE;
	return FALSE;
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
void freeMemory(hotel_t* hotel,costomer_t* costomer ,reservation_t* res,costomer_t* costomerSubsting , int* counterCustomer)
{
	int i ;
	//Free name allocated
	for(i=0; i< *counterCustomer; i++)
		free((costomer+i)->name);
	//Free customers array
	free(costomer);
	//Free reservations array
	free(res);
	//Free sunstring customers array
	free(costomerSubsting);
	//Free hotel
	for(i=0; i<hotel->numberOfFloors; i++)
		free(hotel->rooms[i]);
	free(hotel->rooms);
	printf("Bye bye!\n");
}