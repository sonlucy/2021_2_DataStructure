#ifndef ELPSCYLINDER_H
#define ELPSCYLINDER_H
#include "Elps.h"

//�����
class ElpsCylinder : public Elps
{
	friend ostream& operator<<(ostream& ostr, const ElpsCylinder& elpcyl);
public:
	ElpsCylinder(); // default constructor
	ElpsCylinder(string n);
	ElpsCylinder(int px, int py, double r1, double r2, double h, double ang, COLORREF clr, string n);
	virtual ~ElpsCylinder() {};

	double getArea() const;  //Ÿ���� ǥ����
	double getVolume() const;  //ü��
	void draw();
	void print(ostream&);
	ElpsCylinder& operator=(const ElpsCylinder& right);  //���Կ���
protected:
	double height; // Cylinder height
};
#endif