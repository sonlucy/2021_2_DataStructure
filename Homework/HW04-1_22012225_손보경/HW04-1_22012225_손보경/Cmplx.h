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
	friend class CmplxArray; //복소수를 배열로 만들어 사용할 수 있도록
public: 
	Cmplx(double real = 0.0, double imag = 0.0); // constructor 
	double mag(); // return the magnitude (실수부제곱더하기 허수부제곱의 루트씌운거 (쩔대값크기반환)
	const Cmplx operator+(const Cmplx &); 
	const Cmplx operator-(const Cmplx &); 
	const Cmplx operator*(const Cmplx &); 
	const Cmplx operator/(const Cmplx &);
	const Cmplx operator~(); // 켤레복소수
	bool operator==(const Cmplx &); //같은지
	bool operator!=(const Cmplx &);   //다른지
	bool operator<(const Cmplx &);    //크기 비교  (절댓값으로 비교)
	bool operator>(const Cmplx &); 
	const Cmplx operator=(const Cmplx &);  //복사

private: 
	double real; 
	double imag;
};
#endif
