/*
* Lab02
* Ŭ����, Ŭ���� ��� �Լ�, ����
* �ۼ���: ������Ű��а� 22012225 �պ���
* �ۼ�����: 2021-09-10
*/

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "Date.h"
#include "Person.h"
using namespace std;
#define NUM_PERSON 10

int main()
{
	ofstream fout;
	fout.open("output.txt");  //���Ͽ���
	if (fout.fail())
	{
		cout << "Error in opening output.txt !!" << endl;
		exit;
	}

	/* part 1 - handling class Date */
	Date AD010101(1, 1, 1);
	int year, month, day;
	int daysToChristmas;
	time_t currentTime; //�ð� ���� ������ ���� �� �ִ� ����ü
	struct tm* time_and_date;

	time(&currentTime);  
	time_and_date = localtime(&currentTime);
	year = time_and_date->tm_year + 1900;
	month = time_and_date->tm_mon + 1;
	day = time_and_date->tm_mday;
	Date newYearDay(year, 1, 1), today(year, month, day);

	/*���� 1�� 1�� */
	fout << "AD Jan. 1, 1 is ";
	cout << "AD Jan. 1, 1 is ";
	AD010101.fprintDate(fout);
	AD010101.printDate();
	fout << endl;
	cout << endl;

	/* ���� ��¥ */
	fout << "Today is ";
	cout << "Today is ";
	today.fprintDate(fout);
	today.printDate();
	fout << endl;
	cout << endl;

	/* ������ 1�� 1��*/
	fout << "New year's day of this year was ";
	cout << "New year's day of this year was ";
	newYearDay.fprintDate(fout);
	newYearDay.printDate();
	fout << endl;
	cout << endl;

	/* ������ ũ�������� */
	Date christmas(year, 12, 25);
	fout << "Christmas of this year is ";
	cout << "Christmas of this year is ";
	christmas.fprintDate(fout);
	christmas.printDate();
	fout << endl;
	cout << endl;

	if (today.getMonth() == christmas.getMonth() && today.getDay() == christmas.getDay())
	{   //12���̸鼭 25���̸�
		fout << "Today is Christmas! Happy Christmas to you all !!\n";
		cout << "Today is Christmas! Happy Christmas to you all !!\n";

	}
	else {
		fout << " Sorry, today is not Christmas!\n";
		cout << " Sorry, today is not Christmas!\n";
		daysToChristmas = christmas.getElapsedDaysFromAD010101()- today.getElapsedDaysFromAD010101();
		fout << " You must wait " << daysToChristmas << " day(s) to Christmas !" << endl;
		cout << " You must wait " << daysToChristmas << " day(s) to Christmas !" << endl;

	}
	fout << endl;
	cout << endl;


	/* part 2 - handling class Person */
	Person p1(string("Hong, Gil-Dong"), Date(2000, 1, 1)), p2;
	fout << "Person p1 : " << endl;
	//cout << "Person p1 : " << endl;
	p1.fprintPerson(fout);
	p1.printPerson();
	//p1.printPerson();
	fout << endl;
	//cout << endl;

	fout << "Person p2 : " << endl;
	p2.setName(string("Lee, Soo-Jeong"));
	p2.setBirthDate(Date(2018, 9, 1));
	p2.fprintPerson(fout);
	p2.printPerson();
	fout << endl;
	
	fout << endl << "Generating array of persons ... " << endl;
	cout << endl << "Generating array of persons ... " << endl;
	Person* persons;
	Person* P;   ////////////////////
	persons = (Person*) new Person[NUM_PERSON];
	for (int i = 0; i < NUM_PERSON; i++)
	{
		persons[i].setRandPersonAttributes();
		persons[i].fprintPerson(fout);
		persons[i].printPerson();
		fout << endl;
		cout << endl;
	}
	fout << endl;
	cout << endl;


	/* ���� */
	
	fout << "Seletion sorting of Persons by increasing order of name" << endl;
	cout << "Seletion sorting of Persons by increasing order of name" << endl;

	persons->selectionPersonBy_name(persons);
	for (int i = 0; i < NUM_PERSON; i++)
	{
		persons[i].fprintPerson(fout);
		persons[i].printPerson();
		fout << endl;
		cout << endl;
	}
	fout << endl;
	cout << endl;

	fout << "Seletion sorting of Persons by increasing order of birth" << endl;
	cout << "Seletion sorting of Persons by increasing order of birth" << endl;

	persons->selectionPersonBy_birth(persons);
	for (int i = 0; i < NUM_PERSON; i++)
	{
		persons[i].fprintPerson(fout);
		persons[i].printPerson();
		fout << endl;
		cout << endl;
	}
	

	delete[] persons; //��ü �Ҹ�
	fout.close();

	return 0;
}

