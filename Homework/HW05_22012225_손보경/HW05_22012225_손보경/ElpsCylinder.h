#ifndef ELPSCYLINDER_H
#define ELPSCYLINDER_H
#include "Elps.h"

//원기둥
class ElpsCylinder : public Elps
{
	friend ostream& operator<<(ostream& ostr, const ElpsCylinder& elpcyl);
public:
	ElpsCylinder(); // default constructor
	ElpsCylinder(string n);
	ElpsCylinder(int px, int py, double r1, double r2, double h, double ang, COLORREF clr, string n);
	virtual ~ElpsCylinder() {};

	double getArea() const;  //타원의 표면적
	double getVolume() const;  //체적
	void draw();
	void print(ostream&);
	ElpsCylinder& operator=(const ElpsCylinder& right);  //대입연산
protected:
	double height; // Cylinder height
};
#endif