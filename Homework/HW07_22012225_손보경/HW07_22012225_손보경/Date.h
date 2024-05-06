#ifndef DATE_H 
#define DATE_H 
#include <iostream> 
using namespace std;
#define WEEKDAY_AD01Jan01 MON // the weekday of AD Jan 1. 
#define DAYS_PER_WEEK 7 

class Date
{
	friend ostream& operator<<(ostream& fout, const Date& d)
	{
		fout << " (" << d.year << ", " << d.month << ", " << d.day << ") ";
		return fout;
	}
public:
	Date(); // default constructor 
	Date(int y, int m, int d); // constructor 
	~Date(); // destructor 

	int getWeekDay();
	int getElapsedDaysFromAD010101() const; // get elapsed days from AD 1. 1. 1. 
	int getElapsedDaysFromAD010101(Date d) const;

	bool operator<(Date& d);
	bool operator<=(Date& d);
	bool operator>(Date& d);
	bool operator>=(Date& d);
	bool operator==(Date& d);


private:
	bool isValidDate(int y, int m, int d);
	int year;
	int month;
	int day;
};
bool isLeapYear(int y); // 년도 y가 윤년인지
int getYearDay(int year, int month, int day);  
#endif