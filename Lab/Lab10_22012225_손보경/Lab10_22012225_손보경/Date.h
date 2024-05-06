#ifndef DATE_H
#define DATE_H
#include <iostream>   
#include <iomanip>    
using namespace std;

class Date
{
	friend istream& operator>>(istream&, Date& d);
	friend ostream& operator<<(ostream&, const Date& d);
public:
	Date(); // default constructor
	Date(int y, int m, int d); // constructor

	void setDate(int newYear, int newMonth, int newDay);  //전달받은 새로운 날짜로 초기화
	int getYear() { return year; }
	int getYearDay();  //월,일 ->일수로
	int getWeekDay();
	//int getElapsedDaysFromAD010101();
	//int getElapsedDaysFromAD010101(Date d);
	int getElapsedDays(); // 서기 1년 1월 1일로부터 지난 날짜 일수

	const Date operator=(const Date rightSide);  //대입연산자
	bool operator>(Date rightSide);
	bool operator<(Date rightSide);
	bool operator>=(Date rightSide);
	bool operator<=(Date rightSide);
	bool operator==(Date rightSide);  //같은지
	bool operator!=(Date rightSide);  //다른지

	bool isLeapYear(int y); // 년도 y가 윤년인지

private:

	bool isLeapYear(); // year이 윤년인지
	bool isValidDate(int y, int m, int d);  //전달받은 y , m , d (년월일)이 올바른 범위에 있는지

	int year;
	int month;
	int day;
};

bool isLeapYear(int y); // genRandDate()함수에서 생성한 년도가 윤년인지
Date genRandDate();  //날짜를 랜덤으로 생성

#endif
