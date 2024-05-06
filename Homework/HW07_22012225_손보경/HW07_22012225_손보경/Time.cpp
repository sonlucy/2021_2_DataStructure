#include "Time.h"


Time::Time(int h, int m, int s)
{
	if (isValidTime(h, m, s))
	{
		hour = h;
		min = m;
		sec = s;

	}
	else //유효한 숫자가 아니라면
	{
		cout << "Invaild Time ( " << h << ", " << m << ", " << s << ")";
		cout << "Program aborted ." << endl;
		exit(1);
	}
}

int Time::elasedSec()
{
	int elaSec = 0;

	elaSec += hour * 60 * 60;
	elaSec += min * 60;
	elaSec += sec;

	return elaSec;
}

bool Time::operator<(Time& t) 
{
	//elasedSec()함수 이용하면 더 간단.

	if (this->elasedSec() < t.elasedSec())
		return true;
	else
		return false;

	/*if (hour < t.hour)
		return true;
	else if (hour == t.hour)
	{
		if (min < t.min)
			return true;
		else if (min == t.min)
		{
			if (sec < t.sec)
				return true;
		}
		else
			return false;
	}
	else
		return false;*/
}
bool Time::operator<=( Time& t) 
{
	if (this->elasedSec() <= t.elasedSec())
		return true;
	else
		return false;
}
bool Time::operator>( Time& t) 
{
	if (this->elasedSec() > t.elasedSec())
		return true;
	else
		return false;
}
bool Time::operator>=( Time& t) 
{
	if (this->elasedSec() >= t.elasedSec())
		return true;
	else
		return false;
}
bool Time::operator==( Time& t) 
{
	/**if ((hour == t.hour) && (min == t.min) && (sec == t.sec))
		return true;
	else
		return false;*/
	if (this->elasedSec() == t.elasedSec())
		return true;
	else
		return false;
}

bool Time::isValidTime(int h, int m, int s)
{
	if ((0 <= h < 24) && (0 <= m < 60) && (0 <= s < 60))
		return true;
	else
		return false;
}

Time& Time:: operator+(int s)
{
	Time t;

	t.sec += s;
	while (t.sec > 60)
	{
		t.min += 1;
		t.sec = t.sec - 60;
		
		if (t.min > 60)
		{
			t.hour += 1;
			t.min = t.min - 60;
		}
	}
	
	return t;
	
}
