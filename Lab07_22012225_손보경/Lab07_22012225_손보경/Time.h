#ifndef TIME_H 
#define TIME_H 
#include <iostream> 
using namespace std;
class Time
{
	friend ostream& operator<<(ostream& fout, const Time& t)
	{
		fout << "(" << t.hour << ": " << t.min << ": " << t.sec << ") ";
		return fout;
	}
public:
	Time() { hour = 0; min = 0; sec = 0; } // default constructor 
	Time(int h, int m, int s);

	int elasedSec() const;
	Time getTime() const { return Time(hour, min, sec); }

	bool operator<(const Time&) const;
	bool operator<=(const Time&) const;
	bool operator>(const Time&) const;
	bool operator>=(const Time&) const;
	bool operator==(const Time&) const;
private:
	bool isValidTime(int h, int m, int s);
	int hour;
	int min;
	int sec;
};
#endif