/*
* Lab11
* CyclicShiftHashCode, Hash, SkipList
* 
* 정보통신공학과 22012225 손보경
* 2021-11-19
*/
#include <iostream>
#include <fstream>
#include <string>
#include "HashMap.h"
#include "HashDict.h"  /////////////
#include "CyclicShiftHashCode.h"
#include "T_Entry.h"
#include "MyVoca.h"
#include "MyVocaList.h"
//#include "SkipList.h"

void main()
{
	ofstream fout;
	MyVoca* pVoca, voca;
	List_Str thesaurus;
	List_Str usages;
	int word_count;
	MyVoca mv;
	string keyWord;
	HashDict<string, MyVoca*> myVocaDict;
	HashDict<string, MyVoca*>::Iterator itr;
	HashDict<string, MyVoca*>::Range range;
	T_Entry<string, MyVoca*> vocaEntry;

	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open output.txt !!" << endl;
		exit;
	}
	fout << "Inserting My Vocabularies to myVocaDict . . . " << endl;
	word_count = 0;
	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++)
	{
		pVoca = &myToeicVocaList[i];
		keyWord = myToeicVocaList[i].getKeyWord();
		myVocaDict.insert(keyWord, pVoca);
	}
	//cout << endl;
	fout << "Total " << myVocaDict.size() << " words in my Voca_Dictionary .." << endl;
	// check all vocabularies in the hash_dictionary
	for (itr = myVocaDict.begin(); itr != myVocaDict.end(); ++itr)
	{
		pVoca = itr.getValue();
		fout << *pVoca << endl;
	}
	fout << endl;
	//string testWord = "mean";
	string testWord = "offer";
	range = myVocaDict.findAll(testWord);    //해당 단어 찾기/////////////
	fout << "Thesaurus of [" << testWord << "]: \n";
	for (itr = range.begin(); itr != range.end(); ++itr)
	{
		pVoca = itr.getValue();
		fout << *pVoca << endl;
	}
	fout << endl;

	myVocaDict.fprintBucketSizes(fout);


/*
	//////////////////////////////////////////////////
	fout << endl << "Skip List" << endl;
	SkipList<string, MyVoca*> myVocaSkipList;
	typedef SkipList<string, MyVoca*>::Position Pos_voca;
	Pos_voca posVoca;
	MyVoca* p_Voca;
	string keyWord;
	string deleteList[] = {"mean", "foster" };
	//fout<<" Inserting planet to"

	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++)
	{
		p_Voca = &myToeicVocaList[i];
		keyWord = myToeicVocaList[i].getKeyWord();
		//myVocaDict.insert(keyWord, pVoca);
		myVocaSkipList.SkipListInsert(fout, keyWord, p_Voca);
		myVocaSkipList.PrintSkipList(fout);
	}

	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++)
	{

		fout << deleteList[i] << ":";
		posVoca = myVocaSkipList.SkipListSearch(deleteList[i]);
		
		p_Voca = *posVoca;
		fout << *pVoca << endl;
		myVocaSkipList.SkipListRemove(fout, deleteList[i]);
	}
	myVocaSkipList.PrintSkipList(fout);
	fout << endl;


	//myVocaSkipList.PrintSkipList(fout);


	*/


	fout.close();
}
