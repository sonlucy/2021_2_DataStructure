/* main.cpp */

/***
* Lab06
* 다형성과 가상함수 이용한 도형 그리기
*
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자: 2021-10-08
***/

#include <iostream> 
#include <string> 
#include <fstream> 
#include "ConsolePixelDrawing.h" 
#include "Shape.h" 
#include "Triangle.h" 
#include "Circle.h" 
#include "Rectang.h" 
#include "Polygon.h" 
#include "Star.h" 
#include "AngledArc.h" 
#include "Cylinder.h" 
#include "Tri_Prism.h"
#include "Quadr_Prism.h"
using namespace std;

int main()
{
	Circle cir(50, 200, 50, 0, RGB_BLACK, RGB_RED, 3, "Circle");
	Triangle tri(150, 200, 100, 80, 0, RGB_BLACK, RGB_YELLOW, 3, "Triangle");
	Rectang rec(270, 200, 100, 100, 0, RGB_BLACK, RGB_BLUE, 4, "Rectangle");
	PolyGon poly_5(380, 200, 40, 5, 0, RGB_BLACK, RGB_GREEN, 4, "Polygon_5");

	PolyGon poly_7(50, 400, 50, 7, 0, RGB_BLACK, RGB_MAGENTA, 4, "Polygon_7");
	Star star_5(150, 400, 50, 5, 0, RGB_BLACK, RGB_GREEN, 4, "Star_5");
	AngledArc angle_arc(270, 400, 50, 0, 45, 270, RGB_RED, RGB_YELLOW, 4, "Angle_Arc");
	Cylinder cyl(380, 400, 50, 0, 100, RGB_BLUE, RGB_WHITE, 4, "Cylinder");  //원기둥

	Tri_Prism t_pri(500, 120, 100, 80, 80, 0, RGB_MAGENTA, RGB_WHITE, 4, "t_Prism");  //삼각기둥
	Quadr_Prism q_pri(500, 400, 100, 80, 80, 80, 45, RGB_BLACK, RGB_WHITE, 4, "q_Prism");  //사각기둥

	ConsolePixelFrame frame(50, 50); // fr_x, fr_y 

	frame.addShape(&cir);
	frame.addShape(&tri);
	frame.addShape(&rec);
	frame.addShape(&poly_5);
	frame.addShape(&poly_7);
	frame.addShape(&star_5);
	frame.addShape(&angle_arc);
	frame.addShape(&cyl);
	frame.addShape(&t_pri);
	frame.addShape(&q_pri);


	frame.drawShapes();  //해당하는 클래스의 도형을 그려주는 함수

	printf("hit any key to continue ....");
	_getch();
	return 0;
}
