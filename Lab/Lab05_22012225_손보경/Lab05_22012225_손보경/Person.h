#include <iostream>
#include <string>
#include "Date.h"
class Person
{
	friend ostream& operator<< (ostream& fout, const Person& pe);  
public:
	Person() { birthDate = Date(0, 0, 0); name = ""; };  //전달받는 매개변수가 없을때 기본 생성자
	Person(string nm, Date bd) { birthDate = bd; name = nm; };

	void setName(string n) { name = n; }
	void setBirthDate(Date bd) { birthDate = bd; }
	string getName() const { return name; }
	Date getBirthDate() const { return birthDate; }

	Person& operator=(const Person& pe);  //대입연산자

protected:  //상속클래스가 직접접근이 가능하게

	Date birthDate;
	string name;
};
