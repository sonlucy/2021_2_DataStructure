#ifndef MTRXARRAY_H
#define MTRXARRAY_H

#include <iostream>
#include "MtrxArray.h"
using namespace std;

class Mtrx;

class MtrxArray
{
public:
	MtrxArray(int arraySize); // constructor 
	MtrxArray(const MtrxArray&);//////////////////////////
	~MtrxArray(); // destructor 
	Mtrx& operator[](int);
	int getSize() { return mtrxArraySize; }
	bool isValidIndex(int index);
private:
	Mtrx* pMtrx;
	int mtrxArraySize;
	//bool isValidIndex(int index);
};
#endif

