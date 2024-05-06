#ifndef VECTOR_HANDLER_H 
#define VECTOR_HANDLER_H 
#include <vector>
#include <algorithm> 
#include "Time.h"
#include "Date.h"
#include "Student.h"

template<typename T>
void printVector(vector<T>& v)
{
	string typeName = typeid(T).name();  //� �ڷ������� �о��
	cout << "Vector size(" << v.size() << "), elements : \n";
	typename vector<T>::iterator p;  //�ݺ��� p
	for (p = v.begin(); p != v.end(); p++)  
	{
		/* �ݺ���(p)�� ����Ű�� �ִ� �� ���*/
		cout << *p << " ";  //�������� �̿�

		if ((typeName == "class Date") || (typeName == "class Time"))  //main -> STEP_1����
			continue;  //�׳� ���
		else
			cout << endl;  //
	}
	cout << endl;
}
#endif