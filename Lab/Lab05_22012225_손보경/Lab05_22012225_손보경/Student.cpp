#include "Student.h"
#include "Mystring.h"
using namespace std;

ostream& operator<< (ostream& fout, const Student& st)
{
	fout.setf(ios::showpoint);
	fout.setf(ios::fixed);
	fout.precision(2);
	fout << "Student [ st_id : " << st.st_id << ", name : " << setw(7) <<  st.name;
	fout << ", dept : " << setw(6) << st.dept_name << ", ";
	fout << st.birthDate << " , GPA : " << setw(6) << st.gpa ;

	return fout;
}

Student& Student:: operator=(const Student& pe)
{
	Person::operator= (pe);  //��ӵ� Ŭ������ ���Կ����� ����

	/* �������κ� �ʱ�ȭ */
	st_id = pe.st_id;
	dept_name = pe.dept_name; 
	gpa = pe.gpa;

	return *this;
}


Student::Student()
	:Person("NULL", Date(1, 1, 1))  //�θ�Ŭ���� ������ �ҷ��ͼ� �ʱ�ȭ
{
	/* ������ Student ����� �ʱ�ȭ */
	st_id = 0;
	dept_name = "NULL";
	gpa = 0.0;
}

Student::Student(int id)
	:Person("NULL", Date(1, 1, 1))
{
	st_id = id;
	dept_name = "NULL";
	gpa = 0.0;
}

Student::Student(int id, string n, Date dob, string dept_n, double gp)
	:Person(n, dob)
{
	st_id = id;
	dept_name = dept_n;
	gpa = gp;
}

/*const Student& Student::operator=(const Student& right)
{
	st_id = right.st_id;
	dept_name = right.dept_name;
	gpa = right.gpa;

	name = right.name;
	birthDate = right.birthDate;

	return *this;
}*/

bool Student::operator==(const Student& right)
{
	if ((st_id == right.st_id) && (dept_name == right.dept_name) &&
		(gpa == right.gpa) && (name == right.name) && (birthDate == right.birthDate))
		return true;
	else
		return false;
}

bool Student::operator>(const Student& right)
{
	if ((st_id > right.st_id) && (dept_name > right.dept_name) &&
		(gpa > right.gpa) && (name > right.name) && (birthDate > right.birthDate))
		return true;
	else
		return false;
}

Student genRandStudent(int id)
{
	Student student;
	double Gpa = 0.0;
	Gpa = (rand() % 10000) / 100.0;  //0.0 ~ 99.99

	student.setST_id(id);  //���޹��� id���� student�� �й����� ����
	student.setName(genRandName()); //�������� ������ �̸� student�� �̸����� ����
	student.setBirthDate(genRandDate());  //�������� ������ ��¥ student�� ��¥�� ����
	student.setDept_name(genRandDeptString());  //�������� ������ �а��̸��� student�� �а��̸����� ����
	student.setGPA(Gpa);  //�������� ����( 0.0 ~ 99.99 )�� ������ student�� �������� ����

	return student;
}

void genST_ids(int num_sutdents, int* st_ids)
{
	int* flag = NULL;
	int rand_h, rand_l, big_id;
	int count = 0, True = 0;

	flag = new int[num_sutdents];
	//time(NULL);
	while (count < num_sutdents)
	{
		rand_h = rand();
		rand_l = rand();
		big_id = ((rand_h << 15) | rand_l) % 40001 + 10000; //10000 ~ 50000

		for (int i = 0; i <= count; i++)
		{
			if (flag[i] == big_id)  
				True += 1; 
		}

		if (True <= 0)  //�ߺ�����������
		{
			flag[count] = big_id;
			st_ids[count] = big_id;

			count++;
		}
		else  //�ߺ��Ǹ�
			continue;  //�ٽ� while��
	}
	delete[]flag;

}
