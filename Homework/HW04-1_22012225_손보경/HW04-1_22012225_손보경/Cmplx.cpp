#include <iostream>
#include "Cmplx.h"
using namespace std;

Cmplx::Cmplx(double r, double i) :real(r), imag(i) { } // constructor

double Cmplx::mag(/*const Cmplx& c*/)
{
	double result;

	result = sqrt(real * real + imag * imag); //���� ���
	return result;
}

const Cmplx Cmplx::operator+(const Cmplx& c) 
{
	Cmplx result;
	result.real = real + c.real; 
	result.imag = imag + c.imag;

	return result;
}

const Cmplx Cmplx::operator-(const Cmplx& c)
{
	Cmplx result;
	result.real = real - c.real; 
	result.imag = imag - c.imag;
	
	return result;
}

const Cmplx Cmplx::operator*(const Cmplx& c)
{
	Cmplx result;

	result.real = real * c.real - (imag * c.imag);
	result.imag = (real * c.imag) + (imag * c.real);

	return result;
}

const Cmplx Cmplx::operator/(const Cmplx& c)
{
	Cmplx result;
	double denom;

	denom = c.real * c.real + c.imag * c.imag;
	result.real = ((real * c.real) + (imag * c.imag)) / denom;
	result.imag = ((c.real * imag) - (real * c.imag)) / denom;

	return result;
}

const Cmplx Cmplx::operator~()  //x�� �������� �ݴ��
{
	Cmplx result;

	result.real = real;
	result.imag = -imag;  //����κ��� ��ȣ�� �ݴ��

	return result;
}

bool Cmplx::operator==(const Cmplx& c)
{
	if ((real == c.real) && (imag == c.imag))
		return true;
	else
		return false;
}
bool Cmplx::operator!=(const Cmplx& c)
{
	if ((real == c.real) && (imag == c.imag))
		return false;
	else
		return true;

}
bool Cmplx::operator<(const Cmplx& c)
{
	double c_result;
	c_result = sqrt((c.real * c.real) + (c.imag * c.imag));
	if (mag() < c_result)  
		return true;
	else
		return false;
	
}

bool Cmplx::operator>(const Cmplx& c)
{
	double c_result;
	c_result = sqrt((c.real * c.real) + (c.imag * c.imag));
	if (mag() < c_result)
		return false;
	else
		true;
	
}

const Cmplx Cmplx::operator=(const Cmplx& c)
{
	/* ���޹��� ������ �ʱ�ȭ */
	real = c.real;
	imag = c.imag;

	return *this;  
}
	

ostream& operator<<(ostream& fout, const Cmplx& c)
{
	fout << "Complex ( " << c.real << ", " << c.imag << " )" << endl;
	return fout;
}

istream& operator>>(istream& fin, Cmplx& c)
{
	fin >> c.real >> c.imag;
	return fin;
}

//void Cmplx::printCmplx() { printf("Complex(%.2lf, %.2lf)", real, imag); }
