#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <Windows.h>
#include <conio.h>
//#include "ConsolePixelDrawing.h"
#include "Color.h"
using namespace std;
#define PI 3.14159
class ConsolePixelFrame;

class Shape
{
	friend ostream& operator<<(ostream& ostr, Shape& sh);
public:
	Shape(); // default constructor
	Shape(string name);
	Shape(int px, int py, double angle, COLORREF col, string n); // constructor
	~Shape();
	
	void draw();
	void rotate(double rt_ang) { angle += rt_ang; }
	void move(int dx, int dy) { pos_x += dx; pos_y += dy; }
	
	void fprint(ostream& fout);

	int get_pos_x() const { return pos_x; }
	int get_pos_y() const { return pos_y; }
	void set_pos_x(int x) { pos_x = x; }
	void set_pos_y(int y) { pos_y = y; }
	void setName(string n) { name = n; }
	string getName() { return name; }
	Shape& operator=(const Shape& s);

protected:
	int pos_x; // position x
	int pos_y; // position y
	double angle; // in radian
	string name;
	COLORREF color; // COLORREF is defined in <Windows.h>
};
#endif