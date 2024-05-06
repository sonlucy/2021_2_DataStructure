#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

typedef struct s_Student
{
	int st_id;
	char name[16];
	char dept[16];
	int grade;
	double gpa;
} Student;

/* ����ü struct Student ���� �� ���� */
void initStudents(Student students[], int st_ids[], int num_students);
void printStudent(Student* pSt);  //�־��� �л� ����ü�� ������ ����ϴ� �Լ�
void printStudents(Student* students, int num_students);  //�л����� �迭 ���. printStudent�Լ� ���.
void printStudentID(Student* students, int num_students); //�й����� ����ϴ� �Լ�
void printBigArrayOfStudent_IDs(Student *students, int num_students, int num_first_last); //num_first_last�� �迭�� ù�κа� ���κп��� ��µǴ� �л� ��
void printStudentGPA_ID(Student* students, int num_students); //������ �й� ���
void printBigArrayOfStudent_GPA_IDs(Student *students, int num_students, int num_first_last); //������ �й��� ���, �迭�� ù�κа� ���κ� ���


/* ����ü �迭�� �������İ� ���� Ž���� ���� �Լ� */
void selectionSortStudentsBy_ID(Student* students, int num_students); //�й��� ������������ ���� ����
void selectionSortStudentsByGPA_ID(Student* students, int num_students); //GPA�� ������������ ����, GPA������ ��� �й� ������������ ����.
Student* binarysearchStudentByID(Student *students, int num_students, int st_id);//�й��������� ���� Ž�� ��� ����



void fprintStudent(ostream& fout, Student* pSt);
void fprintStudents(ostream& fout, Student* students, int num_students);
void fprintStudentID(ofstream& fout, Student* students, int num_students);
void fprintBigArrayOfStudent_IDs(ofstream& fout, Student students[], int num_students, int num_first_last);
void fprintStudentGPA_ID(ofstream& fout, Student* students, int num_students);
void fprintBigArrayOfStudent_GPA_IDs(ofstream& fout, Student students[], int num_students, int num_first_last);

void sortStudentsByID(Student students[], int num_students);
void sortStudentsByGPA_ID(Student students[], int num_students);
