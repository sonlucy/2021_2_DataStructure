#ifndef MTRX_H
#define MTRX_H
#include <iostream>
#include <fstream>
using namespace std;
#define MAX_SIZE 100

class Mtrx {
public:
	Mtrx(int num_row, int num_col);  //크기 지정
	Mtrx(double dA[], int num_data, int num_row, int num_col);
	Mtrx(istream& fin);  //파일로부터 읽어 행렬을 초기화하기위함
	~Mtrx(); //소멸자
	int getN_row() { return n_row; } //행개수 받기
	int getN_col() { return n_col; }  //열개수 받기
	void fprintMtrx(ostream& fout);
	void setName(string nm) { name = nm; };  //이름지정
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
