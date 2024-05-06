
#ifndef Complete_Binary_Tree_H
#define Complete_Binary_Tree_H
#include "TA_Entry.h"
//#include "T_Entry.h"
#define CBT_ROOT 1

template<typename K, typename V>
class CompleteBinaryTree : public TA_Entry<K, V>
{
public:

	CompleteBinaryTree(int capa, string nm);

	int add_at_end(T_Entry<K, V>& elem);  ///완전이진트리 끝 노드에 이벤트 더하기
	T_Entry<K, V>& getEndElement() { return this->t_array[end]; }  //end노드 읽어오기
	T_Entry<K, V>& getRootElement() { return this->t_array[CBT_ROOT]; }   //root노드 읽어오기
	int getEndIndex() { return end; }
	void removeCBTEnd();  //end노드 삭제

	void fprintCBT(ostream& fout);
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


template<typename K, typename V>
CompleteBinaryTree<K, V>::CompleteBinaryTree(int capa, string nm)
	:TA_Entry<K, V>(capa, nm)  //
{
	end = 0; // reset to empty
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::fprintCBT(ostream& fout)
{
	if (end <= 0)
	{
		fout << this->getName() << " is empty now !!" << endl;
		return;
	}
	int count = 0;
	for (int i = 1; i <= end; i++)
	{
		///////fout << setw(3) << this->t_array[i] << endl;  ///////this
		//if ((((count + 1) % 10) == 0) && (i != end))
		//fout << endl;
		fout << "[Key:" << this->t_array[i].getKey() << "]";
		if ((count + 1) % 5 == 0)
			fout << endl;
		count++;
	}
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::_printCBT_byLevel(ofstream& fout, int index, int level) //오른쪽자식->그부모자식->왼쪽자식 순 출력
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
template<typename K, typename V>
void CompleteBinaryTree<K, V>::fprintCBT_byLevel(ofstream& fout)
{
	if (end <= 0)
	{
		fout << "CBT is EMPTY now !!" << endl;
		return;
	}
	_printCBT_byLevel(fout, CBT_ROOT, 0);
}

template<typename K, typename V>
int CompleteBinaryTree<K, V>::add_at_end(T_Entry<K, V>& elem)
{
	if (end >= this->capacity)
	{
		cout << this->getName() << " is FULL now !!" << endl;
		return end;
	}
	end++;  //end위치 증가시킨후
	this->t_array[end] = elem;  ///그 위치에 엘리먼트 추가
	return end;
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::removeCBTEnd()
{
	end--;
	this->num_elements--;
}

#endif