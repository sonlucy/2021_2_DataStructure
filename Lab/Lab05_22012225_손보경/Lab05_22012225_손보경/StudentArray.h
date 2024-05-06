#include <iostream>
#include "Student.h"
using namespace std;
class StudentArray
{
	friend ostream& operator<< (ostream&, const StudentArray& st_A);
public:
	StudentArray(int size); // constructor
	StudentArray(const StudentArray& obj);
	~StudentArray();  //�Ҹ���
	int size() const { return num_students; }
	Student& operator[] (int index) const;

	/* ���� �Լ�*/
	void sortByBirthDate();
	void sortByName();
	void sortByST_ID();
	void sortByGPA(); //��������

private:
	Student* students;
	int num_students; //�� �л���
	bool isValidIndex(int index) const;  //�ش� �ε��� �ùٸ� ������
};
