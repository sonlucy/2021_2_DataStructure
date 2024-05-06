#include "Tri_Prism.h"
#include "math.h"
#include "Triangle.h"

Tri_Prism::Tri_Prism()
	:Shape()//Triangle(0, 0, 0, 0, 0.0, SHAPE_COLOR(BLACK), "noname")
{
	base = 0;
	tri_height = 0;
	prsm_height = 0;
}
Tri_Prism::Tri_Prism(string name)
	: Shape(name)//Triangle(0, 0, 0, 0, 0.0, SHAPE_COLOR(BLACK), name)
{
	base = 0;
	tri_height = 0;
	prsm_height = 0;
}

Tri_Prism::Tri_Prism(int px, int py, int b, int tri_h, int pri_h, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string n)
	: Shape(px, py, ang, ln_clr, br_clr, pen_thick, n)
{
	base = b;
	tri_height = tri_h;
	prsm_height = pri_h;
}



Tri_Prism::~Tri_Prism()
{

}

/*double Tri_Prism::getVolume()
{
	double v;
	
}*/


void Tri_Prism::draw()
{

}
void Tri_Prism::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int center_px, center_py;
	int start_px, start_py;
	double start_ang_rad;

	center_px = cp_frame.get_pos_org_x() + get_pos_x();  ////
	center_py = cp_frame.get_pos_org_y() + get_pos_y();  ////

	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	//MoveToEx(hdc, center_px - base / 2, center_py + base / 2, NULL);
	

	//»ï°¢Çü±×¸®°í
	//height ¸¸Å­ ¼± µÎ°³ ±ß°í »ï°¢Çü ¹Øº¯ ±æÀÌ¸¸Å­ ¹Ø¿¡ ÁÙ ±ß±â
	MoveToEx(hdc, center_px- base/2, center_py+base/2, NULL);
	LineTo(hdc, center_px, center_py+base/4 );
	LineTo(hdc, center_px + base / 2, center_py + base / 2);
	LineTo(hdc, center_px - base / 2, center_py + base / 2);
	LineTo(hdc, center_px - base / 2, center_py + base / 2 + prsm_height);
	LineTo(hdc, center_px+base/2, center_py + base / 2 + prsm_height);
	LineTo(hdc, center_px + base / 2, center_py + base / 2);
	//Triangle(hdc, p, 4);

	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);

	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void Tri_Prism::fprint(ostream& fout)
{
	/*fout << name << ": pos( " << get_pos_x() << ", " << get_pos_y() << ") ";
	fout << ", line_color("; fprintRGB(fout, line_color);
	fout << "), brush_color("; fprintRGB(fout, brush_color);*/
	fout << "), base(" << base << "), tri_height(" << tri_height;
	fout << "), prsm_height(" << prsm_height << ") ";

}

Tri_Prism& Tri_Prism::operator=(const Tri_Prism& right)
{
	Shape::operator=(right);
	base = right.base;
	tri_height = right.tri_height;
	prsm_height = right.prsm_height;

	return *this;
}