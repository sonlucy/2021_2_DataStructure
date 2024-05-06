/*
* HW07
* 도착시간 기준으로 정렬
* 
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자: 2021-10-16
*/

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "T_Array.h"
#include "Student.h"
using namespace std;
#define ELEMENTS_PER_LINE 10
#define SAMPLE_LINES 5
#define NUM_ELEMENTS 500
#define MIN_NUM_ELEMENTS 10
#define NUM_STUDENTS 10  

Student students[10] =
{
	Student(21811000, string("Kim, G-M"), Date(1990, 10, 5), Time(3, 0, 30), 3.57),
	Student(21611075, string("Yoon, S-M"), Date(1990, 4, 5), Time(7, 30, 0), 4.37),
	Student(21411015, string("Hwang, S-S"), Date(1989, 1, 10), Time(2, 0, 50), 2.72),
	Student(21611054, string("Lee, K-M"), Date(1991, 5, 15), Time(5, 30, 0), 3.35),
	Student(21311340, string("Hong, G-M"), Date(1990, 2, 5), Time(1, 10, 0), 3.89),
	Student(6543, string("Jang, S-M"), Date(2000, 5, 21), Time(9, 20, 10), 4.42),
	Student(7080, string("Park, S-T"), Date(2001, 5, 1), Time(1, 20, 15), 4.12),
	Student(9564, string("Choi, Y-H"), Date(1997, 6, 10), Time(10, 0, 0), 3.85),
	Student(1000, string("Shin, D-J"), Date(2003, 4, 5), Time(11, 15, 10), 3.21),
	Student(8812, string("Ahn, S-B"), Date(1997, 1, 1), Time(2, 0, 5), 4.45),
};


void main()
{
	ofstream fout;
	T_Array<Student> studentArray(NUM_STUDENTS, "Array of Students");  ////
	Student *pStudent;

	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open output.txt file for results !!" << endl;
		exit;
	}
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		pStudent = &students[i];
		studentArray.insert(i, *pStudent);  ////i위치에 pStudent원소 추가
	}

	fout << "Elements in studentArray after initialization :" << endl;
	studentArray.fprint(fout, 1);

	fout << "Elements in studentArray after sorting :" << endl;
	studentArray.selection_sort(INCREASING);   //오름차순 선택정렬
	studentArray.fprint(fout, 1);
	
	fout << "Elements in studentArray after sorting :" << endl;
	studentArray.quick_sort(DECREASING);   //내림차순 퀵정렬
	studentArray.fprint(fout, 1);

	fout.close();
}

