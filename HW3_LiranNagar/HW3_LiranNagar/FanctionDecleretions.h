#ifndef __FANCTIONSDECLERETIONS__
#define __FANCTIONSDECLERETIONS__


#include <stdio.h>




void initRoom(room_t* room);
void printRoom(room_t* room);
void openAllocatedMemoryToTheHotel(hotel_t* hotel,int* numebrOfFloors,int* numberOfRooms);
void initHotel(hotel_t* hotel,int* numebrOfFloors,int* numberOfRooms);
void showHotelStatus(hotel_t* hotel);
int checkValidNumberOfFloors(int* numebrOfFloors);
int checkValidNumberOfRooms(int* numebrOfRooms);
void printRoomAvalibleWithAttribute(hotel_t* hotel,int attribute);
char setAttributeOrBitFromRight(unsigned char ch, int index, int value);
int findAttribute(unsigned char ch, int index);
void showRoomWithPorchAndAttribute( int attribute,room_t* room,...);
int getAttributeOrGetBitFromRight(unsigned char ch, int index);
int getRandomNumber();
char encryptMethod(void*  genaralVariable, int numberOfBytes );
void shiftRightCircle(void* genaralVariable, size_t const size,int randomNumber );
char decryptMethod(void* genaralVariable, int numberOfBytes);
void shiftLeftCircle(void* genaralVariable , size_t const size,int randomNumber );
void encryptAndSaveToFileDetailsHotel(hotel_t* hotel);
void importHotelDetailsFromFlie(hotel_t* hotel,char* nameFile);
void initAttributeToShowDetails(hotel_t* hotel);
int ifThareIsAttributesAndAvailableRoom( unsigned char attributeChecker,int attribute);
char swapVariableWithRandomNumber(unsigned char* variable,int randomNumber );
void saveNumberToFile(int number);
void importNumberFromFile(int* number);
void xorTheValue(void* genaralVariable, size_t const size);
void freeAllocatedMemoryForHotel(hotel_t* hotel);
void initFloorsAndRooms(int* numebrOfFloors,int* numberOfRooms);
void getAttributeFromTheFirstFloor(hotel_t* hotel);
void invokeArgumentAndImportFile(char*  argv[],hotel_t* hotel);
int checkValidInputsRoom(int* ifVeiwToThePool,int* ifThareIsPorch,int* ifThareIsKettle,int* ifThareIsFreeWifi,int* ifThareIsExtendCouch,int* ifThareIsTV,int* ifTaken,int* numberBeds);
int checkValidAttributeFromUser(int* attributeOption);
#endif