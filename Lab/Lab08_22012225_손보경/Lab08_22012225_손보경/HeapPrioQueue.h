#pragma once 
#ifndef HEAP_PRIQ_QUEUE_H
#define HEAP_PRIQ_QUEUE_H
#include "CompleteBinaryTree.h"
#include <Windows.h>
#include <iostream>
using namespace std;
//#include "TA_Entry.h" ///////
//#include "T_Entry.h"  ///////

template<typename K, typename V>
class HeapPrioQueue : public CompleteBinaryTree<K, V>
{
public:
	HeapPrioQueue(int capa, string nm);
	~HeapPrioQueue();

	bool isEmpty() { return size() == 0; }
	bool isFull() { return size() == this->capacity; }
	int insert(T_Entry<K, V>& elem);

	T_Entry<K, V>* removeHeapMin(); //제일 우선순위가 높은거 찾아내서 삭제하기
	T_Entry<K, V>* getHeapMin();//우선순위가 높은거(root) 읽기


	void fprint(ofstream& fout);
	int size() { return this->end; }  
private:
};

template<typename K, typename V>
HeapPrioQueue<K, V>::HeapPrioQueue(int capa, string nm)
	:CompleteBinaryTree<K, V>(capa, nm)
{ }

template<typename K, typename V>
HeapPrioQueue<K, V>::~HeapPrioQueue()
{ }

template<typename K, typename V>
void HeapPrioQueue<K, V>::fprint(ofstream& fout)
{
	if (size() <= 0)  //비어있음
	{
		fout << "HeapPriorityQueue is Empty !!" << endl;
		return;
	}
	else
		CompleteBinaryTree<K, V>::fprintCBT(fout);
}

template<typename K, typename V>
int HeapPrioQueue<K, V>::insert(T_Entry<K, V>& elem)
{
	int index, parent_index;
	T_Entry<K, V> temp;
	if (isFull())  //가득차있으면
	{
		cout << this->getName() << " is Full !!" << endl;
		return size();
	}
	index = this->add_at_end(elem);  //맨마지막 항목 추가

	/* up-heap bubbling */
	while (index != CBT_ROOT)  //인덱스가 루트까지 도착하면 업힙버블링 끝
	{
		parent_index = this->parentIndex(index); 
		if (this->t_array[index].getKey() >= this->t_array[parent_index].getKey())
			break;
		else
		{
			temp = this->t_array[index];
			this->t_array[index] = this->t_array[parent_index];
			this->t_array[parent_index] = temp;

			index = parent_index; //힙오더가 만족할때까지 업힙버블링(while문)이 계속 실행되기위해 부모노드로 설정
		}
	}
	return size();
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::getHeapMin()
{
	T_Entry<K, V>* pMinElem;
	if (size() <= 0)
	{
		return NULL;
	}
	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>;  //T_Entry를 담아낼수잇는 동적메모리생성, pMinElem가 T_Entry항목 담을 수 잇는 새로운 메모리블록 가리키게됨
	*pMinElem = this->getRootElement();   //현재 root element값 읽어 대입
	return pMinElem; //그 주소 반환
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::removeHeapMin()
{
	int index_p, index_c, index_rc;
	T_Entry<K, V>* pMinElem;
	T_Entry<K, V> temp, t_p, t_c;
	int HPQ_size = size(); //size()를 이용해 사이즈 읽어오기
	if (HPQ_size <= 0)   //비어있는 상태
	{
		return NULL;
	}
	//else
	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>;
	*pMinElem = this->getRootElement();
	if (HPQ_size == 1)  //root노드 하나밖에 없는 상황
	{
		this->removeCBTEnd();
	}
	else  //2개 이상 남아있음
	{
		index_p = CBT_ROOT;
		this->t_array[CBT_ROOT] = this->t_array[this->end];  //end위치를 root위치로 옮김
		this->end--;

		/* down-heap bubbling */
		while (this->hasLeftChild(index_p))  //왼쪽자식 없으면 더이상 밑에 자식 없기때문에 힙오더대상 없으니까
		{
			index_c = this->leftChildIndex(index_p);
			index_rc = this->rightChildIndex(index_p);
			if (this->hasRightChild(index_p) && (this->t_array[index_c] > this->t_array[index_rc])) //이 경우 오른쪽자식이 우선순위 더 높기때문에 오른쪽 자식과 부모자식을 비교해야함.
				index_c = index_rc;  //우선순위가 더 높은쪽이 index_c가 되도록.
			t_p = this->t_array[index_p];
			t_c = this->t_array[index_c];
			if (t_p > t_c) //부모가 더 크면 자리바꿈 필요
			{
				//swap(index_u, index_c);
				temp = this->t_array[index_p];
				this->t_array[index_p] = this->t_array[index_c];
				this->t_array[index_c] = temp;

				index_p = index_c; //while반복 위해
			}
			else
				break;
		} // end while
	}
	return pMinElem;
}
#endif

