#include "Student.h"

void initStudents(Student students[], int st_ids[], int num_students)
{
	int name_len;
	int j, grade;
	double br;
	srand(time(NULL));
	for (int i = 0; i < num_students; i++)
	{
		students[i].st_id = st_ids[i];
		name_len = rand() % 11 + 5; // 5 ~ 15
		students[i].name[0] = rand() % 26 + 'A'; //처음문자는 대문자로 하기위해
		for (j = 1; j < name_len; j++)
			students[i].name[j] = rand() % 26 + 'a'; //두번째문자부터는 소문자로 하기위해
		students[i].name[j] = NULL; //구조체 배열의 끝을 알림
		
		name_len = rand() % 3 + 3;  // 3 ~ 5
		for (j = 0; j < name_len; j++)
			students[i].dept[j] = rand() % 26 + 'A';  //대문자로 표시하기위해
		students[i].dept[j] = NULL;
		students[i].grade = rand() % 8 + 1; //1 ~ 8
		students[i].gpa = (rand() % 10000) / 100.0;  //0.00 ~ 99.99
	}
}

void printStudent(Student* pSt)
{
	int count = 0;
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout << "Student(ID: " << setw(4) << pSt->st_id;
	cout << ", Name: " << setw(16) << pSt->name;
	cout << ", Dept : " << setw(6) << pSt->dept;
	cout << ", Grade : " << pSt->gpa;
}

void printStudents(Student* students, int num_students)
{
	Student pSt;

	for (int i = 0; i < num_students; i++)
	{
		pSt = students[i];
		printStudent(&pSt);
	}
}

void printStudentID(Student *students, int num_students)
{
	cout << setw(6) << students->st_id;
}

void printBigArrayOfStudent_IDs(Student* students, int num_students, int num_first_last)
{
	Student pSt;
	int count = 0;

	if (num_students <= num_first_last * 2)  //총 학생수가 출력하는 학생수보다 작으면
	{
		for (int i = 0; i < num_students; i++)
		{
			pSt = students[i];

			printStudentID(&pSt, num_students);
			count++;
			if (count % 10 == 0)
				cout << endl;
		}
		return;
	}
	for (int i = 0; i < num_first_last; i++)
	{
		pSt = students[i];

		printStudentID(&pSt, num_students);
		count++;
		if (count % 10 == 0)
			cout << endl;
	}
	cout << ". . . . ." << endl;
	count = 0;
	for (int i = num_students - num_first_last; i < num_students; i++)
	{
		pSt = students[i];
		printStudentID(&pSt, num_students);
		count++;
		if (count % 10 == 0)
			cout << endl;
	}
}

void printStudentGPA_ID(Student* students, int num_students)
{
	cout.setf(ios::fixed); //고정 소수점 표시
	cout.setf(ios::showpoint); //소수점 표시
	cout.precision(2); //소수점 2자리까지 표시

	cout << " (" << setw(5) << students->gpa << "," << setw(6) << students->st_id << ") ";
}

void printBigArrayOfStudent_GPA_IDs(Student* students, int num_students, int num_first_last)
{
	Student pSt;
	int count = 0;

	for (int i = 0; i < num_first_last; i++)
	{
		pSt = students[i];

		printStudentGPA_ID(&pSt, count);
		count++;
		if (count % 10 == 0)
			cout << endl;

	}

	cout << " . . . . ." << endl;
	count = 0;
	for (int i = num_students - num_first_last; i < num_students; i++)
	{
		pSt = students[i];
		printStudentGPA_ID(&pSt, count);
		count++;
		if (count % 10 == 0)
			cout << endl;
	}

}

void selectionSortStudentsBy_ID(Student* students, int num_students) //학번의 오름차순으로 선택 정렬
{
	int i, j;
	int min_id, min_pos;
	Student temp;  //구조체 배열을 swap하기위함

	for (i = 0; i < num_students - 1; i++)
	{
		min_pos = i;  
		for (j = i + 1; j < num_students; j++)
		{
			if (students[j].st_id < students[min_pos].st_id)  //j번째 학생번호가 min_pos번째 학생번호보다 작으면
				min_pos = j;  //min_pos를 j로 바꿔줌
		}

		if (min_pos != i)  //min_pos가 i가 아니라면 즉, 정렬이 되어있지않았다면
		{
			/* swapping */
			temp = students[i];
			students[i] = students[min_pos];
			students[min_pos] = temp;
		}
	}
}

void selectionSortStudentsByGPA_ID(Student* students, int num_students) //GPA의 내림차순으로 정렬, GPA동일할 경우 학번 오른차순으로 정렬.
{
	int i, j;
	double min_gpa;
	int min_pos;
	Student temp;

	for (i = 0; i < num_students - 1; i++)
	{
		min_pos = i;
		for (j = i + 1; j < num_students; j++)
		{
			if (students[j].gpa > students[min_pos].gpa) 
				min_pos = j;
			else if (students[j].gpa == students[min_pos].gpa)  //성적이 같으면
			{
				if (students[j].st_id < students[min_pos].st_id) //
					min_pos = j;
			}
		}

		if (min_pos != i)  //min_pos가 i가 아니라면 즉, 정렬이 되어있지않았다면
		{
			/* swapping */
			temp = students[i];
			students[i] = students[min_pos];
			students[min_pos] = temp;
		}
	}
}

Student* binarysearchStudentByID(Student* students, int num_students, int st_id)
{
	int mid, low, high;

	low = 0;
	high = num_students - 1;

	while (low <= high)
	{
		mid = (low + high) / 2;  //반씩 나눠가며 찾기위해
		if (st_id == students[mid].st_id)  //찾아야하는 학번과 mid인덱스 학번이 같으면
			return &students[mid];
		else if (st_id < students[mid].st_id)  //mid인덱스의 학번보다 찾아야하는 학번이 더작으면
			high = mid - 1; //high(맨오른쪽)을 mid-1로 변경
		else  //mid인덱스의 학번보다 찾아야하는 학번이 더 크면
			low = mid + 1;  //low(맨왼쪽)을 mid+1로 변경
	}
	return 0;
}



void fprintStudent(ostream& fout, Student* pSt)
{
	int count = 0;
	fout.setf(ios::fixed);
	fout.setf(ios::showpoint);
	fout.precision(2);
	fout << "Student(ID: " << setw(4) << pSt->st_id;
	fout << ", Name: " << setw(16) << pSt->name;
	fout << ", Dept : " << setw(6) << pSt->dept;
	fout << ", Grade : " << pSt->gpa;
}

void fprintStudents(ostream& fout, Student* students, int num_students)
{
	Student pSt;

	for (int i = 0; i < num_students; i++)
	{
		pSt = students[i];
		fprintStudent(fout, &pSt);
	}
}

void fprintStudentID(ofstream& fout, Student* students, int num_students)
{
	fout << setw(6) << students->st_id;
}

void fprintBigArrayOfStudent_IDs(ofstream& fout, Student students[], int num_students, int num_first_last)
{
	Student pSt;
	int count = 0;
	if (num_students <= num_first_last * 2)
	{
		for (int i = 0; i < num_students; i++)
		{
			pSt = students[i];
			fprintStudentID(fout, &pSt, num_students);
			count++;
			if ((count % 10) == 0)
				fout << endl;
		}
		return;
	}
	for (int i = 0; i < num_first_last; i++)
	{
		pSt = students[i];
		fprintStudentID(fout, &pSt, num_students);
		count++;
		if ((count % 10) == 0)
			fout << endl;
	}

	fout << " . . . . . " << endl;
	count = 0;

	for (int i = num_students - num_first_last; i < num_students; i++)
	{
		pSt = students[i];
		fprintStudentID(fout, &pSt, num_students);
		count++;
		if ((count % 10) == 0)
			fout << endl;
	}
}

void fprintStudentGPA_ID(ofstream& fout,Student* students, int num_students)
{
	fout.setf(ios::fixed); //고정 소수점 표시
	fout.setf(ios::showpoint); //소수점 표시
	fout.precision(2); //소수점 2자리까지 표시

	fout << "(" << setw(5) << students->gpa << "," << setw(6) << students->st_id << ")";
}

void fprintBigArrayOfStudent_GPA_IDs(ofstream& fout, Student students[], int num_students, int num_first_last)
{
	Student pSt;
	int count = 0;

	for (int i = 0; i < num_first_last; i++)
	{
		pSt = students[i];

		fprintStudentGPA_ID(fout, &pSt, count);
		count++;
		if (count % 10 == 0)
			fout << endl;

	}

	fout << " . . . . ." << endl;
	count = 0;
	for (int i = num_students - num_first_last; i < num_students; i++)
	{
		pSt = students[i];
		fprintStudentGPA_ID(fout, &pSt, count);
		count++;
		if (count % 10 == 0)
			fout << endl;
	}

}



void sortStudentsByID(Student students[], int num_students)
{
	int i, j, mx;
	char minName[16] = { 0 };
	Student tmp;
	int min_st, min_ID;
	for (i = 0; i < num_students - 1; i++)
	{
		min_st = i;
		min_ID = students[min_st].st_id;
		for (j = i + 1; j < num_students; j++)
		{
			if (students[j].st_id < min_ID)
			{
				min_st = j;
				min_ID = students[j].st_id;
			}
		}
		if (min_st != i)
		{
			tmp = students[i];
			students[i] = students[min_st];
			students[min_st] = tmp;
		}
	}
}



void sortStudentsByGPA_ID(Student students[], int num_students)
{
	int i, j;
	double min_gpa;
	int min_num;
	Student temp;

	for (i = 0; i < num_students - 1; i++)
	{
		min_num = i;
		for (j = i + 1; j < num_students; j++)
		{
			if (students[j].gpa > students[min_num].gpa)
				min_num = j;
			else if (students[j].gpa == students[min_num].gpa)  //성적이 같으면
			{
				if (students[j].st_id < students[min_num].st_id) //
					min_num = j;
			}
		}

		if (min_num != i)
		{
			temp = students[i];
			students[i] = students[min_num];
			students[min_num] = temp;
		}
	}
}


