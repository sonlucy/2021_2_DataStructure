#include "ElpsCylinder.h"

ostream& operator<<(ostream& ostr, const ElpsCylinder& elpcyl)
{
	ostr.unsetf(ios::left);
	ostr.setf(ios::fixed);
	ostr.setf(ios::showpoint);
	ostr.precision(2);
	ostr << setw(10) << elpcyl.name << " : pos ("  << elpcyl.get_pos_x() << ", " << elpcyl.get_pos_y();
	ostr << "), angle (" << setw(5) << elpcyl.angle << " ), color_ ";
	fprintRGB(ostr, elpcyl.color);
	ostr << ", radius (" << elpcyl.radius_1 << ", " << elpcyl.radius_2 << "), height ( " << elpcyl.height << " )";
	ostr << ", area ( " << elpcyl.getArea() << "), volume ( " << elpcyl.getVolume() << ")" << endl;

	return ostr;
}

ElpsCylinder::ElpsCylinder() // default constructor
	: Elps(0, 0, 0.0, 0.0, 0.0, 0x00000000, "noname")
{ 
	height = 0.0;
}

ElpsCylinder::ElpsCylinder(string n)
	: Elps(0, 0, 0.0, 0.0, 0.0, 0x00000000, n)
{
	height = 0.0;
}


ElpsCylinder::ElpsCylinder(int px, int py, double r1, double r2, double h, double ang, COLORREF clr, string n)
	: Elps(px, py, r1, r2, ang, clr, n)
{
	height = h;  ////////
}


double ElpsCylinder::getArea() const  //Å¸¿ø±âµÕ °Ñ³ÐÀÌ
{
	double a = 0.0;
	
	a = Elps::getArea() * 2 + PI* (radius_1+radius_2 )* height;  //????
	///a = 2.0 * PI * sqrt((radius_1 * radius_1 + radius_2 * radius_2) / 2.0);

	return a;
}

double ElpsCylinder::getVolume() const  //Ã¼Àû
{
	double v = 0.0;

	v = Elps::getArea() * height;  //Å¸¿ø±âµÕºÎÇÇ= ¹Ø³ÐÀÌ *³ôÀÌ 

	return v;
}
void ElpsCylinder:: draw()
{
	cout << "draw() function of " << this->getName() << endl;
}
void ElpsCylinder::print(ostream&)
{

}

ElpsCylinder& ElpsCylinder::operator=(const ElpsCylinder& right)  //´ëÀÔ¿¬»ê
{
	Elps::operator=(right);
	height = right.height;
	
	return *this;
}