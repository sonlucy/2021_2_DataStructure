#pragma once 
#ifndef T_Entry_H
#define T_Entry_H
//#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;


template<typename K, typename V>
class T_Entry
{
	friend ostream& operator<<(ostream& fout, T_Entry<K, V>& entry)
	{
		fout << "[" << setw(2) << entry.getKey() << ", " << (entry.getValue()) << "]";  ///////////////////
		return fout;
	}

public:
	T_Entry(K key, V value) { _key = key; _value = value; }
	T_Entry() { _key = 999; } // default constructor
	~T_Entry() {}

	void setKey(const K& key) { _key = key; }
	void setValue(const V& value) { _value = value; }
	K getKey() const { return _key; }
	V getValue() const { return _value; }

	bool operator>(const T_Entry& right) { return (_key > right.getKey()); }
	bool operator>=(const T_Entry& right) { return (_key >= right.getKey()); }
	bool operator<(const T_Entry& right) { return (_key < right.getKey()); }
	bool operator<=(const T_Entry& right) { return (_key <= right.getKey()); }
	bool operator==(const T_Entry& right) { return ((_key == right.getKey()) && (_value == right.getValue())); }
	T_Entry& operator=(const T_Entry& right);

	void fprint(ostream& fout);

private:
	K _key;
	V _value;
};


template<typename K, typename V>
T_Entry<K, V>& T_Entry<K, V>::operator=(const T_Entry<K, V>& right)
{
	_key = right._key;
	_value = right._value;
	return *this;
}

template<typename K, typename V>
void T_Entry<K, V>::fprint(ostream& fout)
{
	fout << "[Key:" << setw(2) << _key << ", " << setw(10) << *_value << "]";
}
#endif
