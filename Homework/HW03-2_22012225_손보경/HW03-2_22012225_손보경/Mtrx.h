#ifndef MTRX_H
#define MTRX_H
#include <iostream>
#include <fstream>
using namespace std;
#define MAX_SIZE 100

class Mtrx {
public:
	Mtrx(int num_row, int num_col);  //ũ�� ����
	Mtrx(double dA[], int num_data, int num_row, int num_col);
	Mtrx(istream& fin);  //���Ϸκ��� �о� ����� �ʱ�ȭ�ϱ�����
	~Mtrx(); //�Ҹ���
	int getN_row() { return n_row; } //�ళ�� �ޱ�
	int getN_col() { return n_col; }  //������ �ޱ�
	void fprintMtrx(ostream& fout);
	void setName(string nm) { name = nm; };  //�̸�����
	string getName() { return name; };
	Mtrx add(const Mtrx&);
	Mtrx sub(const Mtrx&);
	Mtrx multiply(const Mtrx&);
private:
	string name;
	int n_row;
	int n_col;
	double** dM;
};
#endif
