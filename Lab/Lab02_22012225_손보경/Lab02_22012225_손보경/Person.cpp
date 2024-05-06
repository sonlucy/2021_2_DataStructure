#include "Date.h"
#include "Person.h"
#define NUM_PERSON 10


void Person::setRandPersonAttributes()  //이름을 랜덤으로 만들어 포함
{
	char str[MAX_NAME_LEN + 1];
	int name_len, i = 0;
	
	birthDate.setRandDateAttributes();
	//srand(time(NULL));

	name_len = rand() % (MAX_NAME_LEN - MIN_NAME_LEN) + MIN_NAME_LEN;
	str[0] = rand() % 26 + 'A';
	for (i = 1; i < name_len; i++)
		str[i] = rand() % 26 + 'a';
	str[i] = '\0';

	name = string(str);
}
void Person::fprintPerson(ostream& fout)
{
	fout << " Person [name: ";
	fout.setf(ios::left);
	fout << setw(16) << name;
	fout << ", birth date: ";
	fout.unsetf(ios::left);
	birthDate.fprintDate(fout);
	fout << "]";
}
void Person::printPerson()
{
	cout << " Person [name: ";
	cout.setf(ios::left);
	cout << setw(16) << name;
	cout << ", birth date: ";
	cout.unsetf(ios::left);
	birthDate.printDate();
	cout << "]";
}
Person Person::selectionPersonBy_name(Person *persons)
{
	int i, j;
	int min_name, min_pos;
	Person temp;

	for (i = 0; i < NUM_PERSON - 1; i++)
	{
		min_pos = i;
		for (j = i + 1; j < NUM_PERSON; j++)
		{
			if (persons[j].name<persons[min_pos].name)
			{
				min_pos = j;
			}
			
		}
		if (min_pos != i)
		{
			temp = persons[i];
			persons[i] = persons[min_pos];
			persons[min_pos] = temp;

		}
	}

	return *persons;
}

Person Person::selectionPersonBy_birth(Person* persons)
{
	int i, j;
	int min_birth, min_pos;
	Person temp;
	//Date D;

	for (i = 0; i < NUM_PERSON - 1; i++)
	{
		min_pos = i;
		for (j = i + 1; j < NUM_PERSON; j++)
		{
			if (persons[j].birthDate.sortingforbirth_year() < persons[min_pos].birthDate.sortingforbirth_year())
				min_pos = j;
			else if (persons[j].birthDate.sortingforbirth_year() == persons[min_pos].birthDate.sortingforbirth_year())
			{
				if (persons[j].birthDate.sortingforbirth_month() < persons[min_pos].birthDate.sortingforbirth_month())
					min_pos = j;
				else if (persons[j].birthDate.sortingforbirth_day() == persons[min_pos].birthDate.sortingforbirth_day())
				{
					if (persons[j].birthDate.sortingforbirth_day() < persons[min_pos].birthDate.sortingforbirth_day())
						min_pos = j;
				}
					
			}

		}
		if (min_pos != i)
		{
			temp = persons[i];
			persons[i] = persons[min_pos];
			persons[min_pos] = temp;
		}
	}
	return *persons;
}
