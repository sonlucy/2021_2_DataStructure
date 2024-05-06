#include "MtrxArray.h"
//#include "Mtrx.h"
#include "Class_Mtrx.h"

MtrxArray::MtrxArray(int arraySize) // constructor
{
	mtrxArraySize = arraySize;
	pMtrx = new Mtrx[mtrxArraySize];  
	

}

MtrxArray::MtrxArray(const MtrxArray& m)  ////////////////?
{
	mtrxArraySize = m.mtrxArraySize;
	/*for (int i = 0; i < mtrxArraySize; i++)
	{
		pMtrx[i] = m.pMtrx[i];
	}*/

	this->pMtrx = new Mtrx[mtrxArraySize];
	for (int i = 0; i < mtrxArraySize; i++)
	{
		this->pMtrx[i] = m.pMtrx[i];
	}
}

MtrxArray::~MtrxArray()
{
	//cout << "MtrxArray :: destructor" << endl;
	if (pMtrx != NULL) {
		delete[] pMtrx;
	}
}

bool MtrxArray::isValidIndex(int index)
{
	if (index < 0 || index >= mtrxArraySize)
	{
		cout << "ERROR: given index is out of range. \n";
		exit(0);
	}
	else
		return true;
}

Mtrx& MtrxArray::operator [](int sub)
{
	if (sub < 0 || sub >= mtrxArraySize)
	{
		cout << "ERROR: Subscript out of range.₩n";
		exit(0);
	}
	return pMtrx[sub];
}

