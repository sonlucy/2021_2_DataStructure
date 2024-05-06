#ifndef Trie_H
#define Trie_H
#include <iostream>
#include <string>
#include "TrieNode.h"
#include "MyVoca.h" /////////
#define MAX_STR_LEN 50
//#define DEBUG
using namespace std;

typedef list<MyVoca*> List_pVoca;
typedef list<MyVoca*>::iterator List_pVoca_Iter;

enum SearchMode { FULL_MATCH, PREFIX_MATCH };

template <typename E>
class Trie
{
public:
	Trie(string name); // constructor
	int size() { return num_keys; }

	void insert(string keyWord, E value);  //키워드 추가
	void insertExternalTN(TrieNode<E>* pTN, string keyWord, E value);

	TrieNode<E>* findKeyWord(string keyWord);  //주어진 keyword 탐색
	void findPrefixMatch(string prefix, List_pVoca& predictWords); //접두어 일치하는 단어들 모아서 list에 담아주기

	void deleteKeyWord(string keyWord); //지정된 keyword 항목을 삭제
	void eraseTrie();  //전체 keyword 삭제

	void fprintTrie(ostream& fout);
protected:
	TrieNode<E>* _find(string keyWord, SearchMode sm = FULL_MATCH); //지정된 keyword의 위치의 TrieNode를 반환
	void _traverse(TrieNode<E>* pTN, List_pVoca& list_keywords); //TreNode들을 순차적으로 방문해서 해당되는 keywords들을 List_pVoca에 담아줌

private:
	TrieNode<E>* _root; // root trie 노드의 포인터
	int num_keys;  //전체 key의 개수
	string trie_name;
};
template<typename E>
Trie<E>::Trie(string name)
{
	trie_name = name;
	//_root = new TrieNode<E>('\0', "");
	_root = new TrieNode<E>('\0', E());
	_root->setKey('\0');
	_root->setPrev(NULL);
	_root->setNext(NULL);
	_root->setParent(NULL);
	_root->setChild(NULL);
	num_keys = 0;
};

template<typename E>
void Trie<E>::insertExternalTN(TrieNode<E>* pTN, string keyWord, E value)
{
	TrieNode<E>* pTN_New = NULL;

	pTN_New = new TrieNode<E>('\0', E());  //E? value?
	//pTN_New = new TrieNode<E>('\0', value);  //E? value?


	pTN->setChild(pTN_New); //pTN의 childe는 pTN_New 
	//pTN_New->setParent(pTN);
	(pTN->getChild())->setParent(pTN);   //pTN_New의 parent는 pTN

	pTN_New->setValue(value);  ////////////
	//cout << "key (" << keyWord << ") is inserted \n";
}

template<typename E>
void Trie<E>::insert(string keyWord, E value)
{
	TrieNode<E>* pTN = NULL, * pTN_New = NULL;
	char keyWording[MAX_STR_LEN];
	char* keyPtr = (char*)keyWord.c_str();  //keyWord에 있는 문자들을 하나씩 방문하면서 비교하기위한 포인터////////////////////////////////

	if (keyPtr == NULL)
		return;

	/* Firstly, check any possible duplicated key insertion */
	if (_find(keyWord, FULL_MATCH) != NULL)  //이미 해당하는 키워드가 있으면
	{
		cout << "The given key string (" << keyWord << ") is already existing; just return !!" << endl;
		return;
	}

	pTN = this->_root;  //루트부터
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{
		//해당하는 trie노드의 key보다 내가 삽입하려는 key가 더 크고, pTN의 next는 NULL, key문자가 남아있는 상태
		if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))
			break;  //이 위치에서 break해서 while문 종료시키고 while문 바깥에서 삽입시키게함
		//해당하는 trie노드의 key보다 내가 삽입하려는 key가 더 크고,pTN의 next가 NULL이 아니라면
		while ((pTN->getKey() < *keyPtr) && (pTN->getNext() != NULL))
			pTN = pTN->getNext();  //그 다음 next로 넘어가서 while문이 반복되도록. 반복하다가 next가 null이 아니게 되면 그때 삽입
		while ((pTN != NULL) && (pTN->getKey() == *keyPtr) && (*keyPtr != '\0')) //ex: abc가 있는 상태에서 abx를 삽입하려할때
		{
			pTN = pTN->getChild();  //밑으로 내려가서
			keyPtr++;
		}
		//해당하는 trie노드의 key보다 !내가 삽입하려는 key가 더 작으면!
		if ((pTN->getKey() > *keyPtr) && (*keyPtr != '\0'))
			break;  //pTN의 앞 순서에 삽입을 해야함. 일단 break해서 while문 빠져나가도록.
	} // end while for positioning



	/* Secondly, the given key string is a sub-string of an existing key */
	// e.g.) 이미 "abcde" 가 있는데 "abc" 를 삽입하려할때  
	//기존에 포함된 키 문자열의 일부가 새로운 키 문자열로 삽입되는 경우
	if ((pTN->getKey() != '\0') && (*keyPtr == '\0'))
	{
		/* there was a longer key string already !! */
		/* break the longer key string, and connected to the separated key strings */
		pTN_New = new TrieNode<E>('\0', value);  //external노드 추가하기위해
		pTN_New->setParent(pTN->getParent());  //d의 parent는 c. 그 노드가 parent로 설정되게. a-b-c-new
		(pTN->getParent())->setChild(pTN_New);                                             //      -d-e  
		pTN_New->setNext(pTN);  //pTN_New의 next가 pTN이 되도록.
		pTN->setPrev(pTN_New);  //pTN의 prev가 pTN_New이 되도록
		//cout << "key (" << keyWord << ") is inserted" << endl;
		this->num_keys++;
		return;
	}
	//실제 입력하려는 키값이 더 크고 next가 NULL이고 key단어가 남아있을때
	//ex) abc있는데 cat을 추가하려할때
	//이미 포함된 키 문자열들보다 뒤 순서에 새로운 문자열 삽입
	else if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))
	{
		/* at this level, a new substring is inserted as the last nodes */
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
		pTN_New->setParent(pTN->getParent());  //새로운 노드의 parent는 pTN의 parent 
		pTN_New->setPrev(pTN);  //pTN_New의 prev는 pTN
		pTN->setNext(pTN_New);  //pTN의 next는 pTN_New
		pTN = pTN_New;  //pTN을 다시 오른쪽으로 옮겨가서 나머지부분들을 달수있게. c-a-t
		keyPtr++;
		while (*keyPtr != '\0')
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
			pTN->setChild(pTN_New);  //pTN의 child로 pTN_New
			(pTN->getChild())->setParent(pTN);  //pTN_New의 parent로 pTN
			pTN = pTN->getChild();    //계속 밑으로 내려가게
			keyPtr++;
		}

		if (*keyPtr == '\0')
		{
			insertExternalTN(pTN, keyWord, value);  //external 노드 추가. 전체키워드를 value값으로 가지도록.
			this->num_keys++;
			return;
		}
	}
	//내가 입력하려는 key값이 더 작을경우. 
	//이미 포함된 키 문자열들 보다 앞선 순서에 새로운 문자열을 삽입.
				// 이미 포함된 키 문자열들 중간에 새로운 문자열 삽입???
	else if ((pTN->getKey() > *keyPtr) && (*keyPtr != '\0'))
	{
		/* insert between two existing trie nodes */
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
		pTN_New->setNext(pTN);  //pTN_New의 next가 pTN
		pTN_New->setParent(pTN->getParent());  //pTN_New의 parent는 pTN의 parent

		if (pTN->getPrev() == NULL)  //pTN이 맨 첫번째 노드였던 상태.
		{ /* this pTN_new becomes the new first in this level */
			if (pTN->getParent() != NULL)
				(pTN->getParent())->setChild(pTN_New); //pTN의 parent가 child로 pTN_New 가리키도록
		}
		else //(pTN->getPrev() != NULL)  // pTN->prev - pTN_New - pTN 
		{
			(pTN->getPrev())->setNext(pTN_New);  //pTN의 prev노드를 찾아서 그 노드의 next로 pTN_New를 가리키게
		}
		pTN_New->setPrev(pTN->getPrev());  //pTN_New의 prev노드로는 pTN의 prev노드가 설정되도록
		pTN->setPrev(pTN_New);  //pTN의 prev노드로 pTN_New. 

		pTN = pTN_New;
		keyPtr++;
		while (*keyPtr != '\0')
		{
			//위와 동일한 방식으로 while문
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
			pTN->setChild(pTN_New);
			(pTN->getChild())->setParent(pTN);
			pTN = pTN->getChild();	//남아있는 키워드 문자들을 아래쪽으로 내려가면서 차례대로 처리하도록
			keyPtr++;
		}
		if (*keyPtr == '\0')  //키워드 전체를 삽입한 상태
		{
			insertExternalTN(pTN, keyWord, value); //external노드 추가
			this->num_keys++;
			return;
		}
	}
}

template<typename E>
TrieNode<E>* Trie<E>::findKeyWord(string keyWord)
{
	TrieNode<E>* pTN = NULL;
	pTN = _find(keyWord, FULL_MATCH);
	return pTN;
}
template<typename E>
TrieNode<E>* Trie<E>::_find(string keyWord, SearchMode sm)
{
	char* keyPty; //keyStr의 한스펠링씩 따라가며 비교할 수 있도록 하는 포인터
	TrieNode<E>* pTN = NULL;  //방문중인 TrieNode 를 가리키는 포인터
	//TrieNode<E>* found = NULL;  //찾았을때 사용할 found 포인터?

	keyPty = (char*)keyWord.c_str(); //맨 첫번째 글자
	if (keyPty == NULL) //찾으려는 문자열자체가 정의되어 있지 않음
		return NULL;
	pTN = this->_root; //root부터 시작해서 찾아가도록
	while ((pTN != NULL) && (*keyPty != '\0'))
	{
		while ((pTN != NULL) && (pTN->getKey() < *keyPty))  //next로 가서 찾아야할경우
		{
			if (pTN->getNext() == NULL)
				return NULL;
			pTN = pTN->getNext();
		}
		if ((pTN != NULL) && (pTN->getKey() > *keyPty)) //왼쪽부터 차례대로 찾아가고있는데. 왼쪽에 있다고 ?
		{
			// key not found
			return NULL;
		}
		else if ((pTN == NULL) && (*keyPty != '\0'))  //더 이상 갈곳이 없는데 비교할 문자가 남아있는 경우
		{
			// key not found
			return NULL;
		}
		else if ((pTN->getKey() == *keyPty) && (*keyPty != '\0')) //동일한 key값 찾았고, 아직 key문자는 남아있는 경우
		{
			pTN = pTN->getChild();  //동일한 key를 찾았기때문에 child로 넘어가서 계속 찾아야함
			keyPty++;
			if (*keyPty == '\0') //노드 끝까지 찾아온거
			{
				/* key or prefix found */
				if (sm == FULL_MATCH)   //
				{
					if (pTN->getKey() == '\0') //external 노드까지 찾아옴
					{
						/* found the key string as a full-match */
						return pTN;
					}
					else // (pTN->getKey() != '\0'). 내가 찾으려는 keyword보다 더 긴 키워드가 노드에 구성되어있음
					{
						/* found the key string as a substring of a longer existing string */
						return NULL;
					}
				}

				else if (sm == PREFIX_MATCH)  //접두어가 같은 경우에도 반환
				{
					/* found the key string as a full-match or as a substring of a longer existing
					string */
					return pTN;
				}
			}
			else if ((pTN->getKey() == '\0') && (*keyPty != '\0')) //내가 찾으려는 ketword의 일부 접두어부분이 동일(그 뒤에는 더이상의 노드가 없음)
			{
				if (pTN->getNext() != NULL)
				{
					pTN = pTN->getNext();  //next로 가서 찾아볼수 있도록
					continue;
				}
				else
					return NULL;
			}
			else
			{
				continue;
			}
		}
	} // end while
}

template<typename E>
void Trie<E>::_traverse(TrieNode<E>* pTN, List_pVoca& list_keywords)
{
	if (pTN == NULL) //지금 방문중인 TrieNode가 NULL 임
		return;
	if (pTN->getChild() == NULL) //EXTERNAL 노드에 도달했으면 
	{
		list_keywords.push_back(pTN->getValue()); ////현재방문중인 TrieNode의 value를 읽어 list에 담기
	}
	else  //pTN->getChild() != NULL
	{
		_traverse(pTN->getChild(), list_keywords); //child로 가서 계속 찾아볼수있도록
	}
	if (pTN->getNext() != NULL)
	{
		_traverse(pTN->getNext(), list_keywords);  //next로 가서 계속 찾아볼수있도록
	}
}

template<typename E>
void Trie<E>::findPrefixMatch(string keyStr, List_pVoca& predictWords)
{
	//TrieNode<E>* pPtr = NULL;  //trie노드의 포인터
	const char* keyPtr;  //key string의 한글자씩 찾아갈때 사용
	TrieNode<E>* pTN = NULL;  //trie노드의 trie노드 포인터
	//TrieNode<E>* found = NULL;

	keyPtr = (char*)keyStr.c_str();
	if (keyPtr == NULL) //키워드 잘못설정되어있음
		return;

	pTN = this->_root;  //루트부터 시작해서 찾아가도록
	pTN = _find(keyStr, PREFIX_MATCH);
	_traverse(pTN, predictWords);  //찾았던 위치에서 traverse 수행해 해당하는 키워드들을 List_pVoca에 담기
	//printf("Error in TrieSearch (key: %s) !!\n", keyWord);
}


/*template<typename E>
void Trie<E>::findPrefixMatch(const char* pPrefix, List_pVoca& predictWords)
{
	TrieNode<E>* pTN = NULL;
	if (pPrefix == NULL)
		return;
	pTN = _find(pPrefix, PREFIX_MATCH);
	_traverse(pTN, predictWords);
	//printf("Error in TrieSearch (key: %s) !!\n", keyWord);
}*/

template<typename E>
void Trie<E>::deleteKeyWord(string keyWord)
{
	TrieNode<E>* pTN = NULL, * _root;
	TrieNode<E>* tmp = NULL;
	int trie_val;
	_root = this->_root;
	if (NULL == _root || "" == keyWord)  ////NULL == keyWord  : c2677
		return;
	pTN = _find(keyWord, FULL_MATCH);
	if (pTN == NULL)
	{
		cout << "Key [" << keyWord << "] not found in trie" << endl;
		return;
	}
	while (1)
	{
		if (pTN == NULL)
			break;
		if (pTN->getPrev() && pTN->getNext())
		{
			tmp = pTN;
			(pTN->getNext())->setPrev(pTN->getPrev());
			(pTN->getPrev())->setNext(pTN->getNext());
			free(tmp);
			break;
		}
		else if (pTN->getPrev() && !(pTN->getNext()))
		{
			tmp = pTN;
			(pTN->getPrev())->setNext(NULL);
			free(tmp);
			break;
		}
		else if (!(pTN->getPrev()) && pTN->getNext()) //ptN의 prev가 NULL이고 
		{
			tmp = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			pTN = pTN->getNext();
			pTN->setPrev(NULL);
			free(tmp);
			break;
		}
		else  //삭제해야하는 문자에 오,왼에 어떠한 TRIE노드가 없는 경우. 부모로 올라가면서 계속 삭제해야함
		{
			tmp = pTN;
			pTN = pTN->getParent();
			if (pTN != NULL)
				pTN->setChild(NULL);
			free(tmp);
			if ((pTN == _root) && (pTN->getNext() == NULL) && (pTN->getPrev() == NULL))
			{
				cout << "Now, the trie is empty !!" << endl;
				break;
			}
		}
	}
	this->num_keys--;
}

template<typename E>
void Trie<E>::eraseTrie()  //마지막 key부터 역순으로 삭제
{
	TrieNode<E>* pTN;
	TrieNode<E>* pTN_to_be_deleted = NULL;
	if (this->_root == NULL)
		return;
	pTN = this->_root;
	/* delete the last key word first */
	while (pTN != NULL)
	{
		while ((pTN != NULL) && (pTN->getNext()))
			pTN = pTN->getNext();
		while (pTN->getChild())
		{
			if (pTN->getNext())
				break;
			pTN = pTN->getChild();
		}

		if (pTN->getNext())
			continue;
		if (pTN->getPrev() && pTN->getNext())
		{
			pTN_to_be_deleted = pTN;
			(pTN->getNext())->setPrev(pTN->getPrev());
			(pTN->getPrev())->setNext(pTN->getNext());
			pTN = pTN->getNext();
			free(pTN_to_be_deleted);
		}

		else if (pTN->getPrev() && !(pTN->getNext()))
		{
			pTN_to_be_deleted = pTN;
			(pTN->getPrev())->setNext(NULL);
			pTN = pTN->getPrev();
			free(pTN_to_be_deleted);
		}
		else if (!(pTN->getPrev()) && pTN->getNext())
		{
			pTN_to_be_deleted = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			(pTN->getNext())->setPrev(NULL);
			pTN = pTN->getNext();
			free(pTN_to_be_deleted);
		}
		else
		{
			pTN_to_be_deleted = pTN;
			if (pTN == this->_root)
			{
				/* _root */
				this->num_keys = 0;
				return;
			}
			if (pTN->getParent() != NULL)
			{
				pTN = pTN->getParent();
				pTN->setChild(NULL);
			}

			else
			{
				pTN = pTN->getPrev();
			}
			free(pTN_to_be_deleted);
		} // end if - else
	} // end while
}

template<typename E>
void Trie<E>::fprintTrie(ostream& fout)
{
	TrieNode<E>* pTN;
	int indent = 0;
	fout << "trie ( " << this->trie_name << ") with "
		<< this->num_keys << " trie_nodes\n";
	if (this->num_keys == 0)
	{
		fout << "Empty trie !" << endl;
		return;
	}
	pTN = this->_root;
	pTN->_fprint(fout, pTN, indent);
}
#endif