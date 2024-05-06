/***
*HW03-2
* 파일로부터 입력받아 행렬 3개를 저장하고, 이 행렬 간의 덧셈,뺼셈,곱셈 연산 결과 출력
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자: 20201-09-14
* 마지막 수정일자: 2021-09-17
***/


#include <iostream>
#include <fstream>
#include "Mtrx.h"
using namespace std;

void main()
{
	ifstream fin;
	ofstream fout;

	fin.open("input.txt");
	if (fin.fail())
	{
		cout << "Error in opening input.txt !!" << endl;
		exit;
	}


	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Error in opening Matrix_operations_results.txt !!" << endl;
		exit;
	}


	Mtrx mtrxA(fin);
	mtrxA.setName("MtrxA");
	int n_row = mtrxA.getN_row();
	int n_col = mtrxA.getN_col();
	fout << " MtrxA:\n";
	mtrxA.fprintMtrx(fout);

	Mtrx mtrxB(fin);
	mtrxB.setName("MtrxB");
	fout << " MtrxB:\n";
	mtrxB.fprintMtrx(fout);

	Mtrx mtrxC(fin);
	mtrxC.setName("MtrxC");
	fout << " MtrxC:\n";
	mtrxC.fprintMtrx(fout);

	Mtrx mtrxD(mtrxA.getN_row(), mtrxB.getN_col());
	mtrxD = mtrxA.add(mtrxB);
	mtrxD.setName("MtrxD = mtrxA.add(mtrxB)");
	fout << "MtrxD = mtrxA.add(mtrxB) = \n";
	mtrxD.fprintMtrx(fout);

	Mtrx mtrxE(mtrxA.getN_row(), mtrxB.getN_col());
	mtrxE = mtrxA.sub(mtrxB);
	mtrxE.setName("MtrxE = mtrxA.sub(mtrxB)");
	fout << "MtrxE = mtrxA.sub(mtrxB) = \n";
	mtrxE.fprintMtrx(fout);

	Mtrx mtrxF(mtrxA.getN_row(), mtrxC.getN_col());
	mtrxF = mtrxA.multiply(mtrxC);
	mtrxF.setName("MtrxF = mtrxA.multiply(mtrxC)");
	fout << "MtrxF = mtrxA.multiply(mtrxC) =\n";
	mtrxF.fprintMtrx(fout);

	fout.close();
}