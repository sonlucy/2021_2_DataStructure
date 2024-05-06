#include "Quadr_Prism.h"
#include <math.h>
#include "Rectang.h"


Quadr_Prism::Quadr_Prism()
	:Shape()//Triangle(0, 0, 0, 0, 0.0, SHAPE_COLOR(BLACK), "noname")
{
	width = 0;
	length = 0;
	prsm_height = 0;
}
Quadr_Prism::Quadr_Prism(string name)
	: Shape(name)//Triangle(0, 0, 0, 0, 0.0, SHAPE_COLOR(BLACK), name)
{
	width = 0;
	length = 0;
	prsm_height = 0;
}

Quadr_Prism::Quadr_Prism(int px, int py, int w, int l, int r, int pri_h, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string n)
	: Shape(px, py, ang, ln_clr, br_clr, pen_thick, n)
{
	width = w;
	length = l;
	prsm_height = pri_h;
	radius = r;
	
}



Quadr_Prism::~Quadr_Prism()
{

}

/*double Quadr_Prism::getVolume()
{
	double v;

}*/


void Quadr_Prism::draw()
{
	//
}
void Quadr_Prism::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int center_px, center_py;
	int start_px, start_py;
	double start_ang_rad;

	center_px = cp_frame.get_pos_org_x() + get_pos_x();  ////
	center_py = cp_frame.get_pos_org_y() + get_pos_y();  ////

	/* 사각형 꼭짓점 설정 */
	POINT p[4];	
	p[0].x = center_px - width / 2;		//왼쪽 위
	p[0].y = center_py - length / 2;

	p[1].x = center_px + width / 2;		//오른쪽 위
	p[1].y = center_py - length / 2;

	p[2].x = center_px + width / 2;		//오른쪽 밑
	p[2].y = center_py + length / 2;

	p[3].x = center_px - width / 2;		//왼쪽 밑
	p[3].y = center_py + length / 2;

	hdc = cp_frame.getConsole_DC();  
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);  
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);


	
	
	Polygon(hdc, p, 4);  //사각형 그리기

	start_ang_rad = angle * PI / 180.0;  //라디안으로
	start_px = center_px + radius * cos(start_ang_rad);
	start_py = center_py - radius * sin(start_ang_rad);

	MoveToEx(hdc, center_px - width / 2, center_py - length / 2, NULL);
	LineTo(hdc, start_px - width / 2, start_py - length / 2);
	LineTo(hdc, start_px + width / 2, start_py - length / 2); 
	LineTo(hdc, center_px + width / 2, center_py - length / 2);
	
	MoveToEx(hdc, start_px + width / 2, start_py - length / 2, NULL);
	LineTo(hdc, start_px + width / 2, start_py + length / 2);
	LineTo(hdc, center_px + width / 2, center_py + length / 2);



	/*hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	//old_brush = (HBRUSH)SelectObject(cp_frame.getConsole_DC(), new_brush);
	
	int fr_px, fr_py;

	start_ang_rad = angle * 3.141592 / 180.0;
	start_px = fr_px + radius * cos(start_ang_rad);
	start_py = fr_py - radius * sin(start_ang_rad);
	MoveToEx(hdc, fr_px, fr_py, (LPPOINT)NULL);
	LineTo(hdc, start_px, start_py); 
	//AngleArc(hdc, fr_px, fr_py, radius, angle, sweep_angle); ///
	//Rectang(hdc, fr_px, fr_py, angle, ); //ang, ln_clr, br_clr, pen_thick, name
	LineTo(hdc, fr_px, fr_py);*/


	/*MoveToEx(hdc, (center_px - width / 2), (center_py + length / 2), NULL);  //기준점
	LineTo(hdc, (center_px - width / 2) + length * cos(angle), (center_py + length ) - length * sin(angle));
	LineTo(hdc, (center_px - width / 2)+length*cos(angle)+width, (center_py + length )-length*sin(angle));
	LineTo(hdc, (center_px - width / 2)+width, (center_py + length / 2));
	LineTo(hdc, (center_px - width / 2), (center_py + length / 2));
	
	LineTo(hdc, (center_px - width / 2), (center_py + length / 2)+prsm_height);
	LineTo(hdc, (center_px - width / 2)+width, (center_py + length / 2)+prsm_height);
	LineTo(hdc, (center_px - width / 2)+width, (center_py + length / 2));
	MoveToEx(hdc, (center_px - width / 2) + length * cos(angle) + width, (center_py + length ) - length * sin(angle), NULL);
	LineTo(hdc, (center_px - width / 2) + length * cos(angle) + width, (center_py + length ) + prsm_height-length*sin(angle));
	LineTo(hdc, (center_px - width / 2) + width, (center_py + length /2) + prsm_height);
	*/


	/*
	//사각형그리고( 그릴때 주의
	//height 만큼 선 두개 긋고 사각형 밑변 길이만큼 밑에 줄 긋기
	MoveToEx(hdc, center_px - width / 2, center_py + length / 2, NULL);
	LineTo(hdc, center_px - width / 4, center_py+length/4 );
	LineTo(hdc, center_px + width / 2, center_py+length/4);
	LineTo(hdc, center_px + width / 4, center_py + length / 2);
	LineTo(hdc, center_px - width / 2, center_py + length / 2);
	LineTo(hdc, center_px - width / 2, center_py + length / 2 + prsm_height);
	LineTo(hdc, center_px + width / 4, center_py + length / 2 + prsm_height);
	LineTo(hdc, center_px + width / 4, center_py + length / 2);
	MoveToEx(hdc, center_px + width / 2, center_py + length / 4, NULL);
	LineTo(hdc, center_px + width / 2, center_py + prsm_height+length/4);
	LineTo(hdc, center_px + width / 4, center_py + length / 2 + prsm_height);*/
	
	/*
	// 사각형 그리기 
	MoveToEx(hdc, center_px - width / 2, center_py + length / 2, NULL);
	LineTo(hdc, center_px + width / 2, center_py + length / 2);
	LineTo(hdc, center_px + width / 4, center_py);
	LineTo(hdc, center_px - width / 4, center_py);
	LineTo(hdc, center_px - width / 2, center_py + length / 2);

	// 기둥 그리기
	LineTo(hdc, center_px - width / 2, center_py + length / 2 + prsm_height);
	LineTo(hdc, center_px + width / 2, center_py + length / 2 + prsm_height);
	LineTo(hdc, center_px + width / 2, center_py + length / 2);*/


	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);

	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void Quadr_Prism::fprint(ostream& fout)
{
	/*fout << name << ": pos( " << get_pos_x() << ", " << get_pos_y() << ") ";
	fout << ", line_color("; fprintRGB(fout, line_color);
	fout << "), brush_color("; fprintRGB(fout, brush_color);*/
	fout << "), width(" << width << "), length(" << length;
	fout << "), prsm_height(" << prsm_height << ") ";
	

}

Quadr_Prism& Quadr_Prism::operator=(const Quadr_Prism& right)
{
	Shape::operator=(right);
	width = right.width;
	length = right.length;
	prsm_height = right.prsm_height;

	return *this;
}