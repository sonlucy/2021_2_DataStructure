/***
* ��ü�������α׷��� Lab 01
* ����ü �迭�� ���İ� Ž��
* 
* �ۼ���: ������Ű��а� 22012225 �պ��� (2021�� 9�� 1��)
* �ۼ�����:2021-09-02
* ���� ���� �� ����: 2021-09-03
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
	genBigRandArray(student_ids, NUM_STUDENTS); //�ߺ������ʴ� ���� ���� (�й�)
	initStudents(students, student_ids, NUM_STUDENTS); //�й� �ʱ�ȭ

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
	sortStudentsByGPA_ID(students, NUM_STUDENTS); ///// non-increasing order ������ ����
	fprintBigArrayOfStudent_GPA_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);  /////
	selectionSortStudentsByGPA_ID(students, NUM_STUDENTS);
	printBigArrayOfStudent_GPA_IDs(students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);

	fout << endl << endl;
	fout << "Selection sorting array of students by increasing order of ID : " << endl;
	cout << endl << endl;
	cout << "Selection sorting array of students by increasing order of ID : " << endl;
	sortStudentsByID(students, NUM_STUDENTS);  //////�й��� ����
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
	flag = (char*)calloc(sizeof(char), num_rands); //�����迭����
	srand(time(NULL)); 

	while (count < num_rands)  //�Լ��κ��� ���޹��� num_randsũ�⵿��
	{
		u_int32 = ((long)rand() << 15) | rand(); //�������� 15��Ʈ��ŭ shift��Ű�� �ٽ� rand���� ��Ʈor����
		bigRand = u_int32 % num_rands; //���ο����� ���� ���� ����( 0 ~ num_rands-1 )
		if (flag[bigRand] == 1) {  //�̹� �����Ǿ��� ������
			continue;   //�׳� continue�ؼ� �ٽ� rand����
		}
		flag[bigRand] = 1;  //�̹� �����Ǿ��� ������ �ƴϸ� 1�� �ٲ��־ �����Ǿ��� ������� ǥ�ø� ����
		randArray[count++] = bigRand;
	}
}