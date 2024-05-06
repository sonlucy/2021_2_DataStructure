#pragma once
#ifndef CLASS_MTRX_H 
#define CLASS_MTRX_H 
#include <string> 
using namespace std;
class MtrxArray;

class Mtrx {
	friend ostream& operator<< (ostream& fout, const Mtrx& m);
	friend istream& operator>> (istream& fin, Mtrx& m);
	friend class MtrxArray;  //////////
public:
	Mtrx(int num_row, int num_col);
	Mtrx();
	//Mtrx(int n_row=0, int n_col=0);//:name(string("nomatrix")), n_row(0), n_col(0), dM(NULL){}; // default constructor 
	//Mtrx(string name = "nomatrix", int n_row = 0, int n_col = 0);
	Mtrx(string nm, int num_row, int num_col);
	Mtrx(string nm, double* pA, int num_row, int num_col);
	Mtrx(istream& fin);  //얘가 파일로부터 행, 열 크기와 원소들 입력받는 역할. 
	~Mtrx();
	void init(int n_row, int n_col);

	void set_name(string nm) { name = nm; }
	string get_name() { return name; }

	//void set_n_row(int row) { n_row = row; } ///////////
	//void set_n_col(int col) { n_col = col; }  ///////////
	int get_n_row() const { return n_row; }
	int get_n_col() const { return n_col; }

	const Mtrx operator+(const Mtrx& mA);
	const Mtrx operator-(const Mtrx& mA);
	const Mtrx operator*(const Mtrx& mA);
	const Mtrx operator~(); // returns transposed matrix 
	const Mtrx& operator=(const Mtrx& mA);

	bool operator==(const Mtrx&mA );
	bool operator!=(const Mtrx& mA);

private:
	string name;
	int n_row;
	int n_col;
	double** dM;
};
#endif