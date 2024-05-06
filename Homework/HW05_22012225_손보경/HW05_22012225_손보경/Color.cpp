#include "Color.h"

#include <iostream>
#include <Windows.h>
#include "Color.h"
ostream& fprintRGB(ostream& fout, const COLORREF color)
{
	unsigned int red, green, blue;
	red = (color & 0x000000FF);
	green = (color & 0x0000FF00) >> 8;
	blue = (color & 0x00FF0000) >> 16;
	fout << "RGB(" << setw(2) << hex << uppercase << internal << setfill('0') << red;
	fout << "," << setw(2) << hex << uppercase << internal << setfill('0') << green;
	fout << "," << setw(2) << hex << uppercase << internal << setfill('0') << blue;
	fout << ")";
	return fout;
}
