#pragma once
#ifndef HASH_DICT_H
#define HASH_DICT_H
#include "HashMap.h"
#define DEFAULT_HASH_SIZE 101

template <typename K, typename V>
class HashDict : public HashMap<K, V>  //�ؽ��� ��ӹޱ�
{
public: // public functions
	typedef typename HashMap<K, V>::Iterator Iterator;  //�ؽ����� iterator
	typedef typename HashMap<K, V>::Entry Entry;   //�ؽø��� entry

	// Range class declaration
	class Range  //bucket�� entry���� ���� ���� ����������///////////////////////////////////////////////////////////
	{ // an iterator range
	private:
		Iterator _begin; // front of range
		Iterator _end; // end of range
	public:
		Range() {} // default constructor
		Range(const Iterator& b, const Iterator& e) // constructor
			: _begin(b), _end(e) { }
		Iterator& begin() { return _begin; } // get beginning
		Iterator& end() { return _end; } // get end
	};

public: // public functions
	HashDict(int capacity = DEFAULT_HASH_SIZE); // constructor
	Range findAll(const K& k); // ���޹��� key�� ��� entry�� ã�� (range��)
	Iterator insert(const K& k, const V& v); // insert pair (k,v). �ؽ��ʿ����� ������ Ű�� ������ �����µ�
	                                                               //��� ������ Ű�� �־ �� �ڿ� ���ο� �׸� ����
};

template <typename K, typename V> // constructor
HashDict<K, V>::HashDict(int capacity) : HashMap<K, V>(capacity) { }

template <typename K, typename V> // insert pair (k,v)
typename HashDict<K, V>::Iterator
HashDict<K, V>::insert(const K& k, const V& v) 
{
	Iterator p = this->_find(k); // ���޹��� key ��ġ ã��
	Iterator q = this->_insert(p, Entry(k, v)); //�߰�.!!!  ///////////////////

	return q; // return its position
}

template <typename K, typename V> // find all entries with k
typename HashDict<K, V>::Range
HashDict<K, V>::findAll(const K& k) //���޹��� k�� ��� entry ã��
{
	Iterator b = this->_find(k); // ���޹��� k ��ġ ã��
	Iterator p = b;
	while (p != this->end() && (*p).getKey() == k) //���޹��� k�� ���� key�� entry�ϵ���.
	{ // find next entry with different key or end of bucket array
		++p;   
	}//���޹��� k�� �ٸ� key�̸� while�� ����Ǹ� p��ġ�� ��ȯ�� Range��
	return Range(b, p); // return range of positions
}
#endif
