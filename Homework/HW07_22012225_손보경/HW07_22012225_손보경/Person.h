#ifndef PERSON_H
#define PERSON_H
//#include <string>
//using namespace std;
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
protected:
	string name;
	Date dateOfBirth;  //////////////////////
};
#endif