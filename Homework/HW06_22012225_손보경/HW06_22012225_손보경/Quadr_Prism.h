#ifndef Quadr_Prism_H
#define Quadr_Prism_H
#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
using namespace std;

class Quadr_Prism :public Shape
{
	friend ostream& operator<<(ostream& fout, Quadr_Prism& pr);
public:
	Quadr_Prism();
	Quadr_Prism(string name);
	Quadr_Prism(int px, int py, int w, int l, int h, double ang,COLORREF clr, 
		/*COLORREF ln_clr, COLORREF br_clr, int pen_thick,*/ string n);
	Quadr_Prism(Quadr_Prism& pr);
	~Quadr_Prism();

	double getVolume();
	double getArea();
	virtual void draw(ConsolePixelFrame cp_frame);  //////////
	virtual void draw(ostream& fout);
	void draw();
	void fprint(ostream& fout);
	Quadr_Prism& operator=(const Quadr_Prism& right);

protected:
	int width;
	int length;
	//int prsm_height;
	int height;

};
#endif


