/***
* HW03-1 
* 정수 데이터를 1,000,000개 담을 수 있는 동적 배열 생성 및 정렬
* 
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자:2021-09-13
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
	ba_1.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES); //샘플출력

	ba_1.fprintStatistics(fout); //통계결과출력

	time_t start, end;
	double result;

	start = time(NULL); //시간 측정 시작
	ba_1.quick_sort();  //퀵 정렬
	end = time(NULL); //시간 측정 끝
	result = (double)(end - start);
	fout << endl << " Quick sorting array:\n";
	ba_1.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES); //샘플 출력
	fout << "-> 퀵 정렬 걸린 시간:" << result << endl;
	

	ba_1.suffle();  //뒤섞기
	fout << "\n Suffling array: \n";
	ba_1.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);  //뒤섞어진 샘플 출력


	
	start = time(NULL); //시간 측정 시작
	ba_1.selection_sort();  //선택 정렬
	end = time(NULL); //시간 측정 끝
	result = (double)(end - start);
	fout << endl << " Seletion sorting array\n";
	ba_1.fprintSample(fout, ELEMENTS_PER_LINE, SAMPLE_LINES);  //샘플출력
	fout << "-> 선택 정렬 걸린 시간:" << result << endl;

	fout.close();
}

