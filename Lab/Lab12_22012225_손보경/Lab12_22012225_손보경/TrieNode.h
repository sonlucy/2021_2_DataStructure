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

	//�������� ������ �о� ��ȯ
	TrieNode<E>* getPrev() { return prev; }
	TrieNode<E>* getNext() { return next; }
	TrieNode<E>* getParent() { return parent; }
	TrieNode<E>* getChild() { return child; }

	void _fprint(ostream& fout, TrieNode<E>* pTN, int indent); //������ fout���� �ش�Ǵ� TrieNode�� ������ ����ϵ���.

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
		fout << pTN->key;  //�ش��ϴ� TrieNode�� ���� ���
		_fprint(fout, pTN->child, indent + 1);  //�� TireNode�� child�� �湮�ؼ� ����ϵ���.
		                                         //�̶� indent �ϳ� �߰��ؼ� �鿩���� �ǵ���.
		if (pTN->next == NULL)
			return;
		for (int i = 0; i < indent; i++)
			fout << " ";  //�ش��ϴ� indent��ŭ �鿩����
		_fprint(fout, pTN->next, indent);  //�� TrieNode�� next���� �� ����Լ� ȣ��
	}
}

#endif