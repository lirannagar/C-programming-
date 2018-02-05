#ifndef __FUNCTIONS__
#define __FUNCTIONS__


int checkValidNumberInsideRoom(int* numberPersonsInsideRoomChecker);
int checkValidNumberBreakfast(int* numberPersonsBreakfastChecker,int* numberInsideTheRoom);
void printfValuesOfTheRoomIfTaken(room_t* roomChecker);



void initHotel(hotel_t* hotel,int* numebrOfFloors,int* numberOfRooms);
void showHotelStatus(hotel_t* hotel);
void printRoomDetails(hotel_t* hotel, reservation_t* res);


void checkIn(hotel_t* hotel ,reservation_t* r , costomer_t* costomer , int* counterCostomers, int* counterReservation);
void checkOut(hotel_t* hotel);
int checkIfNameExistAndAddToReservation(reservation_t* r,int* IDChek,int* counterCostomers,costomer_t* costomer);
int checkifThareIsNoCostomersAndAddCostomer(int* counterCostomers,costomer_t* costomer,int* maxCustomer);
void showAllCostomerInTheReservoir(int* counterCostomers,costomer_t* tmpCostomer );
void chackAvailableAndInsertReservation(reservation_t* r,hotel_t* hotel);
void freeMemory(hotel_t* hotel,costomer_t* costomer ,reservation_t* res ,costomer_t* costomerSubsting , int* counterCustomer);


void initCostomer(costomer_t* c,int* counterCostomers,char userOption, int* maxCustomers);
costomer_t addCustomer(int id, char name[],char numberCraditCard[] ,int yearValidCreditCard ,int mouthValidCraditCard);


int checkValidCraditCard(char craditCardNumberChecker[]);

int checkValidYear(int* validYearNumberChecker);
int checkValidMonth(int* validMonthNumberChecker);
void toUpperCaseFirstChar(char str[]);

int checkValidNumberOfFloors(int* numebrOfFloors);
int checkValidNumberOfRooms(int* numebrOfRooms);

costomer_t* findSubstringName(char str[], costomer_t* costomer,int* counterCostomer,int* costomerSubstingCounter);


void printfCostomerSubstring( costomer_t* costomerSubsting,int* costomerSubstingCounter);
void checkMemoryState(void* allocatedArray);

#endif