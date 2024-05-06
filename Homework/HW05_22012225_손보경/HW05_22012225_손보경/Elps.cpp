#include "Elps.h"

ostream& operator<<(ostream& fout, const Elps& elp)
{
	fout.unsetf(ios::left);
	fout.setf(ios::fixed);
	fout.setf(ios::showpoint);
	fout.precision(2);
	fout << setw(10) << elp.name << " : ";
	fout<< "pos ("  << elp.get_pos_x() << ", "<< elp.get_pos_y() << ")";
	fout<< ", angle (" << setw(5) << elp.angle << ")";
	fout << " , color_";
	fprintRGB(fout, elp.color);
	fout << " , radius ( " << elp.getRadius_1() << ", " << elp.getRadius_2() << " ), ";
	fout << " ellipse_area (" << elp.getArea() << " )";
	fout <<  endl;
	return fout;
	
}


Elps::Elps()  //defalt constructor
{
	/* �ʱ�ȭ */
	radius_1=0;
	radius_2=0;
}

Elps::Elps(string name)
	:Shape(name)  //
{
	radius_1 = 0;
	radius_2 = 0;
}
 
Elps::Elps(int px, int py, double r1, double r2, double ang, COLORREF clr, string name)
	:Shape(px, py, ang, clr, name) // constructor
{
	radius_1 = r1;
	radius_2 = r2;
}

Elps::~Elps()
{
	//cout<<"Elps::~Elps()"<<endl;
}

#define pi 3.14
double Elps::getArea() const  //Ÿ���������
{
	double a = 0.0;
	a = radius_1 * radius_2 * PI;  //Ÿ�� �ѳ��� = ��ݰ� * �ܹݰ� * PI

	return a;
}

void Elps:: draw()  //Ÿ���׸���
{
	cout << "draw() function of " << this->getName() << endl;
}

void Elps::fprint(ostream& ost)  //////////
{
	ost.unsetf(ios::left);
	Shape::fprint(ost);  //
	ost << ", radius (" << radius_1 << " , " << radius_2 << " ) ";
	ost << " area ( " << getArea() << " ) ";
}

Elps& Elps::operator=(const Elps& elp)
{
	radius_1 = elp.radius_1;
	radius_2 = elp.radius_2;

	Shape::operator=(elp);  ///�θ�Ŭ������ ���Կ����� ����� �ʱ�ȭ

	return *this;
}
