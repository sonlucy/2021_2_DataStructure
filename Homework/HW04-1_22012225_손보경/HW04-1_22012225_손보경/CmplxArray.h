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
	Cmplx &operator[](int);   //�ش��ϴ� �ε����� ���Ҹ� ��ȯ�ϵ���
	void print(ostream& fout);
	void sort();  //�������� ����
private: 
	Cmplx* pCA; 
	int cmplxArrySize; 
	void subError();
	//bool isValidIndex(int indx);  //�������� �����ȿ� �ִ���
};
#endif
