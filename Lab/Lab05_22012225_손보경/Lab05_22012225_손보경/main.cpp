/***
* Lab05
* 상속 클래스
* 학생배열에서 학번, 이름, 학점, 생년월일 순 정렬
* 
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자: 2021-10-01
* 
***/

#include <iostream>
#include <fstream>
#include "StudentArray.h"
#include <string>
#define NUM_STUDENTS 10
using namespace std;


void main()
{
	StudentArray studentArray(NUM_STUDENTS);   //10명의 학생 정보
	Student st;
	ofstream fout;
	int st_ids[NUM_STUDENTS];
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open an output file (output.txt)\n";
		exit(1);
	}
	genST_ids(NUM_STUDENTS, st_ids);   //중복되지않는 학번 생성 
	fout << "Initializing student array (num_students: " << NUM_STUDENTS << ")" << endl;
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		st = genRandStudent(st_ids[i]); //각각 학생 정보를 임의로 생성
		studentArray[i] = st;  //대입
	}
	fout << studentArray;

	fout << "\nSorting studentArray by student id : " << endl;
	studentArray.sortByST_ID();
	fout << studentArray;

	fout << "\nSorting studentArray by student name : " << endl;
	studentArray.sortByName();
	fout << studentArray;

	fout << "\nSorting studentArray by GPA : " << endl;  //내림차순
	studentArray.sortByGPA();
	fout << studentArray;

	fout << "\nSorting studentArray by BirthDate : " << endl;
	studentArray.sortByBirthDate();
	fout << studentArray;

	fout << endl;
	fout.close();
}

