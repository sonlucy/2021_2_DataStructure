#include "StudentArray.h"

ostream& operator<<(ostream& fout, const StudentArray& st_A)
{
	for (int i = 0; i < st_A.num_students; i++)
	{
		fout << st_A.students[i] << endl;  
	}
	return fout;
}

StudentArray::StudentArray(int size)
{
	num_students = size;
	students = new Student[num_students];  //전달받은 크기만큼 students객체 동적생성
}

StudentArray::StudentArray(const StudentArray& obj)
{
	num_students = obj.num_students;
	for (int i = 0; i < num_students; i++)
	{
		students[i] = obj.students[i];
	}
}

StudentArray::~StudentArray()
{

}

Student& StudentArray::operator[](int index) const
{
	if (isValidIndex(index))
		return students[index];
	else
		exit;

}

bool StudentArray::isValidIndex(int index) const
{
	if ((index >= 0) && (index < num_students))
		return true;
	else
	{
		cout << "This index is not vaild. " << endl;
		return false;
	}
}

void StudentArray::sortByBirthDate()
{
	int min_index = 0;
	Student temp;

	for (int i = 0; i < num_students - 1; i++)
	{
		min_index = i;
		for (int j = i + 1; j < num_students; j++)
		{
			if (students[min_index].birthDate > students[j].birthDate)
				min_index = j;
		}
		if (i != min_index)
		{
			/* swapping */
			temp = students[i];
			students[i] = students[min_index];
			students[min_index] = temp;
		}
	}
}

void StudentArray::sortByName()
{
	int min_index = 0;
	Student temp;

	for (int i = 0; i < num_students - 1; i++)
	{
		min_index = i;
		for (int j = i + 1; j < num_students; j++)
		{
			if (students[min_index].name > students[j].name)
				min_index = j;
		}
		if (i != min_index)
		{
			/* swapping */
			temp = students[i];
			students[i] = students[min_index];
			students[min_index] = temp;
		}
	}

}

void StudentArray::sortByST_ID()
{
	int min_index = 0;
	Student temp;

	for (int i = 0; i < num_students - 1; i++)
	{
		min_index = i;
		for (int j = i + 1; j < num_students; j++)
		{
			if (students[min_index].st_id > students[j].st_id)
				min_index = j;
		}
		if (i != min_index)
		{
			/* swapping */
			temp = students[i];
			students[i] = students[min_index];
			students[min_index] = temp;
		}
	}
}

void StudentArray::sortByGPA()
{
	int min_index = 0;
	Student temp;

	for (int i = 0; i < num_students - 1; i++)
	{
		min_index = i;
		for (int j = i + 1; j < num_students; j++)
		{
			if (students[min_index].gpa < students[j].gpa)  //내림차순
				min_index = j;
		}
		if (i != min_index)
		{
			/* swapping */
			temp = students[i];
			students[i] = students[min_index];
			students[min_index] = temp;
		}
	}
}
