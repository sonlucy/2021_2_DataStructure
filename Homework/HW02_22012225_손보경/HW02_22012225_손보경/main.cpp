#include <iostream>
#include "Date.h"
using namespace std;

int main()
{
	Date AD010101(1, 1, 1), newYearDay(2021, 1, 1), today, christmas(2021, 12, 25);
	int year;
	int daysToChristmas;  //크리스마스까지 며칠남았는지

	cout << "AD Jan. 1, 1 is";
	AD010101.printDate();
	cout << endl;

	cout << "New year's day of 2021 is";
	newYearDay.printDate();
	cout << endl;

	cout << "Christmas of this year is";
	christmas.printDate();
	cout << endl;

	today.inputDate();
	cout << "Today is ";
	today.printDate();
	cout << endl;

	if (today.getMonth() == christmas.getMonth() && today.getDay() == christmas.getDay())
	{
		cout << "Happy Christmas ~!~~!!";
	}
	else 
	{
		cout << "Sorry, today is not Christmas. ";
		daysToChristmas = christmas.getElapsedDaysFromAD010101() - today.getElapsedDaysFromAD010101();
		cout << "You must wait " << daysToChristmas << "day(s) to Christmas ~!~~!" << endl;
	
	}

	return 0;

}