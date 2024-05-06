/***
* HW06
* 상속, 다형성 및 가상함수 사용해 도형 클래스 구성
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
#define NUM_SHAPES 7

int main()
{
	ofstream fout;
	/*
		Shape s1(Position(1, 1), 0, RGB_BLUE, "Blue Shape");
	Triangle t1(Position(2, 2), 3, 4, 0, RGB_RED, "Red Triangle");
	Tri_Prism p1(Position(3, 3), 6, 7, 8, 0, RGB_GREEN, "Green Prism");
	Rectang r1(Position(4, 4), 1, 2, 0, RGB_YELLOW, "Yellow Rectangle");
	Quadr_Prism hx1(Position(5, 5), 5, 6, 7, 0, RGB_ORANGE, "Orange Hexahedtron");
	Circle cir(Position(6, 6), 6, 0, RGB_MAGENTA, "Magenta Circle");
	Cylinder cyl(Position(7, 7), 8, 6, 0, RGB_WHITE, "White Cylinder");
	*/

	Shape s1(1, 1, 0, RGB_BLUE, "Blue Shape");
	Triangle t1(2, 2, 3, 4, 0, RGB_RED, "Red Triangle");
	Tri_Prism p1(3, 3, 6, 7, 8, 0, RGB_GREEN, "Green Prism");
	Rectang r1(4, 4, 1, 2, 0, RGB_YELLOW, "Yellow Rectangle");
	Quadr_Prism hx1(5, 5, 5, 6, 7, 0, RGB_ORANGE, "Orange Hexahedtron");
	Circle cir(6, 6, 6, 0, RGB_MAGENTA, "Magenta Circle");
	Cylinder cyl(7, 7, 8, 6, 0, RGB_WHITE, "White Cylinder");
	
	Shape* shapes[NUM_SHAPES];

	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open an output file (Output.txt)₩n";
		exit(1);
	}
	shapes[0] = &s1;
	shapes[1] = &t1;
	shapes[2] = &p1;
	shapes[3] = &r1;
	shapes[4] = &hx1;
	shapes[5] = &cir;
	shapes[6] = &cyl;
	
	//fout << s1 << endl << t1 << endl << p1 << endl << r1 << endl << hx1 << endl << cir << endl << cyl << endl;
	//shapes[0]->draw(fout);
	for (int i = 0; i < NUM_SHAPES; i++)
	{
		shapes[i]->draw(fout);
		/////////fout << *shapes[i];
		//shapes[i]->fprint(fout);
		
	}
	fout.close();


	return 0;
}
