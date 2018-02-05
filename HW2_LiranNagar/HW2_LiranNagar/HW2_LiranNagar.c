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


void main()
{
	hotel_t hotel;
	costomer_t* costomerArr;	
	reservation_t* reservationArr;
	costomer_t* costomerSubsting =  NULL;
	int counterCostomers = 0;
	int counterReservation = 0;
	int costomerSubstingCounter=0;
	int option;
	int numebrOfFloors;
	int numberOfRooms;
	char strInput[LENGTH_STRING];
	char optionIfAddCostomer;
	int maxCustomers = 0;

	printf("**********************WELCOME TO THE HOTEL ! ! ! **********************\n");
	do
	{
	printf("Please eneter numebr of floors:\n");
	scanf("%d",&numebrOfFloors);
	}
	while(checkValidNumberOfFloors(&numebrOfFloors)==FALSE);
	do
	{
	printf("Please eneter numebr of rooms:\n");
	scanf("%d",&numberOfRooms);
	}
	while(checkValidNumberOfRooms(&numberOfRooms)==FALSE);
	initHotel(&hotel,&numebrOfFloors,&numberOfRooms);
	maxCustomers = hotel.numberOfFloors*hotel.numberOfRooms;
	printf("Hotel has created!\n\n");


	//Initialize Costomer and reservation arrays
	reservationArr = (reservation_t*)calloc(maxCustomers, sizeof(reservation_t));
	costomerArr  = (costomer_t*)calloc(maxCustomers, sizeof(costomer_t));
	checkMemoryState(reservationArr);
	checkMemoryState(costomerArr);
	while(TRUE)
	{
		printf("Please choose one of the opetions:\n 1 - Show hotel status\n 2 - Add costomer\n 3 - CheckIn costomer\n 4 - CheckOut\n 5 - Room details\n 6 - Find Substring name of costomer\n-1 - Exit\n");
		scanf("%d",&option);
		switch(option)
		{
		case 1:
			showHotelStatus(&hotel);
			break;
		case 2:
			printf("Are you sure you want to add new customer? (y/n)\n");
			scanf(" %c",&optionIfAddCostomer);
			initCostomer(costomerArr,&counterCostomers,optionIfAddCostomer,&maxCustomers);
			break;
		case 3:
			checkIn(&hotel,reservationArr+counterReservation,costomerArr,&counterCostomers,&counterReservation);
			break;
		case 4:
			checkOut(&hotel);
			break;
		case 5:
			printRoomDetails(&hotel,reservationArr);
			break;
		case 6:
			printf("Please enetr a String:\n");
			getchar();//Clean the buffer
		    gets(strInput);	
			costomerSubsting  = findSubstringName(strInput,costomerArr,&counterCostomers,&costomerSubstingCounter );
			printfCostomerSubstring(costomerSubsting,&costomerSubstingCounter);
			break;	
		case -1:
			//Free the allocated memory and then exit the program
			freeMemory(&hotel,costomerArr,reservationArr ,costomerSubsting, &counterCostomers );
			system("pause");
			return;
		}
	}
}


