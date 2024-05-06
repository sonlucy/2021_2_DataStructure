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
	string typeName = typeid(T).name();  //어떤 자료형인지 읽어내고
	cout << "Vector size(" << v.size() << "), elements : \n";
	typename vector<T>::iterator p;  //반복자 p
	for (p = v.begin(); p != v.end(); p++)  
	{
		/* 반복자(p)가 가리키고 있는 값 출력*/
		cout << *p << " ";  //간접참조 이용

		if ((typeName == "class Date") || (typeName == "class Time"))  //main -> STEP_1에서
			continue;  //그냥 계속
		else
			cout << endl;  //
	}
	cout << endl;
}
#endif