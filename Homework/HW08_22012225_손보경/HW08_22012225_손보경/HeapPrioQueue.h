#pragma once
#pragma once 
#ifndef HEAP_PRIQ_QUEUE_H
#define HEAP_PRIQ_QUEUE_H
#include "CompleteBinaryTree.h"
#include <Windows.h>
#include <iostream>
using namespace std;
//#include "TA_Entry.h" ///////
//#include "T_Entry.h"  ///////

template<typename T>
class HeapPrioQueue : public CompleteBinaryTree<T>
{
public:
	HeapPrioQueue(int capa, string nm);
	~HeapPrioQueue();

	bool isEmpty() { return size() == 0; }
	bool isFull() { return size() == this->capacity; }
	int insert(T& elem);

	T* removeHeapMin(); //���� �켱������ ������ ã�Ƴ��� �����ϱ�
	T* getHeapMin();//�켱������ ������(root) �б�


	void fprint(ofstream& fout);
	int size() { return this->end; }
private:
};

template<typename T>
HeapPrioQueue<T>::HeapPrioQueue(int capa, string nm)
	:CompleteBinaryTree<T>(capa, nm)
{ }

template<typename T>
HeapPrioQueue<T>::~HeapPrioQueue()
{ }

template<typename T>
void HeapPrioQueue<T>::fprint(ofstream& fout)
{
	if (size() <= 0)  //�������
	{
		fout << "HeapPriorityQueue is Empty !!" << endl;
		return;
	}
	else
		CompleteBinaryTree<T>::fprintCBT(fout);
}

template<typename T>
int HeapPrioQueue<T>::insert(T& elem)
{
	int index, parent_index;
	T_Entry<T> temp;
	if (isFull())  //������������
	{
		cout << this->getName() << " is Full !!" << endl;
		return size();
	}
	index = this->add_at_end(elem);  //�Ǹ����� �׸� �߰�

	/* up-heap bubbling */
	while (index != CBT_ROOT)  //�ε����� ��Ʈ���� �����ϸ� �������� ��
	{
		parent_index = this->parentIndex(index);
		if (this->t_array[index].getKey() >= this->t_array[parent_index].getKey())
			break;
		else
		{
			temp = this->t_array[index];
			this->t_array[index] = this->t_array[parent_index];
			this->t_array[parent_index] = temp;

			index = parent_index; //�������� �����Ҷ����� ��������(while��)�� ��� ����Ǳ����� �θ���� ����
		}
	}
	return size();
}

template<typename T>
T* HeapPrioQueue<T>::getHeapMin()
{
	T* pMinElem;
	if (size() <= 0)
	{
		return NULL;
	}
	pMinElem = (T_Entry<T>*) new T_Entry<T>;  //T_Entry�� ��Ƴ����մ� �����޸𸮻���, pMinElem�� T_Entry�׸� ���� �� �մ� ���ο� �޸𸮺�� ����Ű�Ե�
	*pMinElem = this->getRootElement();   //���� root element�� �о� ����
	return pMinElem; //�� �ּ� ��ȯ
}

template<typename T>
T* HeapPrioQueue<T>::removeHeapMin()
{
	int index_p, index_c, index_rc;
	T* pMinElem;
	T temp, t_p, t_c;
	int HPQ_size = size(); //size()�� �̿��� ������ �о����
	if (HPQ_size <= 0)   //����ִ� ����
	{
		return NULL;
	}
	//else
	pMinElem = (T*) new T_Entry<T>;   ///////////////////////
	*pMinElem = this->getRootElement();
	if (HPQ_size == 1)  //root��� �ϳ��ۿ� ���� ��Ȳ
	{
		this->removeCBTEnd();
	}
	else  //2�� �̻� ��������
	{
		index_p = CBT_ROOT;
		this->t_array[CBT_ROOT] = this->t_array[this->end];  //end��ġ�� root��ġ�� �ű�
		this->end--;

		/* down-heap bubbling */
		while (this->hasLeftChild(index_p))  //�����ڽ� ������ ���̻� �ؿ� �ڽ� ���⶧���� ��������� �����ϱ�
		{
			index_c = this->leftChildIndex(index_p);
			index_rc = this->rightChildIndex(index_p);
			if (this->hasRightChild(index_p) && (this->t_array[index_c] > this->t_array[index_rc])) //�� ��� �������ڽ��� �켱���� �� ���⶧���� ������ �ڽİ� �θ��ڽ��� ���ؾ���.
				index_c = index_rc;  //�켱������ �� �������� index_c�� �ǵ���.
			t_p = this->t_array[index_p];
			t_c = this->t_array[index_c];
			if (t_p > t_c) //�θ� �� ũ�� �ڸ��ٲ� �ʿ�
			{
				//swap(index_u, index_c);
				temp = this->t_array[index_p];
				this->t_array[index_p] = this->t_array[index_c];
				this->t_array[index_c] = temp;

				index_p = index_c; //while�ݺ� ����
			}
			else
				break;
		} // end while
	}
	return pMinElem;
}
#endif

