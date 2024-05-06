#include "ConsolePixelDrawing.h"

ConsolePixelFrame::ConsolePixelFrame(int px, int py)
{
	console = GetConsoleWindow();
	console_DC = GetDC(console);
	pShapes = new Shape * [MAX_NUM_SHAPES];
	num_shapes = 0;
	capacity = MAX_NUM_SHAPES;

	/* 기준 점 */
	pos_org_x = px;
	pos_org_y = py;
}

ConsolePixelFrame::~ConsolePixelFrame()
{
	//delete[] shapes;
	//ReleaseDC(console, console_DC);
}

void ConsolePixelFrame::addShape(Shape* pNew_shape)
{
	if (num_shapes >= capacity)  //배열 확장 필요
	{
		cout << "ConsolePixelFrame::addShape ==> Expanding capacity to "
			<< capacity * 2 << "shapes " << endl;
		Shape** old_shapes = pShapes;
		pShapes = new Shape * [capacity * 2];  //2배만큼 늘려서 동적 생성
		if (pShapes == NULL)
		{
			cout << "Error in expanding dynamic array for shapes capacity "
				<< capacity * 2 << "shapes " << endl;
			exit;
		}
		for (int i = 0; i < num_shapes; i++)
		{
			pShapes[i] = old_shapes[i];  //확장한 동적 배열에 원래의 배열 복사
		}
		capacity = capacity * 2;
		delete[] old_shapes;
	}
	pShapes[num_shapes] = pNew_shape;  //
	num_shapes++;
}

void ConsolePixelFrame::drawShapes()
{
	cout << "Drawing " << num_shapes << " shapes :" << endl;
	if (num_shapes > 0)
	{
		for (int i = 0; i < num_shapes; i++)
			pShapes[i]->draw(*this);  //기반 클래스가 각 각 가리키고 있는 도형의 draw
	}
}

bool ConsolePixelFrame::isValidIndex(int index) //정상적인 범위 안에 있는지
{
	if ((index < 0) || (index >= num_shapes))
	{
		cout << "Error in ConsolePixelFrame::isValidIndex : current number of shapes ("
			<< num_shapes << "), index : " << index << ") !!" << endl;
		return false;
	}
	else
		return true;
}
