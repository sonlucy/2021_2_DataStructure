class StudentArray;
#include "Date.h"
#include "Person.h"

class Student : public Person  //�θ�Ŭ���� Person���κ��� ���
{
	friend class StudentArray; //StudentArrayŬ������ StudentŬ������ private ������ ������� ��밡���ϰ�
	friend ostream& operator<< (ostream&, const Student& st);
public:
	Student(); // default constructor
	Student(int id);
	Student(int id, string n, Date dob, string dept_n, double gpa);

	int getST_id() const { return st_id; }
	string getDept_name() const { return dept_name; };
	double getGPA() const { return gpa; }
	Date getBirthDate() const { return birthDate; }

	/* ���޹��� �μ��� ������ ��� �ʱ�ȭ*/
	void setST_id(int id) { st_id = id; }
	void setDept_name(string dp_n) { dept_name = dp_n; };
	void setGPA(double g) { gpa = g; }

	Student& operator=(const Student& pe);  //���Կ���
	//const Student& operator=(const Student& right);
	bool operator>(const Student& right);
	bool operator==(const Student& right);
private:
	int st_id;
	string dept_name;
	double gpa;
};

Student genRandStudent(int id);  //Student�� ������ ������� �������� ���� �� �ʱ�ȭ
void genST_ids(int num_students, int* st_ids);  //�й�(st_id)�� �������� ����
