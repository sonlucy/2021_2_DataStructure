/***
* Lab05
* ��� Ŭ����
* �л��迭���� �й�, �̸�, ����, ������� �� ����
* 
* �ۼ���: ������Ű��а� 22012225 �պ���
* �ۼ�����: 2021-10-01
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
	StudentArray studentArray(NUM_STUDENTS);   //10���� �л� ����
	Student st;
	ofstream fout;
	int st_ids[NUM_STUDENTS];
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open an output file (output.txt)\n";
		exit(1);
	}
	genST_ids(NUM_STUDENTS, st_ids);   //�ߺ������ʴ� �й� ���� 
	fout << "Initializing student array (num_students: " << NUM_STUDENTS << ")" << endl;
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		st = genRandStudent(st_ids[i]); //���� �л� ������ ���Ƿ� ����
		studentArray[i] = st;  //����
	}
	fout << studentArray;

	fout << "\nSorting studentArray by student id : " << endl;
	studentArray.sortByST_ID();
	fout << studentArray;

	fout << "\nSorting studentArray by student name : " << endl;
	studentArray.sortByName();
	fout << studentArray;

	fout << "\nSorting studentArray by GPA : " << endl;  //��������
	studentArray.sortByGPA();
	fout << studentArray;

	fout << "\nSorting studentArray by BirthDate : " << endl;
	studentArray.sortByBirthDate();
	fout << studentArray;

	fout << endl;
	fout.close();
}

