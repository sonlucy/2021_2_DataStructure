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

	static void _next(Iterator& p) // bucket�� ���� entry
	{
		++p.ent;
	}
	static bool _endOfBkt(const Iterator& p) // bucket�� end����
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
		EItor ent; // bucket ���� entry�� ���� ���������� (list)
		BItor bkt; // which bucket ///////////// bucket array�� �� ��Ŷ�� ���� ����������(vector)
		const BktArray* ba; //bucket array�� ���� ������
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

	void fprintBucketSizes(ostream& fout);  //////��� bucket�� entry�� ���
	void fprintBucket(ostream& fout, BItor bkt);   ///////bucket���� �ִ��ּ������ entry�� ���

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
	if (empty()) return end(); // emtpty�̸� return end
	BItor bkt = B.begin(); // else�̸� entry ��ġ�ؼ� bucket array�� ���� ���������ڸ� bucket array�� ������ġ��.
	
	while (bkt->empty()) ++bkt; // �������� bucket �߰��Ҷ�����

	return Iterator(B, bkt, bkt->begin()); // B:��Ŷ���̺�, bkt:��Ŷ���̺� ���� ��Ŷ, bkt->begin(): ������� ���� ��Ŷ�� �� ó�� �׸�
}

template <typename K, typename V> // iterator to end
typename HashMap<K, V>::Iterator HashMap<K, V>::end()
{
	return Iterator(B, B.end());
}

template <typename K, typename V> // get entry
typename HashMap<K, V>::Entry& HashMap<K, V>::Iterator::operator*() const
{
	return *ent;  //���������� ent�� ����Ű�� ��(ent: bucket ���� entry�� ���� ����������)
}

template <typename K, typename V> // are iterators equal?
bool HashMap<K, V>::Iterator::operator==(const Iterator& p) const
{

	///////////////////////////////////////////////////////////////////////
	if (ba != p.ba || bkt != p.bkt) //bucket array �ٸ��ų� bucket array���������� �ٸ��� 
		return false; // ba or bkt differ?
	else if (bkt == ba->end()) //�Ѵ� end
		return true; // both at the end?
	else //bucket ���� ���� entry�� ����ų��
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
	if (_endOfBkt(*this)) { // bucket�� end�̸�
		++bkt; // ���� bucket����
		while (bkt != ba->end() && bkt->empty()) // �������� bucket �߰��Ҷ�����
			++bkt;
		if (bkt == ba->end()) //bucket array�� end�̸�
			return *this; 
		ent = bkt->begin(); // entry�� ���� ���������ڰ� ��������ʴ� ù entry����Ű����
	}
	return *this; // return self
}

template <typename K, typename V> // find utility
typename HashMap<K, V>::Iterator HashMap<K, V>::_find(const K& k)  //////////////////////////////////////////////////////////
{
	CyclicShiftHashCode hash;
	//B�� bucketarray 
	int i = hash(k) % B.size(); // CyclicShiftHashCode()�̿��ؼ� hash value i ���. hash map ���� ����      //i�� hash value, hash(k)�� �ؽ��ڵ�.
	BItor bkt = B.begin() + i; // the i-th bucket (���޹��� key�� �ִ� bucket ���ϱ�)            //���° ��Ŷ�� ã�ư�������.
	Iterator p(B, bkt, bkt->begin()); // start of i-th bucket
	while (!_endOfBkt(p) && (*p).getKey() != k) // bucket���� ã�ƾ��� key ã��
		++p.ent;

	return p; // return final position . while���� ����Ǹ� ����� �ش� ��ġ���� p�� ��ȯ��
}

template <typename K, typename V> // find key
typename HashMap<K, V>::Iterator HashMap<K, V>::find(const K& k)
{
	Iterator p = _find(k); // look for k

	if (_endOfBkt(p)) // key�� �� ã����
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
	Iterator p = _find(k); // ���޹��� key�� ã��
	
	if (_endOfBkt(p)) { // �� ã����
		return _insert(p, Entry(k, v)); // insert at end of bucket
	}
	else //ã����
	{ 
		p.ent->setValue(v); // ���޹��� value�� ���ٲ�
		return p; // return this position
	}
}

template <typename K, typename V> // remove utility
void HashMap<K, V>::_erase(const Iterator& p)
{
	p.bkt->erase(p.ent); // bucket���κ��� entry ����
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
	for (int bkt = 0; bkt < num_bkts; bkt++) //bucket array ũ�⵿��
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
	fprintBucket(fout, bkt); //���� ���� ��Ʈ�� ��Ŷ ���
}
