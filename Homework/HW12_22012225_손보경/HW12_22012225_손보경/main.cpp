/*
* HW12
* trie �ڷᱸ�� - ��������(predictive text) Ž��
* �Է¹��� ���ξ ������ �ܾ� ���� ���
* trie���α��� ���캼 �� �ֵ����ϴ� fprint ��ü��±��
* trie�� ���Ե� �ܾ�� �� �Է¹��� �ܾ �����ϴ� ���
* ��ü trie ���� (erase)
* 
* ������Ű��а� 22012225 �պ���
* 2021- 11- 27
*/

#include <iostream>
#include <fstream>
#include <list>
#include <string>

#include "MyVoca.h"
#include "MyVocaList.h"
#include "Trie.h"
#include "TrieNode.h"

using namespace std;
#define MAX_WORD_LENGTH 100
#define NUM_TEST_VOCAS 7
//#define TEST_SIMPLE_TRIE
//void test_simple_trie(ostream& fout);
//void test_trie_myVoca(ostream& fout);

void main()
{
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		printf("Error in opening output file !\n");
		exit;
	}
	Trie<MyVoca*> trie_myVoca("Trie_MyVoca");
	TrieNode<MyVoca*>* pTN;
	MyVoca* pVoca;
	int word_count;
	string keyStr;
	char keyWord[MAX_WORD_LENGTH];
	List_pVoca predictVocas;
	List_pVoca_Iter itr;

	/* Testing Basic Operation in trie */
	MyVoca testVocas[NUM_TEST_VOCAS] =
	{
		MyVoca("xyz", NOUN, { "" }, { "" }),
		MyVoca("ABCD", NOUN, { "" }, { "" }),
		MyVoca("ABC", NOUN, { "" }, { "" }),
		MyVoca("AB", NOUN, { "" }, { "" }),
		MyVoca("A", NOUN, { "" }, { "" }),
		MyVoca("xy", NOUN, { "" }, { "" }),
		MyVoca("x", NOUN, { "" }, { "" }),
	};

	fout << "Testing basic operations of trie inserting ..... " << endl;
	for (int i = 0; i < NUM_TEST_VOCAS; i++)
	{
		trie_myVoca.insert(testVocas[i].getKeyWord(), &testVocas[i]);
	}
	trie_myVoca.fprintTrie(fout);

	/*Destroy the trie*/
	fout << "\nTesting TrieDestroy...\n";
	trie_myVoca.eraseTrie();   /////////////
	trie_myVoca.fprintTrie(fout);

	/* inserting keyWords into trie */
	fout << "Inserting My Vocabularies to myVocaDict . . . " << endl;
	word_count = 0;
	pVoca = &myToeicVocaList[0];   //////////////

	while (pVoca->getKeyWord() != "-1")
	{
		keyStr = pVoca->getKeyWord();
		trie_myVoca.insert(keyStr, pVoca);
		pVoca++;
	}
	fout << "Total " << trie_myVoca.size() << " words in trie_myVoca .." << endl;
	trie_myVoca.fprintTrie(fout);

	/* testing keyWord search in trie */
	while (1)
	{
		cout << "\nInput any prefix to search in trie (. to finish) : ";
		cin >> keyStr;
		if (keyStr == string("."))
			break;

		predictVocas.clear();
		trie_myVoca.findPrefixMatch(keyStr, predictVocas);
		cout << "list of predictive wors with prefix (" << keyStr << ") :" << endl;
		itr = predictVocas.begin();
		for (int i = 0; i < predictVocas.size(); i++)
		{
			pVoca = *itr;
			cout << *pVoca << endl;   //�Էµ� ���ξ ������ �ܾ�� ���
			++itr;
		}
	}

	string k;
	cout << "������ �ܾ� �Է�:";
	cin >> k;
	fout << "\n�Է¹��� ������ �ܾ� :" << k << endl;
	trie_myVoca.deleteKeyWord(k);
	trie_myVoca.fprintTrie(fout);


	cout << "\nErasing trie_myVoca ...." << endl;
	fout << "\nErasing trie_myVoca ...." << endl;
	trie_myVoca.eraseTrie();   ///��ü trie ����
	fout.close();
}

