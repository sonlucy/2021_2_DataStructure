#ifndef Rectang_H 
#define Rectang_H
#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
using namespace std;
class Rectang : public Shape
{
	friend ostream& operator<<(ostream & fout, Rectang& rec);
public:
	Rectang();
	Rectang(string name);
	Rectang(int px, int py, int w, int l, double ang, COLORREF clr,
		/*COLORREF ln_clr, COLORREF br_clr, int pen_thick,*/ string name);
	~Rectang();

	double getArea();
	virtual void draw(ConsolePixelFrame cp_frame);
	virtual void draw(ostream& fout);
	void fprint(ostream& fout);
	int getWidth() { return width; }
	int getLength() { return length; }
	Rectang& operator=(Rectang& rec);

protected:
	int width;
	int length;
};
#endif
