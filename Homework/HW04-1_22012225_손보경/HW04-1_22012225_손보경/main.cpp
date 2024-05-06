/***
* HW4
* operator overloading for Class complex number
* 
* �ۼ���: ������Ű��а� 22012225 �պ���
* �ۼ�����: 2021-09-24
* 
***/

#include <iostream>
#include <fstream>
#include "CmplxArray.h"
#include "Cmplx.h"

using namespace std;

void main()
{
	ofstream fout;
	ifstream fin;
	CmplxArray cmplxs(7);
	fin.open("input.txt");
	if (fin.fail())
	{
		cout << "Error in opening intput.txt !!" << endl;
		exit;
	}
	fin >> cmplxs[0] >> cmplxs[1]; //���Ϸκ��� ���Ҽ� ���� �Է� �ް�
	cmplxs[2] = cmplxs[0] + cmplxs[1];  //����
	cmplxs[3] = cmplxs[0] - cmplxs[1];  //����
	cmplxs[4] = cmplxs[0] * cmplxs[1];  //����
	cmplxs[5] = cmplxs[0] / cmplxs[1];  //������
	cmplxs[6] = ~cmplxs[0];  //����κ� ��ȣ �ݴ�

	/* �ܼ�â�� ��� */
	cout << "cmplxs[0] = " << cmplxs[0] << endl;
	cout << "cmplxs[1] = " << cmplxs[1] << endl;
	cout << "cmplxs[2] = cmplxs[0] + cmplxs[1] = " << cmplxs[2] << endl;
	cout << "cmplxs[3] = cmplxs[0] - cmplxs[1] = " << cmplxs[3] << endl;
	cout << "cmplxs[4] = cmplxs[0] * cmplxs[1] = " << cmplxs[4] << endl;
	cout << "cmplxs[5] = cmplxs[0] / cmplxs[1] = " << cmplxs[5] << endl;
	cout << "cmplxs[6] = ~cmplxs[0] (conjugate) = " << cmplxs[6] << endl;

	/* ������ �ٸ��� Ȯ�� �� ��� */
	if (cmplxs[0] == cmplxs[1])
		cout << "cmplxs[0] is equal to cmplxs[1]" << endl;
	else
		cout << "cmplxs[0] is not equal to cmplxs[1]" << endl;
	/* cmplxs[0] ������ ���� */
	cmplxs[1] = cmplxs[0];
	cout << "After cmplxs[1] = cmplxs[0]; ==> " << endl;
	if (cmplxs[0] == cmplxs[1])  //������
		cout << "cmplxs[0] is equal to cmplxs[1]" << endl;  //���ٰ� ���
	else
		cout << "cmplxs[0] is not equal to cmplxs[1]" << endl;

	fin.close();  //���ϴݱ�
}