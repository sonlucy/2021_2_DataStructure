#include "Date.h"
#include "Person.h"
#define NUM_PERSON 10
using namespace std;

ostream& operator<< (ostream&  fout, const Person& pe)
{
	fout.setf(ios::showpoint);
	fout.setf(ios::fixed);
	fout.precision(2);
	fout << "Person [ name : " << setw(7) << pe.name << ", " << pe.birthDate << " ] " << endl;

	return fout;
}

Person& Person:: operator=(const Person& pe)
{
	birthDate = pe.birthDate;
	name = pe.name; 

	return *this;

	/*Person p(name, birthDate);
	p.birthDate = pe.birthDate;
	p.name = pe.name;

	return p;*/
}
