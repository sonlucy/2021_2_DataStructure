#include <iostream>
#include <string>
#include <iomanip>
#include "Date.h"
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };
enum MONTH { JAN = 1, FED, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, NUM_MONTHS };
const char* weekDayName[DAYS_PER_WEEK] = { "Sunday", "Monday", "Tuesday", "Wednesday",
"Thursday", "Friday", "Saturday" };
const char* weekDayNameShort[DAYS_PER_WEEK] = { "SUN", "MON", "TUE", "WED", "THR", "FRI",
"SAT" };
const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July",
"August", "September", "October", "November", "December" };


Date::Date(int y, int m, int d)
{
	setDate(y, m, d);
	//cout << "생성자 호출" << endl;

}

//default constructor
Date::Date()
{
	year = 0;
	month = 0;
	day = 0; //

	//cout << "생성자 호출" << endl;
}

//default destructor
Date::~Date()
{
	//cout << "소멸자 호출" << endl;
	//cout << "Date object instance is destructed" << endl;
}
bool Date::isValidDate(int y, int m, int d)
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (isLeapYear(y))  //윤년이면
		days_month[2] = 29;  //2월달은 29일로 변경

	if ((m >= 1) && (m <= 12) && (d >= 1) && (d <= days_month[m]))
	{  //1~12월 사이이고, 해당 월의 최대일수보다 같거나 작으면
		return true;
	}
	else {
		cout << "Illegal date! (" << m << ", " << d << ") ==> Program aborted.\n";
		return false;
	}
}

void Date::setRandDateAttributes()
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	year = rand() % 2000 + 1000;
	month = rand() % 12 + 1;
	if (isLeapYear(year) && month == 2)
		days_month[2] = 29;
	day = rand() % days_month[month] + 1;
}

void Date::setDate(int y, int m, int d)
{
	if (isValidDate(y, m, d))  //정상적인 날짜이면
	{
		year = y;
		month = m;
		day = d;

	}
	else {
		cout << "Invalid date (" << y << ", " << m << ", " << d << ")";
		cout << " Program aborted !!\n";
		exit(1);
	}
}

void Date::setMonth(int newMonth)
{
	if ((newMonth >= 1) && (newMonth <= 12))
		month = newMonth;
	else
	{
		cout << "Illegal month value! Program aborted.\n";
		exit(1);
	}
	day = 1;
}
void Date::setYear(int y)
{
	year = y;
}
int Date::getYearDay()  //이번 해의 몇번째날인지
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;

	if (isLeapYear())  //윤년이면
		days_month[2] = 29; //2월은 29일
	for (int m = 1; m < month; m++)
		yearDay += days_month[m];
	yearDay += day;  //이번달의 day

	return yearDay;
}
int Date::getYearDay(int month, int day)
{

	int days_month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int yearDay = 0;

	for (int m = 1; m < month; m++)
	{
		yearDay += days_month[m];
	}
	yearDay += day;
	if ((month > 2) && isLeapYear(year))
		yearDay += 1;

	return yearDay;


}

int Date::getElapsedDaysFromAD010101()
{
	int elpsDay = 0;
	elpsDay = getElapsedDaysFromAD010101(*this);
	return elpsDay;
}
int Date::getElapsedDaysFromAD010101(Date d)
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < d.year; y++)  //year이 1부터 작년까지
	{
		if (isLeapYear(y))  //윤년이면
			elpsDay += 366;
		else
			elpsDay += 365;
	}
	yearDay = getYearDay(d.month, d.day); //올해부터 몇번째 날인지
	elpsDay += yearDay;  //올해 일수 더하기

	return elpsDay;
}

int Date::getWeekDay()
{
	int weekDay_AD010101 = MON; // 서기 1년 1월 1일은 월요일
	int weekDay;
	int elapsedDays = 0;

	elapsedDays = getElapsedDaysFromAD010101();
	weekDay = (elapsedDays + weekDay_AD010101 - 1) % 7;
	//cout << ", Elapsed days from AD Jan. 1, 1 (" << elapsedDays << ")";
	return weekDay;
}
void Date::inputDate()
{
	int y, m, d;
	cout << "Enter date in year month day : ";
	cin >> y >> m >> d;
	if (isValidDate(y, m, d))
	{
		year = y;
		month = m;
		day = d;
	}
	else
	{
		cout << "Ilegal date! Program aborted.\n";
		exit(1);
	}
}

bool Date::isLeapYear(int y)
{
	//주어진 y (year)이 윤년인지 아닌지 따지고, true또는 false return
	if ((y % 4 == 0) && (y % 100 != 0) || (y % 400 == 0))
		return true;
	else
		return false;

}
bool Date::isLeapYear()
{
	return isLeapYear(year);
}
void Date::fprintDate(ostream& fout)
{
	const char* weekDayName[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
	"Friday", "Saturday" };
	const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December" };
	int yearDay = 0;
	int weekDay;

	if ((month >= 1) && (month <= 12))
		fout << setw(10) << string(monthName[month]);
	fout << " " << setw(2) << day << ", " << setw(4) << year;

	yearDay = getYearDay();
	weekDay = getWeekDay();
	fout << " (" << setw(10) << string(weekDayName[weekDay]) << ")";
}

void Date::printDate()
{
	const char* weekDayName[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
	"Friday", "Saturday" };
	const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July",
   "August", "September", "October", "November", "December" };
	int yearDay = 0;
	int weekDay;
	char todayWeekDayName[10];  /////////////

	if ((month >= 1) && (month <= 12))
		cout << string(monthName[month]);  //그 달의 이름 출력
	cout << " " << day << ", " << year;  // 일, 년도 출력

	yearDay = getYearDay();
	weekDay = getWeekDay();
	cout << "(" << string(weekDayName[weekDay]) << ")";   //오늘이 무슨요일인지 출력

}

