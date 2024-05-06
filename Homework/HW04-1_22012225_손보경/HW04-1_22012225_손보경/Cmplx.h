#pragma once
#ifndef CMPLX_H
#define CMPLX_H
#include <iostream>
using namespace std; 
class CmplxArray; 

class Cmplx
{
	friend ostream& operator<< (ostream&, const Cmplx&); 
	friend istream& operator>> (istream&, Cmplx&); 
	friend class CmplxArray; //���Ҽ��� �迭�� ����� ����� �� �ֵ���
public: 
	Cmplx(double real = 0.0, double imag = 0.0); // constructor 
	double mag(); // return the magnitude (�Ǽ����������ϱ� ����������� ��Ʈ����� (¿�밪ũ���ȯ)
	const Cmplx operator+(const Cmplx &); 
	const Cmplx operator-(const Cmplx &); 
	const Cmplx operator*(const Cmplx &); 
	const Cmplx operator/(const Cmplx &);
	const Cmplx operator~(); // �ӷ����Ҽ�
	bool operator==(const Cmplx &); //������
	bool operator!=(const Cmplx &);   //�ٸ���
	bool operator<(const Cmplx &);    //ũ�� ��  (�������� ��)
	bool operator>(const Cmplx &); 
	const Cmplx operator=(const Cmplx &);  //����

private: 
	double real; 
	double imag;
};
#endif
