#ifndef STUDENT_H 
#define STUDENT_H 
#include "Person.h" 
#include "Time.h" 
#include "Date.h"
class Student : public Person  //PersonŬ�����κ��� �Ļ�
{
	friend ostream& operator<< (ostream& fout, Student& st);
public:
	Student(); // default constructor 
	Student(int s_id, string n, Date dob, Time avt, double gpa);

	/* �񱳿����� ���۷����� ���ε� */
	/* �����ð� ���� */
	bool operator<( Student&) ;
	bool operator<=( Student&) ;
	bool operator>( Student&) ;
	bool operator>=( Student&) ;
	bool operator==( Student&) ;
private:
	int st_id;
	double gpa;
	Time arrivalTime;  ///�����ð�
};
#endif