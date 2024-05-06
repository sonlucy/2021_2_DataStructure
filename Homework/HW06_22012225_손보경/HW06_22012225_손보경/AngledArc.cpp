#include "AngledArc.h"
#include <iostream>
#include <math.h>
#include "AngledArc.h"
#include "ConsolePixelDrawing.h"
#include <iomanip>
using namespace std;

AngledArc::AngledArc() // default constructor
	:Shape("no_name"), radius(0), start_angle(0), sweep_angle(0)
{
	//cout << "AngleArc::Default AngleArc constructor (" << name << ").₩n";
}
AngledArc::AngledArc(string name)
	: Shape(name), radius(0), start_angle(0), sweep_angle(0)
{
	//cout << "AngleArc::Constructor (" << name << ").₩n";
}
AngledArc::AngledArc(int px, int py, int r, int ang, int start_ang, int sweep_ang,
	COLORREF clr, /*COLORREF ln_clr, COLORREF br_clr, int pen_thick,*/ string name)
	: Shape(px, py, ang, clr, /*ln_clr, br_clr, pen_thick,*/ name)
{
	//cout << "AngleArc::Constructor (" << name << ").₩n";
	radius = r;
	start_angle = start_ang;
	sweep_angle = sweep_ang;
}
AngledArc::~AngledArc()
{
	//cout << "AngleArc::Destructor (" << name << ").₩n";
}
void AngledArc::draw()
{
	cout << "draw() of AngleArc";
	fprint(cout);
}

void AngledArc::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int fr_px, fr_py;
	int start_px, start_py;
	double start_ang_rad;

	fr_px = cp_frame.get_pos_org_x() + get_pos_x();   ///
	fr_py = cp_frame.get_pos_org_y() + get_pos_y();   ///

	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, 3, color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	//new_brush = CreateSolidBrush(brush_color);
	//old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	start_ang_rad = start_angle * 3.141592 / 180.0;
	start_px = fr_px + radius * cos(start_ang_rad);
	start_py = fr_py - radius * sin(start_ang_rad);
	MoveToEx(hdc, fr_px, fr_py, (LPPOINT)NULL);
	LineTo(hdc, start_px, start_py);
	AngleArc(hdc, fr_px, fr_py, radius, start_angle, sweep_angle); ///
	LineTo(hdc, fr_px, fr_py);

	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);

	//SelectObject(hdc, old_brush);
	//DeleteObject(new_brush);
}

ostream& operator<<(ostream& fout, const AngledArc& ang_arc)
{
	fout << ang_arc.name << ": pos(" << ang_arc.get_pos_x() << ", " << ang_arc.get_pos_y() << ")"; ////
	//fout << ", line_color("; fprintRGB(fout, ang_arc.line_color);
	//fout << "), brush_color("; fprintRGB(fout, ang_arc.brush_color);
	fout << ", color("; fprintRGB(fout, ang_arc.color);
	fout << ")";
	fout << ", radius(" << ang_arc.radius << ")";
	fout << ", start_ang (" << ang_arc.start_angle << "), sweep_ang(" << ang_arc.sweep_angle << ")";
	fout << endl;

	return fout;
}
AngledArc& AngledArc::operator=(const AngledArc& right)
{
	Shape::operator=(right);
	radius = right.radius;
	return *this;
}
void AngledArc::fprint(ostream& fout)
{
	Shape::fprint(fout);
	fout << ", radius (" << radius << "), start_angle (" << start_angle;
	fout << "), sweep_angle (" << sweep_angle << ")";
	fout << endl;
}


void AngledArc::draw(ostream fout)
{
	fout << name << ": pos(" << get_pos_x() << ", " << get_pos_y() << ")"; ////
	//fout << ", line_color("; fprintRGB(fout, ang_arc.line_color);
	//fout << "), brush_color("; fprintRGB(fout, ang_arc.brush_color);
	fout << ", color("; fprintRGB(fout, color);
	fout << ")";
	fout << ", radius(" << radius << ")";
	fout << ", start_ang (" << start_angle << "), sweep_ang(" << sweep_angle << ")";
	fout << endl;
}
