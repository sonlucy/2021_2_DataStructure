#ifndef TRIE_NODE_H
#define TRIE_NODE_H
#include <iostream>
#include <string>
#include <list>
#define VALUE_INTERNAL_NODE NULL
using namespace std;
typedef list<string> STL_list; //

template <typename E>
class TrieNode
{
public:
	TrieNode() {} // default constructor
	TrieNode(char k, E v) : key(k), value(v)
	{
		prev = next = parent = child = NULL;
	}

	void setKey(char k) { key = k; }
	void setValue(E v) { value = v; }
	char getKey() { return key; }
	E getValue() { return value; }

	void setNext(TrieNode<E>* nxt) { next = nxt; }
	void setPrev(TrieNode<E>* pv) { prev = pv; } 
	void setParent(TrieNode<E>* pr) { parent = pr; }
	void setChild(TrieNode<E>* chld) { child = chld; }

	//포인터의 값들을 읽어 반환
	TrieNode<E>* getPrev() { return prev; }
	TrieNode<E>* getNext() { return next; }
	TrieNode<E>* getParent() { return parent; }
	TrieNode<E>* getChild() { return child; }

	void _fprint(ostream& fout, TrieNode<E>* pTN, int indent); //지정된 fout으로 해당되는 TrieNode의 내용을 출력하도록.

private:
	char key;  
	E value;

	TrieNode<E>* prev;
	TrieNode<E>* next;
	TrieNode<E>* parent;
	TrieNode<E>* child;

};

template<typename E>
void TrieNode<E>::_fprint(ostream& fout, TrieNode<E>* pTN, int indent)
{
	if (pTN == NULL)
	{
		fout << endl;
		return;
	}
	else
	{
		fout << pTN->key;  //해당하는 TrieNode의 값을 출력
		_fprint(fout, pTN->child, indent + 1);  //그 TireNode의 child를 방문해서 출력하도록.
		                                         //이때 indent 하나 추가해서 들여쓰기 되도록.
		if (pTN->next == NULL)
			return;
		for (int i = 0; i < indent; i++)
			fout << " ";  //해당하는 indent만큼 들여쓰기
		_fprint(fout, pTN->next, indent);  //그 TrieNode의 next부터 또 재귀함수 호출
	}
}

#endif