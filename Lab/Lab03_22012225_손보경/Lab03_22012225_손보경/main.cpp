/***
* Lab03
* ���Ϸκ��� ��� ũ��� ��� ���ҵ��� �Է¹ް� ����, ����, ���� ����
* 
* �ۼ���: ������Ű��а� 22012225 �պ���
* �ۼ�����: 2021-09-13
* ������ ��������: 2021-09-17
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

	Mtrx mtrxA(fin);   //���Ϸκ��� ���� ��,�� ���� �׸��� ���� �ʱ�ȭ
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

	Mtrx mtrxG(mtrxF.getN_col(), mtrxF.getN_row());  //��ġ ���
	mtrxG = mtrxF.trans_Mtrx();
	fout << "MtrxG = transpose MtrxF =\n";
	mtrxG.fprintMtrx(fout);



		//��, �� ũ�� �ٲٰ� �����Ҷ��� �ٲ㼭
	fout.close();


}
