#include "Color.h"
#include <iostream>
#include <Windows.h>

ostream& fprintRGB(ostream& fout, COLORREF color)
{
	int red, green, blue;
	red = (color & 0x000000FF);
	green = (color & 0x0000FF00) >> 8;
	blue = (color & 0x00FF0000) >> 16;
	fout << "RGB(" << setw(3) <<std::hex<<uppercase<< red << ", " << setw(3) << green << ", "
		<< setw(3) << blue << ")";
	return fout;
}


