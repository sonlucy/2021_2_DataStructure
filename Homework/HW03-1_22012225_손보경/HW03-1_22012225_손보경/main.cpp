/***
* HW03-1 
* ���� �����͸� 1,000,000�� ���� �� �ִ� ���� �迭 ���� �� ����
* 
* �ۼ���: ������Ű��а� 22012225 �պ���
* �ۼ�����:2021-09-13
***/

#include <iostream>
#include <fstream>
#include "BigArray.h"
using namespace std;
#define ELEMENTS_PER_LINE 10
#define SAMPLE_LINES 3

void main()
{
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Error in opening output.txt !!"
			<< endl;
		exit;
	}
	int base_offset = -5000000;  ///////////////
	int big_rand_size = 1000000;
	BigArray ba_1(big_rand_size);
	fout << "Generating big rand array of "
		<< ba_1.size() << " elements with base_offset " << base_offset << " ... "
		<< endl;

	ba_1.genBigRandArray(base_offset);
	ba_1.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES); //�������

	ba_1.fprintStatistics(fout); //��������

	time_t start, end;
	double result;

	start = time(NULL); //�ð� ���� ����
	ba_1.quick_sort();  //�� ����
	end = time(NULL); //�ð� ���� ��
	result = (double)(end - start);
	fout << endl << " Quick sorting array:\n";
	ba_1.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES); //���� ���
	fout << "-> �� ���� �ɸ� �ð�:" << result << endl;
	

	ba_1.suffle();  //�ڼ���
	fout << "\n Suffling array: \n";
	ba_1.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);  //�ڼ����� ���� ���


	
	start = time(NULL); //�ð� ���� ����
	ba_1.selection_sort();  //���� ����
	end = time(NULL); //�ð� ���� ��
	result = (double)(end - start);
	fout << endl << " Seletion sorting array\n";
	ba_1.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);  //�������
	fout << "-> ���� ���� �ɸ� �ð�:" << result << endl;

	fout.close();
}

