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
	/* 초기화 */
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
double Elps::getArea() const  //타원면적계산
{
	double a = 0.0;
	a = radius_1 * radius_2 * PI;  //타원 겉넓이 = 장반경 * 단반경 * PI

	return a;
}

void Elps:: draw()  //타원그리기
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

	Shape::operator=(elp);  ///부모클래스의 대입연산자 사용해 초기화

	return *this;
}
