#include "Triangle.h"


Triangle::Triangle()
	:Shape()
{
	base = 0;
	tri_height = 0;

}
Triangle::Triangle(string name)
	:Shape(name)
{
	base = 0;
	tri_height = 0;
}
Triangle::Triangle(int px, int py, int b, int h, double ang, COLORREF ln_clr, COLORREF br_clr,
	int pen_thick, string name)
	: Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	base = b;
	tri_height = h;
}

Triangle::~Triangle()
{ }


double Triangle::getArea()
{
	double a;
	a = base * tri_height / 2.0; //»ï°¢Çü ³ÐÀÌ °ø½Ä( ¹Øº¯*³ôÀÌ/2 )

	return a;
}


void Triangle::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	int pos_center_x, pos_center_y;
	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x();
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y();
	POINT p[3];
	p[0].x = pos_center_x - base / 2;   
	p[0].y = pos_center_y + tri_height * 1.0 / 2.0;

	p[1].x = pos_center_x + base / 2;
	p[1].y = pos_center_y + tri_height * 1.0 / 2.0;

	p[2].x = pos_center_x;
	p[2].y = pos_center_y - tri_height * 1.0 / 2.0;

	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);


	Polygon(hdc, p, 3);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}


void Triangle::fprint(ostream& fout)
{
	fout << name << ": pos( " << get_pos_x() << ", " << get_pos_y() << ") ";
	fout << ", line_color("; fprintRGB(fout, line_color);
	fout << "), brush_color("; fprintRGB(fout, brush_color);
	fout << "), base( " << base << "), height(" << tri_height << ")";
}

Triangle& Triangle::operator=(const Triangle& tri)
{
	Shape::operator=(tri);

	base = tri.base;
	tri_height = tri.tri_height;

	return *this;
}