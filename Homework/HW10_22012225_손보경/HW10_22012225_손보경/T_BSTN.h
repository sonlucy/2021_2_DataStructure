#ifndef T_BSTN_H
#define T_BSTN_H
#include "T_Entry.h"

template<typename K, typename V>
class T_BSTN { // a node of the tree
public:
	T_BSTN() : entry(), pPr(NULL), pLc(NULL), pRc(NULL) { } // default constructor
	T_BSTN(T_Entry<K, V> e) : entry(e), pPr(NULL), pLc(NULL), pRc(NULL) { } // constructor

	K getKey() { return entry.getKey(); }
	V getValue() { return entry.getValue(); }

	T_Entry<K, V>& getEntry() { return entry; }
	void setEntry(T_Entry<K, V> e) { entry = e; }

	T_BSTN<K, V>* getpPr() { return pPr; }  //
	T_BSTN<K, V>* getpLc() { return pLc; }
	T_BSTN<K, V>* getpRc() { return pRc; }

	T_BSTN<K, V>** getppLc() { return &pLc; } //�����ڽ��� �������� �ּ� ��������
	T_BSTN<K, V>** getppRc() { return &pRc; } //rebalancing�Ҷ� ���

	void setpPr(T_BSTN<K, V>* pTN) { pPr = pTN; }
	void setpLc(T_BSTN<K, V>* pTN) { pLc = pTN; }
	void setpRc(T_BSTN<K, V>* pTN) { pRc = pTN; }

	T_Entry<K, V>& operator*() { return entry; }
private:
	T_Entry<K, V> entry; // element value
	T_BSTN<K, V>* pPr; // �θ�
	T_BSTN<K, V>* pLc; // ���� �ڽ�
	T_BSTN<K, V>* pRc; // ������ �ڽ�
};

#endif