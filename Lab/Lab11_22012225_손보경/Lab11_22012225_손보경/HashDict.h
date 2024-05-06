#pragma once
#ifndef HASH_DICT_H
#define HASH_DICT_H
#include "HashMap.h"
#define DEFAULT_HASH_SIZE 101

template <typename K, typename V>
class HashDict : public HashMap<K, V>  //해쉬맵 상속받기
{
public: // public functions
	typedef typename HashMap<K, V>::Iterator Iterator;  //해쉬맵의 iterator
	typedef typename HashMap<K, V>::Entry Entry;   //해시맵의 entry

	// Range class declaration
	class Range  //bucket의 entry들의 범위 관련 접근지정자///////////////////////////////////////////////////////////
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
	Range findAll(const K& k); // 전달받은 key의 모든 entry를 찾기 (range로)
	Iterator insert(const K& k, const V& v); // insert pair (k,v). 해쉬맵에서는 동일한 키가 있으면 덮어썼는데
	                                                               //얘는 동일한 키가 있어도 그 뒤에 새로운 항목 넣음
};

template <typename K, typename V> // constructor
HashDict<K, V>::HashDict(int capacity) : HashMap<K, V>(capacity) { }

template <typename K, typename V> // insert pair (k,v)
typename HashDict<K, V>::Iterator
HashDict<K, V>::insert(const K& k, const V& v) 
{
	Iterator p = this->_find(k); // 전달받은 key 위치 찾고
	Iterator q = this->_insert(p, Entry(k, v)); //추가.!!!  ///////////////////

	return q; // return its position
}

template <typename K, typename V> // find all entries with k
typename HashDict<K, V>::Range
HashDict<K, V>::findAll(const K& k) //전달받은 k의 모든 entry 찾기
{
	Iterator b = this->_find(k); // 전달받은 k 위치 찾고
	Iterator p = b;
	while (p != this->end() && (*p).getKey() == k) //전달받은 k와 같은 key인 entry일동안.
	{ // find next entry with different key or end of bucket array
		++p;   
	}//전달받은 k와 다른 key이면 while문 종료되며 p위치를 반환해 Range로
	return Range(b, p); // return range of positions
}
#endif
