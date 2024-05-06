
#include <string>
#include "Date.h"

istream& operator>>(istream& fin, Date& d)
{
	fin >> d.year >> d.month >> d.day;
	return fin;
}

ostream& operator<<(ostream& fout, const Date& d)
{
	fout << "(" << d.year << ". " << setw(2) << d.month << ". " << d.day << ")";
	return fout;
}

Date::Date()
	:year(1), month(1), day(1)
{


}

Date::Date(int y, int m, int d)
{
	if (isValidDate(y, m, d))  //올바른 값이면
	{   /* 데이터 할당 */
		year = y;
		month = m;
		day = d;
	}
	else //올바르지않은 값이면
	{
		cout << "invaild date (" << y << ", " << m << ", " << d << " )";
		cout << "Program aborted. " << endl;
		exit;
	}
}

void Date::setDate(int newYear, int newMonth, int newDay)
{
	if (isValidDate(newYear, newMonth, newDay)) //올바른 값이면
	{
		/* 전달받은 새로운 년월일값으로 데이터 초기화 */
		year = newYear;
		month = newMonth;
		day = newDay;
	}
	else
	{
		cout << "Invaild date (" << newYear << ", " << newMonth << ", " << newDay << ") ";
		cout << "Program aborted. " << endl;
		exit;
	}
}

bool Date::isValidDate(int y, int m, int d)
{
	int days_month[13] = { 0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (isLeapYear(y)) //윤년이면
	{
		days_month[2] = 29; //2월은 29일
	}
	if ((m >= 1) && (m <= 12) && (d >= 1) && d <= days_month[m]) //올바른 범위내에 있는 경우
	{
		return true;
	}
	else
	{
		cout << "Illegal date. (" << m << ", " << d << ")==> Program aborted." << endl;
		return false;
	}
}

bool Date::isLeapYear()
{
	return isLeapYear(year);
}


bool Date::isLeapYear(int y)
{
	if ((y % 4 == 0) && (y % 100 != 0) || (y % 400 == 0))
		return true;
	else
		return false;
}

int Date::getYearDay()
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int year_day = 0;

	if (isLeapYear())  //윤년이면
		days_month[2] = 29;  //2월은 29일
	for (int y = 1; y < month; y++)  ////////////////////////
	{
		year_day += days_month[y];  //해당 월의 일수
	}

	year_day += day;
	return year_day;
}

int Date::getWeekDay()
{
	int elpsedDay = 0;
	int weekDay;

	elpsedDay = getElapsedDays();
	weekDay = elpsedDay % 7;

	return weekDay;
}

int Date::getElapsedDays()
{
	int yearDay;
	int elpsedDay = 0;

	for (int y = 1; y < year; y++)
	{
		if (isLeapYear(y))  //윤년이면
			elpsedDay += 366;  //1년은 366일
		else
			elpsedDay += 365;  //윤년 아니면 1년은 365일
	}
	yearDay = getYearDay(); //월, 일의 일수 받아오고
	elpsedDay += yearDay;

	return elpsedDay;
}

const Date Date:: operator=(const Date rightSide)
{
	year = rightSide.year;
	month = rightSide.month;
	day = rightSide.day;

	return *this;
}

bool Date::operator>(Date rightSide)
{
	int left_date_sum = 0, right_date_sum = 0;

	left_date_sum = this->getElapsedDays();
	right_date_sum = rightSide.getElapsedDays();

	if (left_date_sum > right_date_sum)
		return true;
	else
		return false;
}

bool Date::operator<(Date rightSide)
{

	int left_date_sum = 0, right_date_sum = 0;

	left_date_sum = this->getElapsedDays();
	right_date_sum = rightSide.getElapsedDays();

	if (left_date_sum < right_date_sum)
		return true;
	else
		return false;
}

bool Date::operator>=(Date rightSide)
{
	int left_date_sum = 0, right_date_sum = 0;

	left_date_sum = this->getElapsedDays();
	right_date_sum = rightSide.getElapsedDays();

	if (left_date_sum >= right_date_sum)
		return true;
	else
		return false;
}

bool Date::operator<=(Date rightSide)
{

	int left_date_sum = 0, right_date_sum = 0;

	left_date_sum = this->getElapsedDays();
	right_date_sum = rightSide.getElapsedDays();

	if (left_date_sum <= right_date_sum)
		return true;
	else
		return false;
}


bool Date::operator==(Date rightSide)
{
	if ((year == rightSide.year) && (month == rightSide.month) && (day = rightSide.day))
		return true;
	else
		return false;
}

bool Date::operator!=(Date rightSide)
{
	if ((year != rightSide.year) || (month != rightSide.month) || (day != rightSide.day))
		return true;
	else
		return false;
}



bool isLeapYear(int y)  // used in genRandDate()
{
	if ((y % 4 == 0) && (y % 100 != 0) || (y % 400 == 0))
		return true;
	else
		return false;
}

Date genRandDate()
{
	Date Rand_date;
	int y, m, d;
	int days_month[13] = { 0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	y = (rand() % 1000) + 2000;  //2000 ~ 2999
	m = (rand() % 12) + 1;  //1~ 12

	if (isLeapYear(y))//윤년이면
		days_month[2] = 29;  //2월은 29일까지 있음

	d = (rand() % days_month[m]) + 1;  // 1 ~ 해당 달의 일수

	Rand_date.setDate(y, m, d);

	return Rand_date;
}


/*void Date::inputDate()
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
}*/


/*int Date::sortingforbirth_year()
{
	return year;
}

int Date::sortingforbirth_month()
{
	return month;
}
int Date::sortingforbirth_day()
{
	return day;
}*/

