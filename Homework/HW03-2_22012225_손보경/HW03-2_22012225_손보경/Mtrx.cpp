#include "Mtrx.h"
#include <iostream>
#include <iomanip>
using namespace std;
typedef double* DBLPTR;

Mtrx::Mtrx(int num_row, int num_col)
{
	int i, j;
	//cout <<"Mtrx constructor (int size: " 
	// << size << ")₩n";
	n_row = num_row;
	n_col = num_col;
	/* 동적배열 생성 */
	dM = new DBLPTR[n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	}
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = 0.0;  //초기화
		}
	}
	// cout <<"End of Mtrx constructor... ₩n";
}

Mtrx::Mtrx(double dA[], int num_data, int num_row, int num_col)
{
	int i, j, cnt;
	n_row = num_row;
	n_col = num_col;

	/* 동적 배열 생성 */
	dM = new DBLPTR[n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	}

	cnt = 0;
	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < n_col; j++)
		{
			if (cnt < num_data)
			{
				dM[i][j] = dA[cnt++];
			}
			else  //행렬 데이터 개수보다 더 크게되면
			{
				dM[i][j] = 0.0;  //0으로 초기화
			}
		}
	}
}


Mtrx::~Mtrx()
{
	// cout << "destructor of Mtrx (" 
	// << name << ")" << endl;
	/*
	for (int i=0; i<n_row; i++)
	delete [] dM[i];
	delete [] dM;
	*/
}

Mtrx::Mtrx(istream& fin)
{
	//DBLPTR *dM; 
	int i, j, size_row, size_col, num_data, cnt;
	double d;
	//cout <<"Mtrx constructor (double **dA, int size: " << size << ")₩n";
	fin >> size_row >> size_col;  //파일로부터 행, 열 크기 입력받고
	n_row = size_row;
	n_col = size_col;

	/* 파일로부터 입력받은 행렬크기에 맞춰 동적 배열 생성*/
	dM = new DBLPTR[n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	}
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			if (fin.eof()) //파일의 끝이면
				dM[i][j] = 0.0;  //0으로 초기화
			else
			{
				fin >> d;
				dM[i][j] = d;  //파일로부터 읽어온 값으로 초기화
			}
		}
	}
	//cout <<"End of Mtrx constructor... ₩n;'
}

#define SETW 10
void Mtrx::fprintMtrx(ostream& fout)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	for (int i = 0; i < n_row; i++) {
		for (int j = 0; j < n_col; j++)
		{
			fout.setf(ios::fixed);
			fout.precision(2);
			if ((i == 0) && (j == 0))
				fout << a6 << a3 << setw(SETW) << dM[i][j];
			else if ((i == 0) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a4;
			else if ((i > 0) && (i < (n_row - 1)) && (j == 0))
				fout << a6 << a2 << setw(SETW) << dM[i][j];
			else if ((i > 0) && (i < (n_row - 1)) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a2;
			else if ((i == (n_row - 1)) && (j == 0))
				fout << a6 << a6 << setw(SETW) << dM[i][j];
			else if ((i == (n_row - 1)) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a5;
			else
				fout << setw(SETW) << dM[i][j];
		}
		fout << endl;
	}
	fout << endl;
}

Mtrx Mtrx::add(const Mtrx& mA)  //call by reference
{
	int i, j;
	Mtrx mR(n_row, n_col);
	mR.setName("R");
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] + mA.dM[i][j];
		}
	}
	return mR;  //return by value
}

Mtrx Mtrx::sub(const Mtrx& mA)
{
	int i, j;
	Mtrx mR(n_row, n_col);
	mR.setName("R");
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] - mA.dM[i][j];
		}
	}
	return mR;
}

Mtrx Mtrx::multiply(const Mtrx& mA)
{
	int i, j, k;
	Mtrx mR(n_row, mA.n_col);
	mR.setName("R");
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < mA.n_col; j++) {
			mR.dM[i][j] = 0.0;
			for (k = 0; k < n_col; k++) {
				mR.dM[i][j] += dM[i][k] * mA.dM[k][j];
			}
		}
	}
	return mR;
}

