#ifndef PIXEL_DRAWING_H
#define PIXEL_DRAWING_H 
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "Shape.h"
#include "Color.h"
using namespace std;
/* 선 종류 지정 */
#define PS_SOLID 0 
#define PS_DASH 1 // -------
#define PS_DOT 2 // .......
#define PS_DASHDOT 3 // _._._._
#define PS_DASHDOTDOT 4 // _.._.._
#define PS_NULL 5 
#define PS_INSIDEFRAME 6 
#define PS_USERSTYLE 7 
#define PS_ALTERNATE 8 
#define MAX_NUM_SHAPES 100 
class Shape;
class ConsolePixelFrame
{
public:
	ConsolePixelFrame(int org_x, int org_y);
	~ConsolePixelFrame();

	void addShape(Shape* new_shape); //추가할 도형의 주소를 pShapes 포인터가 가리키도록하고 포인터배열로 생성
	void drawShapes();  //pShapes 포인터 배열에 있는 도형들을 그리는 함수
	int get_pos_org_x() { return pos_org_x; }
	int get_pos_org_y() { return pos_org_y; }
	HDC getConsole_DC() { return console_DC; }

private:
	HWND console;  //
	HDC console_DC; // device context 
	Shape** pShapes; // Array of Shape Pointers 
	int num_shapes;  
	int capacity;
	int pos_org_x;
	int pos_org_y;
	bool isValidIndex(int sub);
};
#endif
