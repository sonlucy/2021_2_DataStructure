/***
* 객체지향프로그래밍 Lab 01
* 구조체 배열의 정렬과 탐색
* 
* 작성자: 정보통신공학과 22012225 손보경 (2021년 9월 1일)
* 작성일자:2021-09-02
* 최종 수정 및 보완: 2021-09-03
* 
***/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Student.h"
using namespace std;

#define NUM_STUDENTS 5000
#define NUM_SEARCH 5
#define NUM_FIRST_LAST_BLOCK 100

void genBigRandArray(int *randArray, int num_rands);

void main()
{
	ofstream fout;
	int* student_ids;
	Student* students, * pSt;
	int studentID_search[NUM_SEARCH] = { 1, 123, 999, 2500, 4999 };

	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Error in opening output.txt" << endl;
		exit;
	}

	student_ids = (int*)malloc(sizeof(int) * NUM_STUDENTS);
	students = (Student*)malloc(sizeof(Student) * NUM_STUDENTS);
	genBigRandArray(student_ids, NUM_STUDENTS); //중복되지않는 난수 생성 (학번)
	initStudents(students, student_ids, NUM_STUDENTS); //학번 초기화

	fout << endl << endl;
	fout << "Initialized array of students : " << endl;
	cout << endl << endl;
	cout << "Initialized array of students : " << endl;
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK); //////
	printBigArrayOfStudent_IDs(students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);

	fout << endl << endl;
	fout << "Selection sorting array of students by increasing order of ID : " << endl;
	cout << endl << endl;
	cout << "Selection sorting array of students by increasing order of ID : " << endl;
	sortStudentsByID(students, NUM_STUDENTS);  //////
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);/////
	selectionSortStudentsBy_ID(students, NUM_STUDENTS);
	printBigArrayOfStudent_IDs(students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);

	fout << endl << endl;
	fout << "Seletion sorting array of students by (decreasing order of GPA, increasing order of ID) : " << endl;
	cout << endl << endl;
	cout << "Seletion sorting array of students by (decreasing order of GPA, increasing order of ID) : " << endl;
	sortStudentsByGPA_ID(students, NUM_STUDENTS); ///// non-increasing order 성적순 정렬
	fprintBigArrayOfStudent_GPA_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);  /////
	selectionSortStudentsByGPA_ID(students, NUM_STUDENTS);
	printBigArrayOfStudent_GPA_IDs(students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);

	fout << endl << endl;
	fout << "Selection sorting array of students by increasing order of ID : " << endl;
	cout << endl << endl;
	cout << "Selection sorting array of students by increasing order of ID : " << endl;
	sortStudentsByID(students, NUM_STUDENTS);  //////학번순 정렬
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);  ///////
	selectionSortStudentsBy_ID(students, NUM_STUDENTS);
	printBigArrayOfStudent_IDs(students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	
	fout << endl << endl;
	fout << "Searching student with student_ID : " << endl;
	cout << endl << endl;
	cout << "Searching student with student_ID : " << endl;
	for (int i = 0; i < NUM_SEARCH; i++)
	{
		pSt = binarysearchStudentByID(students, NUM_STUDENTS, studentID_search[i]);
		fout << "Student search by ID (" << setw(4) << studentID_search[i] << ") : ";
		cout << "Student search by ID (" << setw(4) << studentID_search[i] << ") : ";

		if (pSt != NULL)
		{
			fprintStudent(fout, pSt);
			printStudent(pSt);
		}
		else
		{
			fout << "NULL - student was not found !!";
			cout << "NULL - student was not found !!";

		}

		fout << endl;
		cout << endl;
	}

	fout.close();
}


void genBigRandArray(int *randArray, int num_rands)
{
	char* flag;
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand;
	flag = (char*)calloc(sizeof(char), num_rands); //동적배열생성
	srand(time(NULL)); 

	while (count < num_rands)  //함수로부터 전달받은 num_rands크기동안
	{
		u_int32 = ((long)rand() << 15) | rand(); //왼쪽으로 15비트만큼 shift시키고 다시 rand시켜 비트or연산
		bigRand = u_int32 % num_rands; //모듈로연산을 통해 범위 지정( 0 ~ num_rands-1 )
		if (flag[bigRand] == 1) {  //이미 생성되었던 난수면
			continue;   //그냥 continue해서 다시 rand실행
		}
		flag[bigRand] = 1;  //이미 생성되었던 난수가 아니면 1로 바꿔주어서 생성되었던 난수라는 표시를 해줌
		randArray[count++] = bigRand;
	}
}