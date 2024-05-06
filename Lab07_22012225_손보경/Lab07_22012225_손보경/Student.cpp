#include "Student.h"
#include <iomanip>

ostream& operator<<(ostream& fout, Student& st)
{
	fout << "Student [ st_id: " << setw(5) << st.st_id;
	fout << ", name: " << setw(7) << std::left << st.name;
	fout << ", gpa: ";
	fout.precision(2);
	fout.setf(ios::fixed);
	fout.setf(ios::showpoint);
	fout << setw(5) << st.gpa;
	fout << ", date_of_birth: " << st.dateOfBirth;
	fout << ", arrival: " << std::right << st.arrivalTime << "]";
	return fout;
}
Student::Student() // default constructor
{
	name = "nobody";  //
	arrivalTime = Time(0, 0, 0);
	st_id = 0;
	gpa = 0.0;
}
Student::Student(int id, string n, Date dob, Time avt, double g)
{
	name = n;  //
	dateOfBirth = dob;
	arrivalTime = avt;
	st_id = id;
	gpa = g;
}

bool Student::operator<(const Student& other) const
{
	if (this->st_id < other.st_id)
		return true;
	else
		return false;
}
bool Student::operator<=(const Student& other) const
{
	if (this->st_id <= other.st_id)
		return true;
	else
		return false;
}
bool Student::operator>(const Student& other) const
{
	if (this->st_id > other.st_id)
		return true;
	else
		return false;
}
bool Student::operator>=(const Student& other) const
{
	if (this->st_id >= other.st_id)
		return true;
	else
		return false;
}
bool Student::operator==(const Student& other) const
{
	if (this->st_id == other.st_id)
		return true;
	else
		return false;
}



void Student::getKey(string keyName, void* pKey) //void :자료형 지정x
{
	/* pKey가 가리키는 데이터 멤버의 자료형으로 만들어준후 
	해당 클래스의 데이터멤버로 할당 */
	if (keyName == "ST_ID")
		*(int*)pKey = this->st_id;
	else if (keyName == "ST_NAME")
		*(string*)pKey = this->name;
	else if (keyName == "GPA")
		*(double*)pKey = this->gpa;
	else if (keyName == "ARRIVAL_TIME")
		*(Time*)pKey = this->arrivalTime;
	else if (keyName == "BIRTH_DATE")
		*(Date*)pKey = this->dateOfBirth;
	else
		pKey = NULL;
}