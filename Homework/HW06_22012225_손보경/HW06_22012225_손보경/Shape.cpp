#include "Shape.h"
#include <iostream>
#include <iomanip>

using namespace std;

Shape::Shape() // default constructor
{
	pos_x = pos_y = 0;
	angle = 0;
	//line_color = brush_color = RGB_BLACK;
	color = RGB_BLACK;
	name = "no_name";
	//cout << "Shape::Default constructor (" << name << ").₩n";
}

Shape::Shape(string n)
	:name(n)
{
	pos_x = pos_y = 0;
	angle = 0;
	//line_color = brush_color = RGB_BLACK;
	color = RGB_BLACK;
	//cout << "Shape::Constructor (" << name << ").₩n";
}
Shape::~Shape()
{
	//cout << "Shape::Destructor (" << name << ").₩n";
}

Shape::Shape(int px, int py, double ang, /*COLORREF ln_clr, COLORREF br_clr,
	int pen_thick,*/ COLORREF clr, string nm)
{
	pos_x = px;
	pos_y = py;
	angle = ang;
	//line_color = ln_clr;
	//brush_color = br_clr;
	//pen_thickness = pen_thick;
	color = clr;
	name = nm;
	//cout << "Shape::Constructor (" << name << ").₩n";
}
void Shape::fprint(ostream& fout)
{
	fout << name << ": pos(" << get_pos_x() << ", " << get_pos_y() << ")";
	fout << ", color(";
	fprintRGB(fout, color); 
	//fout << ", line_color(";
	//fprintRGB(fout, line_color);
	//fout << "), brush_color(";
	//fprintRGB(fout, brush_color);
}


void Shape::draw(ConsolePixelFrame cp_frame)
{
	/* virtual function that will be late-binded to sub-class's draw() */
}


Shape& Shape::operator=(const Shape& s)
{
	pos_x = s.pos_x;
	pos_y = s.pos_y;
	angle = s.angle;
	name = s.name;
	//line_color = s.line_color;
	//brush_color = s.brush_color;
	color = s.color;

	return *this;
}

ostream& operator<<(ostream& ostr, Shape& shp)
{
	ostr << shp.name << ": pos(" << shp.get_pos_x() << ", " << shp.get_pos_y() << ")";
	//ostr << ", line_color(";
	//fprintRGB(ostr, shp.line_color);  ///////
	ostr << ", color(";
	fprintRGB(ostr, shp.color);
	//ostr << "), brush_color(";
	//fprintRGB(ostr, shp.brush_color);  /////////
	//ostr << ")";
	return ostr;
}

void Shape::draw(ostream& fout)
{
	fout << name << ": pos(" << get_pos_x() << ", " << get_pos_y() << ")";
	//ostr << ", line_color(";
	//fprintRGB(ostr, shp.line_color);  ///////
	fout << ", color(";
	fprintRGB(fout, color);
	fout << ")\n";
	//ostr << "), brush_color(";
	//fprintRGB(ostr, shp.brush_color);  /////////
	//ostr << ")";
}
