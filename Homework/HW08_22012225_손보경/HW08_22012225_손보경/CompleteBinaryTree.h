#pragma once

#ifndef Complete_Binary_Tree_H
#define Complete_Binary_Tree_H
/////////////////#include "TA_Entry.h"
#include <iomanip>
#include <string>
#include <fstream>
#define CBT_ROOT 1

template<typename T>
class CompleteBinaryTree //: //public TA_Entry<T>
{
public:

	CompleteBinaryTree(int capa);
	//int add_at_end(T& elem);  ///완전이진트리 끝 노드에 이벤트 더하기
	T& getEndElement() { return this->t_array[end]; }  //end노드 읽어오기
	T& getRootElement() { return this->t_array[CBT_ROOT]; }   //root노드 읽어오기
	int getEndIndex() { return end; }
	void removeCBTEnd();  //end노드 삭제

	//void fprintCBT(ofstream& fout);
	void fprintCBT_byLevel(ofstream& fout);



protected:
	void _printCBT_byLevel(ofstream& fout, int p, int level);
	int parentIndex(int index) { return index / 2; }
	int leftChildIndex(int index) { return index * 2; }
	int rightChildIndex(int index) { return (index * 2 + 1); }
	bool hasLeftChild(int index) { return ((index * 2) <= end); }  //왼쪽자식 있는지
	bool hasRightChild(int index) { return ((index * 2 + 1) <= end); }  //오른쪽 자식 있는지
	int end;
};


template<typename T>
CompleteBinaryTree<T>::CompleteBinaryTree(int capa)
	//:TA_Entry<T>(capa, nm)  //
{
	end = 0; // reset to empty
}

/*template<typename T>
void CompleteBinaryTree<T>::fprintCBT(ofstream& fout)
{
	if (end <= 0)
	{
		fout  << "CBT is empty now !!" << endl;
		return;
	}
	int count = 0;
	for (int i = 1; i <= end; i++)
	{
		fout << setw(3) << this->t_array[i] << endl;  ///////this
		//if ((((count + 1) % 10) == 0) && (i != end))
		//fout << endl;
		count++;
	}
}*/

template<typename T>
void CompleteBinaryTree<T>::_printCBT_byLevel(ofstream& fout, int index, int level) //오른쪽자식->그부모자식->왼쪽자식 순 출력
{
	int index_child;
	if (hasRightChild(index))  //오른쪽 자식 있으면
	{
		index_child = rightChildIndex(index);  //오른쪽자식 인덱스 받아와서
		_printCBT_byLevel(fout, index_child, level + 1);  //오른쪽 자식이 없을때까지 쭉 
	}
	for (int i = 0; i < level; i++)
		fout << "    "; //누적되어있는 level(깊이)만큼 들여쓰기
	this->t_array[index].fprint(fout);  //그 항목 출력
	fout << endl;  //줄바꿈
	if (hasLeftChild(index))
	{
		index_child = leftChildIndex(index);  //왼쪽 자식 있으면 왼쪽자식 인덱스 받아오
		_printCBT_byLevel(fout, index_child, level + 1);
	}
}
template<typename T>
void CompleteBinaryTree<T>::fprintCBT_byLevel(ofstream& fout)
{
	if (end <= 0)
	{
		fout << "CBT is EMPTY now !!" << endl;
		return;
	}
	_printCBT_byLevel(fout, CBT_ROOT, 0);
}

/*template<typename T>
int CompleteBinaryTree<T>::add_at_end(T& elem)
{
	if (end >= this->capacity)
	{
		cout << this->getName() << " is FULL now !!" << endl;
		return end;
	}
	end++;  //end위치 증가시킨후
	this->t_array[end] = elem;  ///그 위치에 엘리먼트 추가
	return end;
}*/

template<typename T>
void CompleteBinaryTree<T>::removeCBTEnd()
{
	end--;
	this->num_elements--;
}

#endif