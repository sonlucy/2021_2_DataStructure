#include "Shape.h"
#include <iostream>
#include <iomanip>
using namespace std;

ostream& operator<<(ostream& ostr, Shape& sh)  ////////////////
{
	ostr.unsetf(ios::left);
	ostr.setf(ios::fixed);
	ostr.setf(ios::showpoint);
	ostr.precision(2);
	ostr << setw(10) << sh.name << " : ";  /////////////////
	ostr << "pos (" <<  sh.get_pos_x() << ", "<< sh.get_pos_y() << ")";
	ostr << ", angle (" << setw(5) << sh.angle << ")";
	ostr << " , color_";
	fprintRGB(ostr, sh.color);
	ostr << endl;
	return ostr;
}

Shape::Shape() // default constructor
{
	pos_x = pos_y = 0;
	angle = 0;
	color= RGB_BLACK;
	name = "no_name";
	//cout << "Shape::Default constructor (" << name << ").\n";
}
Shape::Shape(string n)
	:name(n)
{
	pos_x = pos_y = 0;
	angle = 0;
	color= RGB_BLACK;
	//cout << "Shape::Constructor (" << name << ").\n";
}

Shape::Shape(int px, int py, double ang, COLORREF colr, string n)
{
	pos_x = px;
	pos_y = py;
	angle = ang;
	color = colr;
	name = n;
}
Shape::~Shape()
{
	//cout << "Shape::Destructor (" << name << ").\n";
}
void Shape::draw()
{
	cout << "draw() of " << name << endl;
}

void Shape::fprint(ostream& fout)
{
	fout << name << ": pos(" << get_pos_x() << ", " << get_pos_y() << ")";
	fout << ", color(";
	fprintRGB(fout, color);
	fout << ")";
}


Shape& Shape::operator=(const Shape& right)
{
	pos_x = right.pos_x;   // position (x, y)
	pos_y = right.pos_y;
	angle = right.angle;
	name = right.name;
	color = right.color;
	return *this;
}

