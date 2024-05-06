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
	Person::operator= (pe);  //상속된 클래스의 대입연산자 구현

	/* 나머지부분 초기화 */
	st_id = pe.st_id;
	dept_name = pe.dept_name; 
	gpa = pe.gpa;

	return *this;
}


Student::Student()
	:Person("NULL", Date(1, 1, 1))  //부모클래스 생성자 불러와서 초기화
{
	/* 나머지 Student 멤버들 초기화 */
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

	student.setST_id(id);  //전달받은 id값을 student의 학번으로 설정
	student.setName(genRandName()); //랜덤으로 생성한 이름 student의 이름으로 설정
	student.setBirthDate(genRandDate());  //랜덤으로 생성한 날짜 student의 날짜로 설정
	student.setDept_name(genRandDeptString());  //랜덤으로 생성한 학과이름을 student의 학과이름으로 설정
	student.setGPA(Gpa);  //랜덤으로 생성( 0.0 ~ 99.99 )한 학점을 student의 학점으로 설정

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

		if (True <= 0)  //중복되지않으면
		{
			flag[count] = big_id;
			st_ids[count] = big_id;

			count++;
		}
		else  //중복되면
			continue;  //다시 while문
	}
	delete[]flag;

}
