#pragma once
#ifndef CMPLXARRAY_H
#define CMPLXARRAY_H
#include <iostream>
#include "Cmplx.h"
using namespace std;

class CmplxArray {
public: 
	CmplxArray(int size); // constructor 
	CmplxArray(const CmplxArray& obj); // constructor

	~CmplxArray(); 
	int size() { return cmplxArrySize; } 
	Cmplx &operator[](int);   //해당하는 인덱스의 원소를 반환하도록
	void print(ostream& fout);
	void sort();  //절댓값으로 정렬
private: 
	Cmplx* pCA; 
	int cmplxArrySize; 
	void subError();
	//bool isValidIndex(int indx);  //정상적인 범위안에 있는지
};
#endif
