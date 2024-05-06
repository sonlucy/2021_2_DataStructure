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

	Time& operator+(int s);  //������ �ʸ�ŭ �����ִ� �Լ�
	
	int elasedSec() ;  //������ ��
	Time getTime() { return Time(hour, min, sec); }
	
	bool operator<(Time& t);
	bool operator<=(Time& t);
	bool operator>(Time& t);
	bool operator>=(Time& t);
	bool operator==(Time& t);
private:
	bool isValidTime(int, int, int);
	int hour;
	int min;
	int sec;
};
#endif