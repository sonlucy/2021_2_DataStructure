class StudentArray;
#include "Date.h"
#include "Person.h"

class Student : public Person  //부모클래스 Person으로부터 상속
{
	friend class StudentArray; //StudentArray클래스가 Student클래스의 private 데이터 멤버들을 사용가능하게
	friend ostream& operator<< (ostream&, const Student& st);
public:
	Student(); // default constructor
	Student(int id);
	Student(int id, string n, Date dob, string dept_n, double gpa);

	int getST_id() const { return st_id; }
	string getDept_name() const { return dept_name; };
	double getGPA() const { return gpa; }
	Date getBirthDate() const { return birthDate; }

	/* 전달받은 인수로 데이터 멤버 초기화*/
	void setST_id(int id) { st_id = id; }
	void setDept_name(string dp_n) { dept_name = dp_n; };
	void setGPA(double g) { gpa = g; }

	Student& operator=(const Student& pe);  //대입연산
	//const Student& operator=(const Student& right);
	bool operator>(const Student& right);
	bool operator==(const Student& right);
private:
	int st_id;
	string dept_name;
	double gpa;
};

Student genRandStudent(int id);  //Student의 데이터 멤버들을 랜덤으로 생성 및 초기화
void genST_ids(int num_students, int* st_ids);  //학번(st_id)를 랜덤으로 생성
