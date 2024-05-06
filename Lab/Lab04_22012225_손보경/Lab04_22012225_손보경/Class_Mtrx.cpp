
#include "Class_Mtrx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
typedef double* DBLPTR;

//Mtrx::Mtrx(int row, int col) : n_row(row), n_col(col) dM(NULL){}


/*Mtrx::Mtrx(int row, int col)
	:n_row(row), n_col(col)
{
	dM = new DBLPTR[n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	}
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = 0.0;
		}
	}
}*/

Mtrx::Mtrx()
{
	name = "nomatrix";
	dM = NULL;
	n_row = 0;
	n_col = 0; 

}

Mtrx::Mtrx(int num_row, int num_col)
{
	int i, j;

	n_row = num_row;
	n_col = num_col;
	dM = new DBLPTR[n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	}
	/*초기화*/
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = 0.0;
		}
	}
}
/*Mtrx::Mtrx(int row, int col)  //////////////////////////////////////
	: n_row(row), n_col(col)
{
	//name = "nomatrix";
	//n_row = 0;
	//n_col = 0;
	///////dM = NULL;
	//n_row = 5;  ///////////////////////////////////////
	//n_col = 7;
	DBLPTR* dM;
	int i, j;
	dM = new DBLPTR[n_row];

	for (i = 0; n_row; i++) 
	{
		dM[i] = new double[n_col];
	}

	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < n_col; j++)
		{
			dM[i][j] = 0.0;
		}
	}


	//////////////////dM = new DBLPTR[n_row];

}*/

Mtrx::Mtrx(string nm, int num_row, int num_col)
	: name(nm), n_row(num_row), n_col(num_col)  //
{
	int i, j;
	//cout <<"Mtrx constructor (int size: " 
	// << size << ")\n";

	**dM;
	dM = new DBLPTR[n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	}
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = 0.0;
		}
	}
	// cout <<"End of Mtrx constructor... \n";
}

Mtrx::Mtrx(string nm, double* pA, int num_row, int num_col)  /////
{
	int i, j, cnt;
	n_row = num_row;
	n_col = num_col;

	/*동적배열 생성*/
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
			if (cnt < sizeof(pA))
			{
				dM[i][j] = pA[cnt++];
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
	// DBLPTR *dM; /* defined in class, as private data member
	int i, j, size_row, size_col, num_data, cnt;
	double d;
	//cout <<"Mtrx constructor (double **dA, int size: " << size << ") \n";

	fin >> size_row >> size_col;  //파일로부터 행, 열 개수 읽어들이고

	n_row = size_row;
	n_col = size_col;
	/* 파일로부터 읽어들인 행렬 크기로 동적 2차원 배열 생성 */
	dM = new DBLPTR[n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	}

	/*cnt = 0;
	num_data = n_row * n_col;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			if ((fin.eof()) || (cnt >= num_data))
				dM[i][j] = 0.0;
			else
			{
				fin >> d;
				dM[i][j] = d;
				cnt++;
			}
		}
	}*/

	/* 초기화 부분 */
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			if (fin.eof())
				dM[i][j] = 0.0;
			else
			{
				fin >> d;
				dM[i][j] = d;
			}
		}
	}
	//cout <<"End of Mtrx constructor... \n";
}


#define SETW 10
ostream& operator<< (ostream& fout, const Mtrx& m)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	//fout << m.get_name() << endl;
	fout << m.name << endl;   //이름 출력
	
	for (int i = 0; i < m.n_row; i++) {
		for (int j = 0; j < m.n_col; j++)
		{
			fout.setf(ios::fixed);
			fout.precision(2);  //소수점이하 두자리까지 표시되도록
			if ((i == 0) && (j == 0))
				fout << a6 << a3 << setw(SETW) << m.dM[i][j];
			else if ((i == 0) && (j == (m.n_col - 1)))
				fout << setw(SETW) << m.dM[i][j] << a6 << a4;
			else if ((i > 0) && (i < (m.n_row - 1)) && (j == 0))
				fout << a6 << a2 << setw(SETW) << m.dM[i][j];
			else if ((i > 0) && (i < (m.n_row - 1)) && (j == (m.n_col - 1)))
				fout << setw(SETW) << m.dM[i][j] << a6 << a2;
			else if ((i == (m.n_row - 1)) && (j == 0))
				fout << a6 << a6 << setw(SETW) << m.dM[i][j];
			else if ((i == (m.n_row - 1)) && (j == (m.n_col - 1)))
				fout << setw(SETW) << m.dM[i][j] << a6 << a5;
			else
				fout << setw(SETW) << m.dM[i][j];
		}
		fout << endl;
	}
	fout << endl;

	return fout;
}

istream& operator>> (istream& fin, Mtrx& m)
{
	int size_row, size_col;
	//	int n_row = m.get_n_row();
	//	int n_col = m.get_n_col();

		// 행과 열의 크기 입력받기 
	fin >> size_row >> size_col;
	m.n_row = size_row;
	m.n_col = size_col;

	//fin >> m.n_row >> m.n_col;

	double d;
	int i, j;


	m.dM = new DBLPTR[m.n_row];
	for (i = 0; i < m.n_row; i++)
	{
		m.dM[i] = new double[m.n_col];
	}
	for (i = 0; i < m.n_row; i++) {
		for (j = 0; j < m.n_col; j++) {
			if (fin.eof())  //파일의 끝이면
				m.dM[i][j] = 0.0;  //0으로 초기화
			else
			{
				fin >> d;
				m.dM[i][j] = d;  //파일로부터 읽어온 값으로 초기화
			}
		}
	}

	return fin;
}

const Mtrx Mtrx::operator+(const Mtrx& mA)
{
	int i, j;
	Mtrx mR("mR", mA.n_row, mA.n_col);

	for (i = 0; i < mA.n_row; i++) {
		for (j = 0; j < mA.n_col; j++) {
			mR.dM[i][j] = dM[i][j] + mA.dM[i][j];
		}
	}

	return mR;
}

const Mtrx Mtrx::operator-(const Mtrx& mA)
{
	int i, j;
	Mtrx mR("mR", mA.n_row, mA.n_col);

	for (i = 0; i < mA.n_row; i++) {
		for (j = 0; j < mA.n_col; j++) {
			mR.dM[i][j] = dM[i][j] - mA.dM[i][j];
		}
	}
	return mR;
}

const Mtrx Mtrx:: operator*(const Mtrx& mA)
{
	int i, j, k;
		//mA.n_col은 전달받은 행렬의 열크기. 즉, 파일로부터읽어들영햠
	Mtrx mR("mR", n_row, n_col);
	

	for (i = 0; i <n_row; i++)  //5
	{
		for (j = 0; j < mA.n_col; j++)  //5가 되어야하는디
		{
			mR.dM[i][j] = 0.0;
			for (k = 0; k < n_col; k++)  //7
			{
				mR.dM[i][j] += dM[i][k] * mA.dM[k][j];  //5*7 = 5*7  *  7*7
			}
		}
	}

	return mR;
}

const Mtrx Mtrx::operator~() // returns transposed matrix 
{
	int i, j;
	Mtrx mR("mR", n_col, n_row);

	for (i = 0; i < n_col; i++) {
		for (j = 0; j < n_row; j++) {
			mR.dM[i][j] = dM[j][i];
		}
	}
	
	/*int i, j;
	Mtrx mR("mR", n_col, mA.n_row);

	for (i = 0; i < n_row; i++) {
		for (j = 0; j < mA.n_col; j++) {
			mR.dM[j][i] = dM[i][j];
		}
	}*/
	return mR;
}

const Mtrx& Mtrx:: operator=(const Mtrx& mA)
{
	int i, j;
	Mtrx mR("mR", mA.n_row, mA.n_col);

	for (i = 0; i < mA.n_row; i++) {
		for (j = 0; j < mA.n_col; j++) {
			mR.dM[i][j] = mA.dM[i][j];  
		}
	}
	
	return mR;
}

bool Mtrx::operator==(const Mtrx& mA)
{

	int i, j;
	Mtrx mR("mR", n_row, n_col);
	
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			if (mR.dM[i][j] != mA.dM[i][j])
				return false; break;
		}
	}
	return true;
}

bool Mtrx::operator!=(const Mtrx& mA)
{
	int i, j;
	Mtrx mR("mR", n_row, n_col);

	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			if (mR.dM[i][j] != mA.dM[i][j])
				return true; break;
		}
	}
	return false;
}



void Mtrx::init(int n_row, int n_col)
{
	Mtrx(name, n_row, n_col);
}
