#pragma once
/** HashMap.h */
#ifndef HASHMAP_H 
#define HASHMAP_H
#include <list>
#include <vector>
#include "T_Entry.h"
#include "CyclicShiftHashCode.h"  ///////////
#include "MyVoca.h"/////////////

using namespace std;

template <typename K, typename V>
class HashMap {

public: // public types
	typedef T_Entry<const K, V> Entry; //////////////////////////// a (key,value) pair
	class Iterator;

public: // public functions
	HashMap(int capacity = 101); // constructor

	int size() const {return num_entry;} // number of entries
	bool empty() const { return (num_entry == 0); } // is the map empty?

	Iterator find(const K& k); // find entry with key k
	Iterator insert(const K& k, const V& v); // insert/replace (k,v)
	void erase(const K& k); // remove entry with key k
	void erase(const Iterator& p); // erase entry at p
	Iterator begin(); // iterator to first entry
	Iterator end(); // iterator to end entry

protected: // protected types
	typedef std::list<Entry> Bucket; ////////////////////////// a bucket of entries
	typedef std::vector<Bucket> BktArray; ////////////////////////////// a bucket array

	// HashMap utilities here
	Iterator _find(const K& k); // find utility
	Iterator _insert(const Iterator& p, const Entry& e); // insert utility
	void _erase(const Iterator& p); // remove utility

	typedef typename BktArray::iterator BItor; //////////////////////// bucket iterator
	typedef typename Bucket::iterator EItor; //////////////////////// entry iterator

	static void _next(Iterator& p) // bucket의 다음 entry
	{
		++p.ent;
	}
	static bool _endOfBkt(const Iterator& p) // bucket의 end인지
	{
		return p.ent == p.bkt->end();
	}
private:
	int num_entry; // number of entries
	BktArray B; // bucket array

public: // public types
////////////////////////////////////////////////////////////////////////////// Iterator class declaration 
	class Iterator 
	{                                  // an iterator (& position)
	protected: 
		EItor ent; // bucket 안의 entry에 대한 접근지정자 (list)
		BItor bkt; // which bucket ///////////// bucket array의 각 버킷에 대한 접근지정자(vector)
		const BktArray* ba; //bucket array에 대한 포인터
	public:
		Iterator() {} // default constructor
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor()): ent(q), bkt(b), ba(&a) { }
		V getValue() { Entry& e = *ent; return e.getValue(); }

		Entry& operator*() const; // get entry V getValue() { Entry& e = *ent; return e.value(); } 
		bool operator==(const Iterator& p) const; // are iterators equal? 
		bool operator!=(const Iterator& p) const; // are iterators different ? 
		Iterator& operator++(); // advance to next entry 
		Iterator& advanceEItor() 
		{
			++ent;
			return *this;
		}
		friend class HashMap; // give HashMap access
	};

	void fprintBucketSizes(ostream& fout);  //////모든 bucket의 entry를 출력
	void fprintBucket(ostream& fout, BItor bkt);   ///////bucket들의 최대최소평균의 entry를 출력

};
#endif

/*
#include "Entry.h"
#include <iostream>
#include "HashMap.h"*/

template <typename K, typename V> // constructor
HashMap<K, V>::HashMap(int capacity) : num_entry(0), B(capacity) { }

template <typename K, typename V> // iterator to front
typename HashMap<K, V>::Iterator HashMap<K, V>::begin()
{
	if (empty()) return end(); // emtpty이면 return end
	BItor bkt = B.begin(); // else이면 entry 서치해서 bucket array에 대한 접근지정자를 bucket array의 시작위치로.
	
	while (bkt->empty()) ++bkt; // 비지않은 bucket 발견할때까지

	return Iterator(B, bkt, bkt->begin()); // B:버킷테이블, bkt:버킷테이블 안의 버킷, bkt->begin(): 비어있지 않은 버킷의 맨 처음 항목
}

template <typename K, typename V> // iterator to end
typename HashMap<K, V>::Iterator HashMap<K, V>::end()
{
	return Iterator(B, B.end());
}

template <typename K, typename V> // get entry
typename HashMap<K, V>::Entry& HashMap<K, V>::Iterator::operator*() const
{
	return *ent;  //접근지정자 ent가 가리키는 곳(ent: bucket 안의 entry에 대한 접근지정자)
}

template <typename K, typename V> // are iterators equal?
bool HashMap<K, V>::Iterator::operator==(const Iterator& p) const
{

	///////////////////////////////////////////////////////////////////////
	if (ba != p.ba || bkt != p.bkt) //bucket array 다르거나 bucket array접근지정자 다르면 
		return false; // ba or bkt differ?
	else if (bkt == ba->end()) //둘다 end
		return true; // both at the end?
	else //bucket 안의 같은 entry를 가리킬때
		return (ent == p.ent); // else use entry to decide
}

template <typename K, typename V> // are iterators equal?
bool HashMap<K, V>::Iterator::operator!=(const Iterator& p) const
{
	if (ba != p.ba || bkt != p.bkt) 
		return true; // ba or bkt differ?
	else if (bkt == ba->end())
		return false; // both at the end?
	else 
		return (ent != p.ent); // else use entry to decide
}




template <typename K, typename V> // advance to next entry
typename HashMap<K, V>::Iterator& HashMap<K, V>::Iterator::operator++()
{
	++ent; // next entry in bucket
	if (_endOfBkt(*this)) { // bucket의 end이면
		++bkt; // 다음 bucket으로
		while (bkt != ba->end() && bkt->empty()) // 비지않은 bucket 발견할때까지
			++bkt;
		if (bkt == ba->end()) //bucket array의 end이면
			return *this; 
		ent = bkt->begin(); // entry에 대한 접근지정자가 비어있지않는 첫 entry가리키도록
	}
	return *this; // return self
}

template <typename K, typename V> // find utility
typename HashMap<K, V>::Iterator HashMap<K, V>::_find(const K& k)  //////////////////////////////////////////////////////////
{
	CyclicShiftHashCode hash;
	//B는 bucketarray 
	int i = hash(k) % B.size(); // CyclicShiftHashCode()이용해서 hash value i 계산. hash map 수로 나눔      //i는 hash value, hash(k)는 해시코드.
	BItor bkt = B.begin() + i; // the i-th bucket (전달받은 key가 있는 bucket 구하기)            //몇번째 버킷을 찾아갈것인지.
	Iterator p(B, bkt, bkt->begin()); // start of i-th bucket
	while (!_endOfBkt(p) && (*p).getKey() != k) // bucket에서 찾아야할 key 찾기
		++p.ent;

	return p; // return final position . while문이 종료되면 종료된 해당 위치에서 p가 반환됨
}

template <typename K, typename V> // find key
typename HashMap<K, V>::Iterator HashMap<K, V>::find(const K& k)
{
	Iterator p = _find(k); // look for k

	if (_endOfBkt(p)) // key값 못 찾으면
		return end(); // return end iterator
	else
		return p; // return its position
}

template <typename K, typename V> // insert utility
typename HashMap<K, V>::Iterator
HashMap<K, V>::_insert(const Iterator& p, const Entry& e) 
{
	EItor ins = p.bkt->insert(p.ent, e); // insert before p using insert() of list<Entry>
	num_entry++; // one more entry

	return Iterator(B, p.bkt, ins); // return this position
}

template <typename K, typename V> // insert/replace (v,k)
typename HashMap<K, V>::Iterator
HashMap<K, V>::insert(const K& k, const V& v)
{
	Iterator p = _find(k); // 전달받은 key값 찾고
	
	if (_endOfBkt(p)) { // 못 찾으면
		return _insert(p, Entry(k, v)); // insert at end of bucket
	}
	else //찾으면
	{ 
		p.ent->setValue(v); // 전달받은 value로 값바꿈
		return p; // return this position
	}
}

template <typename K, typename V> // remove utility
void HashMap<K, V>::_erase(const Iterator& p)
{
	p.bkt->erase(p.ent); // bucket으로부터 entry 삭제
	num_entry--; // one fewer entry
}

template <typename K, typename V> // remove entry at p
void HashMap<K, V>::erase(const Iterator& p)
{
	_erase(p);
}

template <typename K, typename V> // remove entry with key k
void HashMap<K, V>::erase(const K& k)
{
	Iterator p = _find(k); // find k
	if (_endOfBkt(p)) // not found?
		//throw NonexistentElement("Erase of nonexistent"); // ...error
		cout << "Erase of nonexistent" << endl;
	_erase(p); // remove it
}


template <typename K, typename V>
void HashMap<K, V>::fprintBucket(ostream& fout, BItor bkt)
{
	Iterator p(B, bkt, bkt->begin());
	MyVoca* pVoca;
	while (p.ent != bkt->end())
	{
		pVoca = p.getValue();
		fout << *pVoca << endl;
		++p.ent;
	}
}

template <typename K, typename V>
void HashMap<K, V>::fprintBucketSizes(ostream& fout)
{
	int bkt_size;
	int max_ent, min_ent, total;
	int num_bkts, max_bkt = 0;
	double avg = 0.0;
	max_ent = min_ent = B[0].size();
	total = 0;
	num_bkts = B.size();
	for (int bkt = 0; bkt < num_bkts; bkt++) //bucket array 크기동안
	{
		bkt_size = B[bkt].size();
		fout << "Bucket[" << setw(3) << bkt << "] : " << bkt_size << " entries"
			<< endl;

		if (bkt_size > max_ent)
		{
			max_ent = bkt_size;
			max_bkt = bkt;
		}
		if (bkt_size < min_ent)
			min_ent = bkt_size;
		total += bkt_size;
	}
	avg = total / num_bkts;
	fout.precision(2);
	fout << "\nMax_ent(" << setw(2) << max_ent << "), min_ent(" << setw(2) 
		<< min_ent << "), avg (" << setw(5) << avg << ")" << endl;
	fout << "Bucket with maximum (" << max_ent << ") entries : " << endl;
	BItor bkt = B.begin() + max_bkt;// the ith bucket
	fprintBucket(fout, bkt); //가장 많은 엔트리 버킷 출력
}
