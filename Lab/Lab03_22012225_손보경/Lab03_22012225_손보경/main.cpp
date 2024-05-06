/***
* Lab03
* 파일로부터 행렬 크기와 행렬 원소들을 입력받고 덧셈, 뺄셈, 곱셈 연산
* 
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자: 2021-09-13
* 마지막 수정일자: 2021-09-17
****/

#include <iostream>
#include <fstream>
#include "Mtrx.h"
using namespace std;

void main()
{
	ifstream fin;
	ofstream fout;
	fin.open("Matrix_data.txt");
	if (fin.fail())
	{
		cout << "Error in opening Matrix_data.txt !!" << endl;
		exit;
	}
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Error in opening Matrix_operations_results.txt !!" << endl;
		exit;
	}

	Mtrx mtrxA(fin);   //파일로부터 먼저 행,열 개수 그리고 원소 초기화
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

	Mtrx mtrxF(mtrxA.getN_row(), mtrxC.getN_col());  //5, 5
	mtrxF = mtrxA.multiply(mtrxC);
	mtrxF.setName("MtrxF = mtrxA.multiply(mtrxC)");
	fout << "MtrxF = mtrxA.multiply(mtrxC) =\n";
	mtrxF.fprintMtrx(fout);

	Mtrx mtrxG(mtrxF.getN_col(), mtrxF.getN_row());  //전치 행렬
	mtrxG = mtrxF.trans_Mtrx();
	fout << "MtrxG = transpose MtrxF =\n";
	mtrxG.fprintMtrx(fout);



		//행, 렬 크기 바꾸고 대입할때도 바꿔서
	fout.close();


}
