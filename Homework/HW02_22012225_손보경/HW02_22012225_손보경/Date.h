#pragma once
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define WEEKDAY_AD01Jan01 MON  //the weekday of AD Jan 1.
#define DAYS_PER_WEEK 7
#define Secs_in_Minute 60
#define Secs_in_Hour (Secs_in_Minute *60)
#define Secs_in_DAY (Secs_in_Hour*24)
#define LOCAL_GMT_OFFSET_HOUR 9

class Date
{
public:
	Date(); //default constructor 기본생성자 (별도의 정보가 제공되지 않았을때
	Date(int y, int m, int d); ///constructor 생성자
	~Date();  //destructor 소멸자 (클래스 기반으로 만들어져있는 변수가 더이상 사용하지안ㅎ을떄 소멸시키기위해

	void inputDate();
	void fprintDate(ostream& fout);
	void printDate();
	void setDate(int y, int m, int d);
	void setRandDateAttributes();
	void setMonth(int m);
	void setYear(int y);
	int getYear() { return year; }  //inline 멤버 함수
	int getMonth() { return month; } //Returns 1 for January, 2 for February, etc.
	int getDay() { return day; }
	int getYearDay();
	int getYearDay(int m, int d);  //1월 1일부터 몇번쨰날인가
	int getWeekDay();  //무슨요일
	int getElapsedDaysFromAD010101(); // get elapsed days from AD 1. 1. 1.
	int getElapsedDaysFromAD010101(Date);
	//void fprintCalendar_Month(ostream& fout);  //지정된 파일로 출력
private:
	/* 데이터 멤버 */
	bool isLeapYear(); // check whether the year is leap year
	bool isLeapYear(int y); // check whether the given year y is leap year
	bool isValidDate(int y, int m, int d);
	int year;
	int month;
	int day;
};
#endif

