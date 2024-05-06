#include <iostream>
#include <string>
#include "Date.h"
class Person
{
	friend ostream& operator<< (ostream& fout, const Person& pe);  
public:
	Person() { birthDate = Date(0, 0, 0); name = ""; };  //���޹޴� �Ű������� ������ �⺻ ������
	Person(string nm, Date bd) { birthDate = bd; name = nm; };

	void setName(string n) { name = n; }
	void setBirthDate(Date bd) { birthDate = bd; }
	string getName() const { return name; }
	Date getBirthDate() const { return birthDate; }

	Person& operator=(const Person& pe);  //���Կ�����

protected:  //���Ŭ������ ���������� �����ϰ�

	Date birthDate;
	string name;
};
