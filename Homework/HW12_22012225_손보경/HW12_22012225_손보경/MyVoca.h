#ifndef MY_VOCA_H 
#define MY_VOCA_H
#include <iostream>
#include <string>
#include <list>
using namespace std;
enum Word_Type { NOUN, VERB, ADJ, ADV, PREPOS }; // noun, verb, adjective, adverbs, preposition
typedef list<string> List_Str;
typedef list<string>::iterator Lst_Str_Itr;  //list�� iteratoer(����������)

class MyVoca
{
	friend ostream& operator<<(ostream& fout, MyVoca& mv)
	{
		const string wd_ty[] = { "n", "v", "adj", "adv", "prepos" };
		list<string>::iterator itr; //list�� iterator(����������)
		fout << mv.keyWord << "(" << wd_ty[mv.type] << "):" << endl;
		fout << " - thesaurus(";
		for (itr = mv.thesaurus.begin(); itr != mv.thesaurus.end(); ++itr)
		{
			fout << *itr << ", ";
		}
		fout << ")" << endl;
		fout << " - example usage(";
		for (itr = mv.usages.begin(); itr != mv.usages.end(); ++itr)
		{
			fout << *itr << " ";
		}
		fout << ")";
		return fout;
	}
public:
	MyVoca(string kw, Word_Type wt, List_Str thes, List_Str ex_usg)
		:keyWord(kw), type(wt), thesaurus(thes), usages(ex_usg) {}
	MyVoca() {} // default constructor
	string getKeyWord() { return keyWord; }

private:
	string keyWord; // �ܾ�. entry word (also key)
	Word_Type type;  //�ܾ��� ǰ��
	List_Str thesaurus; // ���Ǿ�
	List_Str usages;  //����
};
#endif