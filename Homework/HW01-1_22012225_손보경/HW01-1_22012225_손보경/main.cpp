/***
* Homework 1-2 
*  0~32 ������ 10����, 8���� 16����, 2������ ����ϱ�.
* 8������ O, 16������ 0x ���ξ� ǥ���Ұ�.
* 
* �ۼ���: ������Ű��а� 22012225 �պ���
* �ۼ�����:2021-09-02
***/
#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;

//1~32���ڸ� 
//10����, 8����,16����, 2���� ���ʴ�� ���
void main()
{

	for (int i = 0; i <= 32; i++)
	{
		std::cout <<setw(7)<< std::dec << i;  //10����
		std::cout << setw(7) <<"O" << std::oct << i; //8����
		std::cout << setw(7) <<"0x"<< std::hex << i;  //16����
		cout <<setw(15)<< bitset<8>(i);  //2����
		cout<<endl;
	}
}