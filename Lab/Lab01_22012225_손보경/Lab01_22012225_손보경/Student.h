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

/* 구조체 struct Student 설계 및 구현 */
void initStudents(Student students[], int st_ids[], int num_students);
void printStudent(Student* pSt);  //주어진 학생 구조체의 내용을 출력하는 함수
void printStudents(Student* students, int num_students);  //학생들의 배열 출력. printStudent함수 사용.
void printStudentID(Student* students, int num_students); //학번만을 출력하는 함수
void printBigArrayOfStudent_IDs(Student *students, int num_students, int num_first_last); //num_first_last는 배열의 첫부분과 끝부분에서 출력되는 학생 수
void printStudentGPA_ID(Student* students, int num_students); //성적과 학번 출력
void printBigArrayOfStudent_GPA_IDs(Student *students, int num_students, int num_first_last); //성적과 학번을 출력, 배열의 첫부분과 끝부분 출력


/* 구조체 배열의 선택정렬과 이진 탐색을 위한 함수 */
void selectionSortStudentsBy_ID(Student* students, int num_students); //학번의 오름차순으로 선택 정렬
void selectionSortStudentsByGPA_ID(Student* students, int num_students); //GPA의 내림차순으로 정렬, GPA동일할 경우 학번 오른차순으로 정렬.
Student* binarysearchStudentByID(Student *students, int num_students, int st_id);//학번기준으로 이진 탐색 기능 수행



void fprintStudent(ostream& fout, Student* pSt);
void fprintStudents(ostream& fout, Student* students, int num_students);
void fprintStudentID(ofstream& fout, Student* students, int num_students);
void fprintBigArrayOfStudent_IDs(ofstream& fout, Student students[], int num_students, int num_first_last);
void fprintStudentGPA_ID(ofstream& fout, Student* students, int num_students);
void fprintBigArrayOfStudent_GPA_IDs(ofstream& fout, Student students[], int num_students, int num_first_last);

void sortStudentsByID(Student students[], int num_students);
void sortStudentsByGPA_ID(Student students[], int num_students);
