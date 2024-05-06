#ifndef ELPS_H
#define ELPS_H
#include "Shape.h"
//Ÿ����

class Elps : public Shape // Ellipse
{
	friend ostream& operator<<(ostream& fout, const Elps& elp);
public:
	Elps();
	Elps(string name);
	Elps(int px, int py, double r1, double r2, double ang, COLORREF clr, string name); 
	~Elps();

	double getArea() const;  //Ÿ���������
	void draw();  //Ÿ���׸���
	void fprint(ostream& ost);

	double getRadius_1() const { return radius_1; }
	double getRadius_2() const { return radius_2; }
	void setRadius(double r1, double r2) { radius_1 = r1; radius_2 = r2; }
	Elps& operator=(const Elps& elp);  //���Կ���

protected:
	/*����, ���� */
	double radius_1;
	double radius_2;
};
#endif