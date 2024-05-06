#include "Circle.h"


Circle::Circle()
	:Shape()
{
	radius = 0;
}

Circle::Circle(string name)
	: Shape(name)
{
	radius = 0;
}
Circle::Circle(int px, int py, int r, double ang,
	COLORREF clr, /*COLORREF ln_clr, COLORREF br_clr, int pen_thick,*/ string name)
	: Shape(px, py, ang, clr, /*ln_clr, br_clr, pen_thick,*/ name)
{
	radius = r;
}


Circle::~Circle()
{

}

double Circle::getArea()
{
	double area;
	area = PI * radius * radius;

	return area;
}



void Circle::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int pos_center_x, pos_center_y;

	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x();
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y();

	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, 3, color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	//new_brush = CreateSolidBrush(brush_color);
	//old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Ellipse(hdc, pos_center_x - radius, pos_center_y - radius, pos_center_x + radius, pos_center_y + radius);  //타원그리기


	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);

	//SelectObject(hdc, old_brush);
	//DeleteObject(new_brush);
}

void Circle::fprint(ostream& fout)
{
	fout << name << ": pos(" << get_pos_x() << ", " << get_pos_y() << " ) ";
	//fout << " , line_color ("; fprintRGB(fout, line_color);
	//fout << " ), brush_color ("; fprintRGB(fout, brush_color);
	fout << "), color("; fprintRGB(fout, color);
	fout << " ), radius (" << radius << " ) ";

}

ostream& operator<<(ostream& fout, Circle& c)
{
	fout << c.name << ": pos( " << c.get_pos_x() << ", " << c.get_pos_y() << ") ";
	//fout << ", line_color("; fprintRGB(fout, c.line_color);
	//fout << "), brush_color("; fprintRGB(fout, c.brush_color);
	fout << "), color("; fprintRGB(fout, c.color);
	fout << "), radius( " << c.radius << ") ";

	return fout;
}

void Circle::draw(ostream& fout)
{
	fout << name << ": pos( " << get_pos_x() << ", " << get_pos_y() << ") ";
	//fout << ", line_color("; fprintRGB(fout, c.line_color);
	//fout << "), brush_color("; fprintRGB(fout, c.brush_color);
	fout << "), color("; fprintRGB(fout, color);
	fout << "), radius( " << radius << "), Circle_area(" << getArea() << ")\n";

}
