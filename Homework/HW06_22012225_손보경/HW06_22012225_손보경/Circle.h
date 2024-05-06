#ifndef Circle_H 
#define Circle_H
#include <string>
#include "Shape.h"
using namespace std;
#define PI 3.14159 
class Circle : public Shape
{
	friend ostream& operator<<(ostream& fout, Circle& c);
public:
	Circle();
	Circle(string name);
	Circle(int px, int py, int r, double ang,
		COLORREF clr,  /*COLORREF ln_clr, COLORREF br_clr, int pen_thick,*/ string name);
	//Circle(Circle &tr);
	~Circle();

	double getArea();
	//virtual void draw(ostream& fout);
	virtual void draw(ConsolePixelFrame cp_frame);
	virtual void draw(ostream& fout);
	void fprint(ostream& fout);
	int getRadius() const { return radius; }
	void setRadius(int r) { radius = r; }
	Circle& operator=(const Circle& cir);

protected:
	int radius;
};
#endif
