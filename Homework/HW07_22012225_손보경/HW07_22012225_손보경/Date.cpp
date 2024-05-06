#include "Date.h"
#include <iostream>
#include <string>
#include <iomanip>


Date::Date()
{
	year = 0;
	month = 0;
	day = 0; //

	//cout << "������ ȣ��" << endl;
}

Date::Date(int y, int m, int d)
{
	//setDate(y, m, d);
	//cout << "������ ȣ��" << endl;

	if (isValidDate(y, m, d))  //�ùٸ� ���̸�
	{   /* ������ �Ҵ� */
		year = y;
		month = m;
		day = d;
	}
	else //�ùٸ������� ���̸�
	{
		cout << "invaild date (" << y << ", " << m << ", " << d << " )";
		cout << "Program aborted. " << endl;
		exit;
	}
}



//default destructor
Date::~Date()
{
	//cout << "�Ҹ��� ȣ��" << endl;
	//cout << "Date object instance is destructed" << endl;
}
bool Date::isValidDate(int y, int m, int d)
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (isLeapYear(y))  //�����̸�
		days_month[2] = 29;  //2������ 29�Ϸ� ����

	if ((m >= 1) && (m <= 12) && (d >= 1) && (d <= days_month[m]))
	{  //1~12�� �����̰�, �ش� ���� �ִ��ϼ����� ���ų� ������
		return true;
	}
	else {
		cout << "Illegal date! (" << m << ", " << d << ") ==> Program aborted.\n";
		return false;
	}
}


int Date::getWeekDay()
{
	int elpsedDays = 0;
	int weekDay;

	elpsedDays = getElapsedDaysFromAD010101(); //��¥�� �ϼ��� �ٲپ� ��ȯ
	weekDay = elpsedDays % 7;

	return weekDay;
}



/*int Date::getYearDay(int month, int day)
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

int Date::getElapsedDays()
{
	int yearDay;
	int elpsedDay = 0;

	for (int y = 1; y < year; y++)
	{
		if (isLeapYear(y))  //�����̸�
			elpsedDay += 366;  //1���� 366��
		else
			elpsedDay += 365;  //���� �ƴϸ� 1���� 365��
	}
	yearDay = getYearDay(); //��, ���� �ϼ� �޾ƿ���
	elpsedDay += yearDay;

	return elpsedDay;
}*/

int Date::getElapsedDaysFromAD010101() const
{
	int elpsDay = 0;
	elpsDay = getElapsedDaysFromAD010101(*this);

	return elpsDay;
}

int Date::getElapsedDaysFromAD010101(Date d) const
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < d.year; y++)  //year�� 1���� �۳����
	{
		if (isLeapYear(y))  //�����̸�
			elpsDay += 366;
		else
			elpsDay += 365;
	}
	yearDay = getYearDay(d.year, d.month, d.day); //���غ��� ���° ������
	elpsDay += yearDay;  //���� �ϼ� ���ϱ�

	return elpsDay;
}


bool Date::operator>=(Date& d)
{


	if (this->getElapsedDaysFromAD010101() >= d.getElapsedDaysFromAD010101())
		return true;
	else
		return false;
}

bool Date::operator<=(Date& d)
{


	if (this->getElapsedDaysFromAD010101() <= d.getElapsedDaysFromAD010101())
		return true;
	else
		return false;
}

bool Date::operator>(Date& d)
{

	if (this->getElapsedDaysFromAD010101() > d.getElapsedDaysFromAD010101())
		return true;
	else
		return false;
}

bool Date::operator<(Date& d)
{

	if (this->getElapsedDaysFromAD010101() < d.getElapsedDaysFromAD010101())
		return true;
	else
		return false;
}

bool Date::operator==(Date& d)
{
	//if ((year == d.year) && (month == d.month) && (day = d.day))
	if (this->getElapsedDaysFromAD010101() == d.getElapsedDaysFromAD010101())
		return true;
	else
		return false;
}

/*int Date::getWeekDay()
{
	int weekDay_AD010101 = MON; // ���� 1�� 1�� 1���� ������
	int weekDay;
	int elapsedDays = 0;

	elapsedDays = getElapsedDaysFromAD010101();
	weekDay = (elapsedDays + weekDay_AD010101 - 1) % 7;
	//cout << ", Elapsed days from AD Jan. 1, 1 (" << elapsedDays << ")";
	return weekDay;
}*/

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
		cout << string(monthName[month]);  //�� ���� �̸� ���
	cout << " " << day << ", " << year;  // ��, �⵵ ���

	yearDay = getYearDay();
	weekDay = getWeekDay();
	cout << "(" << string(weekDayName[weekDay]) << ")";   //������ ������������ ���

}

int Date::sortingforbirth_year()
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


bool isLeapYear(int y)
{
	//�־��� y (year)�� �������� �ƴ��� ������, true�Ǵ� false return
	if ((y % 4 == 0) && (y % 100 != 0) || (y % 400 == 0))
		return true;
	else
		return false;

}

int getYearDay(int year, int month, int day)
{
	int days_month[13] = { 0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int year_day = 0;

	if (isLeapYear(year))  //�����̸�
		days_month[2] = 29;  //2���� 29��

	for (int y = 1; y < month; y++)
	{
		year_day += days_month[y];  //�ش� ���� �ϼ�
	}

	year_day += day;
	return year_day;
}

