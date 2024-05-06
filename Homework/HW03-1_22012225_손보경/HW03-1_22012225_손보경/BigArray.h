#ifndef BIG_ARRAY_H
#define BIG_ARRAY_H
#include <iostream>
#include <fstream>
using namespace std;

typedef struct
{
	int min;
	int max;
	double avg; // average
	int mean;
	double var; // variance
	double std_dev; // standard deviation
} ArrayStatistics;

class BigArray
{
public:
	BigArray(int n); // constructor
	~BigArray(); // destructor
	void genBigRandArray(int base_offset);
	int size() { return num_elements; }
	void suffle();  //섞어주는 함수
	void selection_sort();  //선택정렬
	void quick_sort();  //퀵정렬
	void getStatistics(ArrayStatistics&);  //통계
	void fprintStatistics(ostream& fout);  //통계결과 출력
	void fprintBigArray(ostream& fout, int elements_per_line);
	void fprintSample(ostream& fout, int elements_per_line, int num_sample_lines);  //샘플 출력
private:
	int* big_array;
	int num_elements;
};
#endif