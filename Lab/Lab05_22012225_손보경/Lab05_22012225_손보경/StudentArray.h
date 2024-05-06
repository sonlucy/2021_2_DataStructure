#include <iostream>
#include "Student.h"
using namespace std;
class StudentArray
{
	friend ostream& operator<< (ostream&, const StudentArray& st_A);
public:
	StudentArray(int size); // constructor
	StudentArray(const StudentArray& obj);
	~StudentArray();  //소멸자
	int size() const { return num_students; }
	Student& operator[] (int index) const;

	/* 정렬 함수*/
	void sortByBirthDate();
	void sortByName();
	void sortByST_ID();
	void sortByGPA(); //내림차순

private:
	Student* students;
	int num_students; //총 학생수
	bool isValidIndex(int index) const;  //해당 인덱스 올바른 값인지
};
