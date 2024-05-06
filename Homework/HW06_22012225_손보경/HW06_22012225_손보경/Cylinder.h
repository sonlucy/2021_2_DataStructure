#ifndef CYLINDER_H 
#define CYLINDER_H 
#include <string> 
#include "Shape.h" 
using namespace std;

class Cylinder : public Shape
{
	friend ostream& operator<<(ostream&, const Cylinder&);
public:
	Cylinder();
	Cylinder(string name);
	Cylinder(int px, int py, int r, int ht, int ang,
		COLORREF clr, /*COLORREF ln_clr, COLORREF br_clr, int pen_thick, */string name);
	//Cylinder(Cylinder &cyl); 
	~Cylinder();

	double getArea();
	double getVoume();
	virtual void draw(ConsolePixelFrame cp_frame);
	virtual void draw(ostream& fout);
	virtual void draw(); // // used for testing of late binding 
	void fprint(ostream& fout);
	int getRadius() const { return radius; }
	void setRadius(int r) { radius = r; }
	Cylinder& operator=(const Cylinder& cir);

protected:
	int radius;
	int height;
};
#endif