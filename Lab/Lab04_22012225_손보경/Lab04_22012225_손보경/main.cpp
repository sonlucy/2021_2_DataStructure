/***
* 
* Lab04 
* 연산자 오버로딩
* 
* 정보통신공학과 22012225 손보경
* 작성일자: 2021-09-21 
* 마지막 수정일자:
* 
* 지역변수에 대해 리턴바이레퍼런스 할 경우 함수 종료되면서 지역변수도 사라지기때문에 오류
***/

#include <iostream> 
#include <fstream> 
#include <string> 
//#include "Mtrx.h" 
#include "Class_Mtrx.h"
#include "MtrxArray.h" 
using namespace std;
#define NUM_MTRX 7 

int main()
{
	ifstream fin;
	ofstream fout;
	int n_row, n_col;


	/*for (int i = 0; i < NUM_MTRX; i++)
	{
		cout << mtrx[i];
	}*/

	fin.open("Matrix_data.txt");
	if (fin.fail())
	{
		cout << "Error in opening input data file !!" << endl;
		exit;
	}

	fout.open("Result.txt");
	if (fout.fail())
	{
		cout << "Error in opening output data file !!" << endl;
		exit;
	}


	MtrxArray mtrx(NUM_MTRX);

	fin >> mtrx[0] >> mtrx[1] >> mtrx[2];   //파일로부터 읽어들이고

	/* 이름 설정 */
	mtrx[0].set_name("mtrx[0] =");
	mtrx[1].set_name("mtrx[1] =");
	mtrx[2].set_name("mtrx[2] =");

	/* 파일로부터 읽어들인 행렬 출력 */
	fout << mtrx[0] << endl;
	fout << mtrx[1] << endl;
	fout << mtrx[2] << endl;


	/* 덧셈 */
	//mtrx[3].get_n_row(); mtrx[3].get_n_col();
	mtrx[3] = mtrx[0] + mtrx[1];  //
	mtrx[3].set_name("mtrx[3] = mtrx[0] + mtrx[1] =");
	fout << mtrx[3] << endl;

	/* 뺄셈 */
	mtrx[4] = mtrx[0] - mtrx[1];
	mtrx[4].set_name("mtrx[4] = mtrx[0] - mtrx[1] =");
	fout << mtrx[4] << endl;

	/* 곱셈 */
	mtrx[5] = mtrx[0] * mtrx[2];  //5*7   *   7*5   =  5 *5
	mtrx[5].set_name("mtrx[5] = mtrx[0] * mtrx[2] =");
	fout << mtrx[5] << endl;

	/* transpose */
	mtrx[6] = ~mtrx[5];
	mtrx[6].set_name("mtrx[6] = ~mtrx[5] (transposed matrix) =");
	fout << mtrx[6] << endl;


	/* 같은지 다른지 검사 */
	if (mtrx[5] == mtrx[6])
		fout << "mtrx[5] and mtrx[6] are equal.\n";
	if (mtrx[5] != mtrx[6])
		fout << "mtrx[5] and mtrx[6] are not equal.\n";

	fin.close();
	fout.close();
	return 0;
}