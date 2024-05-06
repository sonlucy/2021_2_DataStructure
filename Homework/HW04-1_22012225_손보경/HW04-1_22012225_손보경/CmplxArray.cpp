#include "CmplxArray.h"
#include "Cmplx.h"

CmplxArray::CmplxArray(int size) // constructor
{
	cmplxArrySize = size;
	this->pCA = new Cmplx[size];
	for (int i = 0; i < size; i++) {
		this->pCA[i].real = 0.0;
		this->pCA[i].imag = 0.0;
	}
}

CmplxArray::CmplxArray(const CmplxArray& obj) // constructor
{
	cmplxArrySize = obj.cmplxArrySize;
	this->pCA = new Cmplx[cmplxArrySize];
	for (int i = 0; i < cmplxArrySize; i++) {
		this->pCA[i] = obj.pCA[i]; // *(pCA+i) = obj.pCA[i];
	}
}

CmplxArray::~CmplxArray() // destructor
{
	if (cmplxArrySize > 0)
		delete[] pCA;
}

void CmplxArray::subError()
{
	cout << "ERROR: Subscript out of range.₩n";
	exit(0);
}

Cmplx& CmplxArray::operator [](int sub)
{
	if (sub < 0 || sub >= cmplxArrySize) // checking validity of range
		subError();
	return pCA[sub];  //해당하는 인덱스 원소 반환
}

void CmplxArray::print(ostream& fout)  
{
	fout << pCA;  
}

void CmplxArray::sort()  //절댓값으로 정렬  
{

	//pCA->real
	int i, j;
	int min, min_pos;
	Cmplx temp;

	min= pCA->mag();

	for (i = 0; i < cmplxArrySize; i++)
	{
		pCA++;
		//pCA->mag();
		if (min > pCA->mag())
		{
			min = pCA->mag();
		}
		if (min != i)
		{
			temp = pCA[i];
			pCA[i] = pCA[min];
			pCA[min] = temp;
		}
		//min = sqrt((pCA->real[i] * pCA->real) + (pCA->imag * pCA->imag));
	
	}
}