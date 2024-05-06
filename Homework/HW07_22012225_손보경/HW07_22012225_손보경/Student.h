#ifndef STUDENT_H 
#define STUDENT_H 
#include "Person.h" 
#include "Time.h" 
#include "Date.h"
class Student : public Person  //Person클래스로부터 파생
{
	friend ostream& operator<< (ostream& fout, Student& st);
public:
	Student(); // default constructor 
	Student(int s_id, string n, Date dob, Time avt, double gpa);

	/* 비교연산자 오퍼레이팅 업로딩 */
	/* 도착시간 기준 */
	bool operator<( Student&) ;
	bool operator<=( Student&) ;
	bool operator>( Student&) ;
	bool operator>=( Student&) ;
	bool operator==( Student&) ;
private:
	int st_id;
	double gpa;
	Time arrivalTime;  ///도착시간
};
#endif