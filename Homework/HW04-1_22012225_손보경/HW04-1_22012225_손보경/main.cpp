/***
* HW4
* operator overloading for Class complex number
* 
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자: 2021-09-24
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
	fin >> cmplxs[0] >> cmplxs[1]; //파일로부터 복소수 성분 입력 받고
	cmplxs[2] = cmplxs[0] + cmplxs[1];  //덧셈
	cmplxs[3] = cmplxs[0] - cmplxs[1];  //뺄셈
	cmplxs[4] = cmplxs[0] * cmplxs[1];  //곱셈
	cmplxs[5] = cmplxs[0] / cmplxs[1];  //나눗셈
	cmplxs[6] = ~cmplxs[0];  //허수부분 부호 반대

	/* 콘솔창에 출력 */
	cout << "cmplxs[0] = " << cmplxs[0] << endl;
	cout << "cmplxs[1] = " << cmplxs[1] << endl;
	cout << "cmplxs[2] = cmplxs[0] + cmplxs[1] = " << cmplxs[2] << endl;
	cout << "cmplxs[3] = cmplxs[0] - cmplxs[1] = " << cmplxs[3] << endl;
	cout << "cmplxs[4] = cmplxs[0] * cmplxs[1] = " << cmplxs[4] << endl;
	cout << "cmplxs[5] = cmplxs[0] / cmplxs[1] = " << cmplxs[5] << endl;
	cout << "cmplxs[6] = ~cmplxs[0] (conjugate) = " << cmplxs[6] << endl;

	/* 같은지 다른지 확인 후 출력 */
	if (cmplxs[0] == cmplxs[1])
		cout << "cmplxs[0] is equal to cmplxs[1]" << endl;
	else
		cout << "cmplxs[0] is not equal to cmplxs[1]" << endl;
	/* cmplxs[0] 성분을 복사 */
	cmplxs[1] = cmplxs[0];
	cout << "After cmplxs[1] = cmplxs[0]; ==> " << endl;
	if (cmplxs[0] == cmplxs[1])  //같으면
		cout << "cmplxs[0] is equal to cmplxs[1]" << endl;  //같다고 출력
	else
		cout << "cmplxs[0] is not equal to cmplxs[1]" << endl;

	fin.close();  //파일닫기
}