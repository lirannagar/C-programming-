#ifndef __RESERVATIONSTRUCT__
#define __RESERVATIONSTRUCT__

struct Reservation
{
	costomer_t costomerPointer;
	int numberOfPeopleInsideRoom;
	int numberOfPeopleThatWillEatBreakfast;
	room_t roomPointer;
	int ifChackOut;

}typedef reservation_t;

#endif

