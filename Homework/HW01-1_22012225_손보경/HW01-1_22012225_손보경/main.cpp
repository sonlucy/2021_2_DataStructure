/***
* Homework 1-2 
*  0~32 정수를 10진수, 8진수 16진수, 2진수로 출력하기.
* 8진수는 O, 16진수는 0x 접두어 표시할것.
* 
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자:2021-09-02
***/
#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;

//1~32숫자를 
//10진수, 8진수,16진수, 2진수 차례대로 출력
void main()
{

	for (int i = 0; i <= 32; i++)
	{
		std::cout <<setw(7)<< std::dec << i;  //10진수
		std::cout << setw(7) <<"O" << std::oct << i; //8진수
		std::cout << setw(7) <<"0x"<< std::hex << i;  //16진수
		cout <<setw(15)<< bitset<8>(i);  //2진수
		cout<<endl;
	}
}