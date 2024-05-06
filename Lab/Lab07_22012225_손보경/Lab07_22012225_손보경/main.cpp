/*
* Lab07
* 
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자: 2021-10-15
*/

#include <iostream>
#include <conio.h> # for _getch()
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Person.h"
#include "Time.h"
#include "Date.h"
#include "T_Array.h"
#include "Student.h"
#include "VectorHandler.h"
using namespace std;
#define NUM_TIMES 10
#define NUM_DATES 10
#define NUM_STUDENTS 10
#define STEP_1
#define STEP_2
#define STEP_3
#define STEP_4



void main()
{

#ifdef STEP_1
	Time times[NUM_TIMES] =
	{
		Time(3, 0, 30), Time(7, 30, 0), Time(2, 0, 50), Time(5, 30, 0), Time(1, 10, 0),
		Time(9, 20, 10), Time(1, 20, 15), Time(10, 0, 0), Time(11, 15, 10), Time(2, 0, 5)
	};

	vector<Time> v_times(times, times + NUM_TIMES); //vector
	cout << "Initial v_times : " << endl;
	printVector(v_times);

	sort(v_times.begin(), v_times.end());  ////sort
	cout << "After sort() : " << endl;
	printVector(v_times);


	Date dates[10] =
	{
		Date(2003, 4, 5), Date(2002, 7, 15), Date(2001, 5, 1), Date(2001, 3, 10), Date(2000, 5, 21),
		Date(2000, 3, 1), Date(1999, 12, 25), Date(1998, 10, 9), Date(1997, 6, 10), Date(1996, 1, 1)
	};
	vector<Date> v_dates(dates, dates + NUM_DATES);  //vector
	cout << "Initial v_dates :" << endl;
	printVector(v_dates);

	sort(v_dates.begin(), v_dates.end()); ///sort
	cout << "After sort() : " << endl;
	printVector(v_dates);

	cout << "Hit any key to continue .... ";
	_getch();
	cout << endl;
#endif

	Student students[NUM_STUDENTS] =
	{
		Student(5234, string("Kim, G-M"), Date(2002, 7, 15), Time(3, 0, 30), 3.57),
		Student(1999, string("Yoon, S-M"), Date(1999, 12, 25), Time(7, 30, 0), 4.37),
		Student(4141, string("Byun, S-S"), Date(2001, 3, 10), Time(2, 0, 50), 2.72),
		Student(2167, string("Lee, K-M"), Date(1998, 10, 9), Time(5, 30, 0), 3.35),
		Student(3890, string("Hong, G-M"), Date(2000, 3, 1), Time(1, 10, 0), 3.89),
		Student(6543, string("Jang, S-M"), Date(2000, 5, 21), Time(9, 20, 10), 4.42),
		Student(7080, string("Park, S-T"), Date(2001, 5, 1), Time(1, 20, 15), 4.12),
		Student(9564, string("Choi, Y-H"), Date(1997, 6, 10), Time(10, 0, 0), 3.85),
		Student(1000, string("Shin, D-J"), Date(2003, 4, 5), Time(11, 15, 10), 3.21),
		Student(8812, string("Ahn, S-B"), Date(1997, 1, 1), Time(2, 0, 5), 4.45),
	};

#ifdef STEP_2


	vector<Student> v_students(students, students + NUM_DATES);  //vector
	cout << "Initial v_students :" << endl;
	printVector(v_students);

	sort(v_students.begin(), v_students.end());  //sort()
	cout << "₩nstudents after sorting by st_id :" << endl;
	printVector(v_students);

	cout << "Hit any key to continue .... ";
	_getch();
	cout << endl;
#endif




#ifdef STEP_3
	///// Step 3 - Testing template array class T_Array<T, K> 
	//Student* pSt;   ////////////

	T_Array<Student, int> stArray_keyID(NUM_STUDENTS, "T_Array<Student, keyST_ID>");  //학번기준
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyID.insert(i, students[i]);
	}
	cout << "T_Array<Student_keyID> at initialization : " << endl;
	stArray_keyID.print(1);

	stArray_keyID.selection_sort(string("ST_ID"), INCREASING);  //학번기준 오름차순 정렬
	//stArray_keyID.quick_sort("ST_ID", INCREASING);
	//stArray_keyID.mergeSort("ST_ID", INCREASING);
	cout << "\nT_Array<Student_keyID> after sorting (increasing order) by ST_ID : " << endl;
	stArray_keyID.print(1);


	T_Array<Student, double> stArray_keyGPA(NUM_STUDENTS, "T_Array<Student, keyGPA>");  //GPA
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyGPA.insert(i, students[i]);
	}
	//stArray_keyGPA.selection_sort(string("GPA"), DECREASING);  //학점 내림차순 정렬
	stArray_keyGPA.mergeSort(string("GPA"), DECREASING);
	cout << "\nT_Array<Student, keyGPA> after sorting (decreasing order) by GPA : " << endl;
	stArray_keyGPA.print(1);

	cout << "Hit any key to continue .... ";
	_getch();
	cout << endl;
#endif 

#ifdef STEP_4 
	T_Array<Student, string> stArray_keyName(NUM_STUDENTS, "T_Array<Student, keyName > "); //이름
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyName.insert(i, students[i]);
	}
	stArray_keyName.selection_sort(string("ST_NAME"), INCREASING);  //이름 오름차순 정렬
	cout << "\nT_Array<Student_keyName> after sorting (increasing order) by name : " << endl;
	stArray_keyName.print(1);

	T_Array<Student, Date> stArray_keyDoB(NUM_STUDENTS, "Array of Students, date of birth as key");  //날짜
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyDoB.insert(i, students[i]);
	}

	stArray_keyDoB.selection_sort(string("BIRTH_DATE"), INCREASING);  //날짜 오름차순 정렬
	cout << "\nstArray_keyDoB after sorting (increasing order) by date of birth : " << endl;
	stArray_keyDoB.print(1);

	T_Array<Student, Time> stArray_keyTime(NUM_STUDENTS, "Array of Students, arrival time as key");  //시간
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyTime.insert(i, students[i]);
	}

	stArray_keyTime.selection_sort(string("ARRIVAL_TIME"), INCREASING);  //시간 기준 오름차순
	cout << "\nstArray_keyArrTm after sorting (increasing order) by arrival time : " << endl;
	stArray_keyTime.print(1);
#endif
}





