#ifndef Quadr_Prism_H
#define Quadr_Prism_H
#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
using namespace std;

class Quadr_Prism :public Shape
{
	friend ostream* operator<<(ostream& ostr, Quadr_Prism& pr);
public:
	Quadr_Prism();
	Quadr_Prism(string name);
	Quadr_Prism(int px, int py, int w, int l, int pri_h,int r, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string n);
	Quadr_Prism(Quadr_Prism& pr);
	~Quadr_Prism();

	double getVolume();
	virtual void draw(ConsolePixelFrame cp_frame);  //////////
	void draw();
	void fprint(ostream& fout);
	Quadr_Prism& operator=(const Quadr_Prism& right);
protected:
	int width;
	int length;
	int prsm_height;
	int radius;

};
#endif


