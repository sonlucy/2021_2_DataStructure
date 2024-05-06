#include "Student.h"
#include "Date.h"
#include <iomanip>
//#include <string>
//#include <string>


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
Student::Student(int id, string n,  Date dob, Time avt, double g)
{
	name = n;  //
	dateOfBirth = dob;
	arrivalTime = avt;
	st_id = id;
	gpa = g;
}

bool Student::operator<( Student& other) 
{
	if (this->arrivalTime < other.arrivalTime)
		return true;
	else
		return false;
}
bool Student::operator<=( Student& other) 
{
	if (this->arrivalTime <= other.arrivalTime)
		return true;
	else
		return false;
}
bool Student::operator>( Student& other) 
{
	if (this->arrivalTime > other.arrivalTime)
		return true;
	else
		return false;
}
bool Student::operator>=( Student& other) 
{
	if (this->arrivalTime >= other.arrivalTime)
		return true;
	else
		return false;
}
bool Student::operator==( Student& other) 
{
	if (this->arrivalTime == other.arrivalTime)
		return true;
	else
		return false;
}

