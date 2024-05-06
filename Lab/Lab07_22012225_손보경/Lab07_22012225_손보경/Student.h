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
	void getKey(string keyName, void* pKey);   ////pKey가 가리키는 값을 전달받은 keyName에 해당하는 데이터멤버 가리키게

	//int getIntKey() {return st_id;}
	//double getDoubleKey() { return gpa;}

	/* 비교연산자 오퍼레이팅 업로딩 */
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