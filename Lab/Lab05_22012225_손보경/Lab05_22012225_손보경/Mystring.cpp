#include "Mystring.h"

string genRandName()
{
	string name;
	char na[10] = { NULL };
	int name_len, i;

	na[0] = rand() % 26 + 'A';  //첫글자 대문자로
	name_len = rand() % 4 + 3;  // 3 ~ 6
	for (i = 1; i <= name_len; i++)
	{
		na[i] = rand() % 26 + 'a';  //소문자
	}

	name = na;
	return name;
}

string genRandDeptString()
{
	string dept;
	char de[10] = { NULL };
	int dept_len, i;

	dept_len = rand() % 2 + 3;  //3 ~4
	for (i = 0; i < dept_len; i++)
	{
		de[i] = rand() % 26 + 'A'; //대문자조합으로
	}
	
	dept = de;
	return dept;
}