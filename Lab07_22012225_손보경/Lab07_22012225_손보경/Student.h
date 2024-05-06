#ifndef STUDENT_H 
#define STUDENT_H 
#include "Person.h" 
#include "Date.h" 
#include "Time.h" 
class Student : public Person  //
{
	friend ostream& operator<< (ostream& fout, Student& st);
public:
	Student(); // default constructor 
	Student(int s_id, string n, Date dob, Time avt, double gpa);
	void getKey(string keyName, void* pKey);   ////pKey�� ����Ű�� ���� ���޹��� keyName�� �ش��ϴ� �����͸�� ����Ű��

	//int getIntKey() {return st_id;}
	//double getDoubleKey() { return gpa;}

	/* �񱳿����� ���۷����� ���ε� */
	bool operator<(const Student&) const;
	bool operator<=(const Student&) const;
	bool operator>(const Student&) const;
	bool operator>=(const Student&) const;
	bool operator==(const Student&) const;
private:
	int st_id;
	double gpa;
};
#endif