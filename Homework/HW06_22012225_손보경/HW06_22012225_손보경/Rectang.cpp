#include "Rectang.h"

Rectang::Rectang()
	:Shape()
{
	width = 0;
	length = 0;
}

Rectang::Rectang(string name)
	:Shape(name)
{
	width = 0;
	length = 0;
}

Rectang::Rectang(int px, int py, int w, int l, double ang,COLORREF clr, 
	/* COLORREF ln_clr, COLORREF br_clr, int pen_thick,*/ string name)
	:Shape(px, py, ang, clr /*ln_clr, br_clr, pen_thick*/, name)
{
	width = w;
	length = l;
}


Rectang::~Rectang()
{ }

double Rectang::getArea()
{
	double a;
	a = width * length;

	return a;
}

void Rectang::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	int pos_center_x, pos_center_y;

	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x();
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y();

	POINT p[4];
	p[0].x = pos_center_x - width / 2;  //왼쪽 위
	p[0].y = pos_center_y - length / 2;

	p[1].x = pos_center_x + width / 2;   //오른쪽 위
	p[1].y = pos_center_y - length / 2.0;

	p[2].x = pos_center_x + width / 2;  //오른쪽 밑
	p[2].y = pos_center_y + length / 2.0;

	p[3].x = pos_center_x - width / 2;  //왼쪽 밑
	p[3].y = pos_center_y + length / 2.0;

	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, 3, color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	//new_brush = CreateSolidBrush(brush_color);
	//old_brush = (HBRUSH)SelectObject(cp_frame.getConsole_DC(), new_brush);

	Polygon(hdc, p, 4);  //

	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	//SelectObject(hdc, old_brush);
	//DeleteObject(new_brush);
}


void Rectang::fprint(ostream& fout)
{
	fout << name << ": pos( " << get_pos_x() << ", " << get_pos_y() << ") ";
	//fout << ", line_color("; fprintRGB(fout, line_color);
	//fout << "), brush_color("; fprintRGB(fout, brush_color);
	fout << ", color("; fprintRGB(fout, color);
	fout << "), width(" << width << "), length(" << length << ")";
}

Rectang& Rectang::operator=(Rectang& rec)
{
	Shape::operator=(rec); // 부모클래스 대입연산자

	width = rec.width;
	length = rec.length;

	return *this;
}

ostream& operator<<(ostream& fout, Rectang& rec)
{
	fout << rec.name << ": pos( " << rec.get_pos_x() << ", " << rec.get_pos_y() << ") ";
	//fout << ", line_color("; fprintRGB(fout, line_color);
	//fout << "), brush_color("; fprintRGB(fout, brush_color);
	fout << ", color("; fprintRGB(fout, rec.color);
	fout << "), width(" << rec.width << "), length(" << rec.length << ")";

	return fout;


}

void Rectang::draw(ostream& fout)
{
	fout << name << ": pos( " << get_pos_x() << ", " << get_pos_y() << ") ";
	//fout << ", line_color("; fprintRGB(fout, line_color);
	//fout << "), brush_color("; fprintRGB(fout, brush_color);
	fout << ", color("; fprintRGB(fout, color);
	fout << "), width(" << width << "), length(" << length;
	fout << "), Rect_area(" << getArea() << ")\n";
}
