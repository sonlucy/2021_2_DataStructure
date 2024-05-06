/***
* Homework 1 - 1 ���� �Է� �� ������ ��� �м�
* �ۼ���: ������Ű��а� 22012225 �պ���
* �ۼ�����: 2021-09-02
* 
***/

#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

int fileInputData(ifstream& fin, int* data_array, int max_num_data);
void getStatistics_fileOut(int* data_array, int num_data, ofstream& fout);

void main()
{
	ifstream fin;
	ofstream fout;
	int data_array[10];

	fin.open("input_data.txt");
	if (fin.fail())
	{
		cout << "Fail to open an input file" << "(input_data.txt)" << endl;
		exit(1);
	}
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open an output file" << "(output_data.txt)" << endl;
		exit(1);
	}

	fout << "Total 10 input from input data file." << endl;
	int NUM_DATA = fileInputData(fin, data_array, 10);
	getStatistics_fileOut(data_array, NUM_DATA, fout);

	fin.close();
	fout.close();

}

int fileInputData(ifstream& fin, int* data_array, int max_num_data)
{
	//10���� ���� �����͸� ���Ϸκ��� �Է� �޴� ��� ����

	int i;
	for ( i = 0; i < max_num_data; i++)
	{
		fin >> data_array[i];
	}
	return i; //�Էµ� ������ ���� ��ȯ
}

void getStatistics_fileOut(int* data_array, int num_data, ofstream& fout)
{
	//�Էµ� �������� ��� �м� ��� ����
	//�Էµ� �����Ϳ� ���� ��� �����ʹ� output.txt ���Ϸ� ����Ұ�.
	int min, max, sum=0;
	double avg=0.0, var=0.0, std_dev=0.0;
	double sq_diff_sum = 0.0;
	int i = 0;
	min = data_array[i];
	max = data_array[i];
	sum += data_array[i];
	for (int j = i+1; j < num_data; j++)
	{
		sum += data_array[j];
		if (data_array[j] < min)
			min = data_array[j];
		if (data_array[j] > max)
			max = data_array[j];
	}
	avg = sum / (double)num_data;
	for (int i = 0; i < num_data; i++)
	{
		double diff = data_array[i] - avg;
		sq_diff_sum += diff * diff;
	}
	var = sq_diff_sum / num_data;
	std_dev = sqrt(var);

	fout << "Total " << num_data << " integer data: {";
	for (int i = 0; i < num_data; i++)
	{
		fout << data_array[i] << ",";
	}
	fout << "} " << endl;

	fout << "min(" << min << "), max(" << max << "),";
	fout << " sum(" << sum << "), average(" << avg << ")" << endl;
	fout << "variance(" << var << "), standard deviation (" << std_dev << ")" << endl;
}
