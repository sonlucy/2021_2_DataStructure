#ifndef Tri_Prism_H
#define Tri_Prism_H
#include <string>
#include "ConsolePixelDrawing.h"
//#include "Triangle.h"
#include "Shape.h"
using namespace std;

class Tri_Prism : public Shape
{
	friend ostream* operator<<(ostream& ostr, Tri_Prism& pr);
public:
	Tri_Prism();
	Tri_Prism(string name);
	Tri_Prism(int px, int py, int b, int tri_h, int pri_h, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string n);
	Tri_Prism(Tri_Prism& pr);
	~Tri_Prism();
	
	double getVolume();
	virtual void draw(ConsolePixelFrame cp_frame);  //////////
	void draw();
	void fprint(ostream& fout);
	Tri_Prism& operator=(const Tri_Prism& right);
protected:
	int base;
	int tri_height;
	int prsm_height;

};

#endif