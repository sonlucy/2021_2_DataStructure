#ifndef PERSON_H 
#define PERSON_H 
#include <iostream> 
#include <string> 
#include "Date.h" 
#include "Time.h" 
class Person
{
	friend ostream& operator<< (ostream& fout, const Person& p)
	{
		fout << " Person [name: " << p.name << "]";
		return fout;
	}
public:
	Person() { name = "nobody"; }
	Person(string n) { name = n; }

	void setName(string n) { name = n; }
	string getName() { return name; }

	void setDoB(Date dob) { dateOfBirth = dob; }
	const Date getDoB() const { return dateOfBirth; }

	void setArrivalTime(Time t) { arrivalTime = t; }
	const Time getArrivalTime() const { return arrivalTime; }
protected:
	string name;  
	/* 상속클래스가 사용할 수 있게*/
	Date dateOfBirth; 
	Time arrivalTime;  
};
#endif