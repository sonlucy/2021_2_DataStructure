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

	void setDate(int newYear, int newMonth, int newDay);  //���޹��� ���ο� ��¥�� �ʱ�ȭ
	int getYear() { return year; }
	int getYearDay();  //��,�� ->�ϼ���
	int getWeekDay();
	//int getElapsedDaysFromAD010101();
	//int getElapsedDaysFromAD010101(Date d);
	int getElapsedDays(); // ���� 1�� 1�� 1�Ϸκ��� ���� ��¥ �ϼ�

	const Date operator=(const Date rightSide);  //���Կ�����
	bool operator>(Date rightSide);
	bool operator<(Date rightSide);
	bool operator>=(Date rightSide);
	bool operator<=(Date rightSide);
	bool operator==(Date rightSide);  //������
	bool operator!=(Date rightSide);  //�ٸ���

	bool isLeapYear(int y); // �⵵ y�� ��������

private:

	bool isLeapYear(); // year�� ��������
	bool isValidDate(int y, int m, int d);  //���޹��� y , m , d (�����)�� �ùٸ� ������ �ִ���

	int year;
	int month;
	int day;
};

bool isLeapYear(int y); // genRandDate()�Լ����� ������ �⵵�� ��������
Date genRandDate();  //��¥�� �������� ����

#endif
