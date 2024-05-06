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
	//int add_at_end(T& elem);  ///��������Ʈ�� �� ��忡 �̺�Ʈ ���ϱ�
	T& getEndElement() { return this->t_array[end]; }  //end��� �о����
	T& getRootElement() { return this->t_array[CBT_ROOT]; }   //root��� �о����
	int getEndIndex() { return end; }
	void removeCBTEnd();  //end��� ����

	//void fprintCBT(ofstream& fout);
	void fprintCBT_byLevel(ofstream& fout);



protected:
	void _printCBT_byLevel(ofstream& fout, int p, int level);
	int parentIndex(int index) { return index / 2; }
	int leftChildIndex(int index) { return index * 2; }
	int rightChildIndex(int index) { return (index * 2 + 1); }
	bool hasLeftChild(int index) { return ((index * 2) <= end); }  //�����ڽ� �ִ���
	bool hasRightChild(int index) { return ((index * 2 + 1) <= end); }  //������ �ڽ� �ִ���
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
void CompleteBinaryTree<T>::_printCBT_byLevel(ofstream& fout, int index, int level) //�������ڽ�->�׺θ��ڽ�->�����ڽ� �� ���
{
	int index_child;
	if (hasRightChild(index))  //������ �ڽ� ������
	{
		index_child = rightChildIndex(index);  //�������ڽ� �ε��� �޾ƿͼ�
		_printCBT_byLevel(fout, index_child, level + 1);  //������ �ڽ��� ���������� �� 
	}
	for (int i = 0; i < level; i++)
		fout << "    "; //�����Ǿ��ִ� level(����)��ŭ �鿩����
	this->t_array[index].fprint(fout);  //�� �׸� ���
	fout << endl;  //�ٹٲ�
	if (hasLeftChild(index))
	{
		index_child = leftChildIndex(index);  //���� �ڽ� ������ �����ڽ� �ε��� �޾ƿ�
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
	end++;  //end��ġ ������Ų��
	this->t_array[end] = elem;  ///�� ��ġ�� ������Ʈ �߰�
	return end;
}*/

template<typename T>
void CompleteBinaryTree<T>::removeCBTEnd()
{
	end--;
	this->num_elements--;
}

#endif