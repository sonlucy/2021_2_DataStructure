/* Person.h */
//Date항목이 포함되는 Person 클래스로 만들어 구현

#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Date.h"
using namespace std;
#define MAX_NAME_LEN 15
#define MIN_NAME_LEN 5

class Person
{
public:
	Person() : name(string("nobody")), birthDate(Date(1, 1, 1)) { }  //기본생성자
	Person(string n, Date bd) : name(n), birthDate(bd) { }  //생성자(초기화 부분을 담당)
	void setName(string n) { name = n; }  //데이터멤버 설정자
	string getName() { return name; }  //데이터멤버 접근자
	void setBirthDate(Date bd) { birthDate = bd; }
	Date getBirthDate() { return birthDate; }
	void setRandPersonAttributes();
	void fprintPerson(ostream& fout);
	Person selectionPersonBy_name(Person *persons);
	Person selectionPersonBy_birth(Person *persons);
	void printPerson();


private:
	/* 데이터 멤버 */
	Date birthDate;
	string name;
};
#endif