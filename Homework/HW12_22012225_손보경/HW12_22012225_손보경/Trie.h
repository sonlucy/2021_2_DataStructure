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

	void insert(string keyWord, E value);  //Ű���� �߰�
	void insertExternalTN(TrieNode<E>* pTN, string keyWord, E value);

	TrieNode<E>* findKeyWord(string keyWord);  //�־��� keyword Ž��
	void findPrefixMatch(string prefix, List_pVoca& predictWords); //���ξ� ��ġ�ϴ� �ܾ�� ��Ƽ� list�� ����ֱ�

	void deleteKeyWord(string keyWord); //������ keyword �׸��� ����
	void eraseTrie();  //��ü keyword ����

	void fprintTrie(ostream& fout);
protected:
	TrieNode<E>* _find(string keyWord, SearchMode sm = FULL_MATCH); //������ keyword�� ��ġ�� TrieNode�� ��ȯ
	void _traverse(TrieNode<E>* pTN, List_pVoca& list_keywords); //TreNode���� ���������� �湮�ؼ� �ش�Ǵ� keywords���� List_pVoca�� �����

private:
	TrieNode<E>* _root; // root trie ����� ������
	int num_keys;  //��ü key�� ����
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


	pTN->setChild(pTN_New); //pTN�� childe�� pTN_New 
	//pTN_New->setParent(pTN);
	(pTN->getChild())->setParent(pTN);   //pTN_New�� parent�� pTN

	pTN_New->setValue(value);  ////////////
	//cout << "key (" << keyWord << ") is inserted \n";
}

template<typename E>
void Trie<E>::insert(string keyWord, E value)
{
	TrieNode<E>* pTN = NULL, * pTN_New = NULL;
	char keyWording[MAX_STR_LEN];
	char* keyPtr = (char*)keyWord.c_str();  //keyWord�� �ִ� ���ڵ��� �ϳ��� �湮�ϸ鼭 ���ϱ����� ������////////////////////////////////

	if (keyPtr == NULL)
		return;

	/* Firstly, check any possible duplicated key insertion */
	if (_find(keyWord, FULL_MATCH) != NULL)  //�̹� �ش��ϴ� Ű���尡 ������
	{
		cout << "The given key string (" << keyWord << ") is already existing; just return !!" << endl;
		return;
	}

	pTN = this->_root;  //��Ʈ����
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{
		//�ش��ϴ� trie����� key���� ���� �����Ϸ��� key�� �� ũ��, pTN�� next�� NULL, key���ڰ� �����ִ� ����
		if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))
			break;  //�� ��ġ���� break�ؼ� while�� �����Ű�� while�� �ٱ����� ���Խ�Ű����
		//�ش��ϴ� trie����� key���� ���� �����Ϸ��� key�� �� ũ��,pTN�� next�� NULL�� �ƴ϶��
		while ((pTN->getKey() < *keyPtr) && (pTN->getNext() != NULL))
			pTN = pTN->getNext();  //�� ���� next�� �Ѿ�� while���� �ݺ��ǵ���. �ݺ��ϴٰ� next�� null�� �ƴϰ� �Ǹ� �׶� ����
		while ((pTN != NULL) && (pTN->getKey() == *keyPtr) && (*keyPtr != '\0')) //ex: abc�� �ִ� ���¿��� abx�� �����Ϸ��Ҷ�
		{
			pTN = pTN->getChild();  //������ ��������
			keyPtr++;
		}
		//�ش��ϴ� trie����� key���� !���� �����Ϸ��� key�� �� ������!
		if ((pTN->getKey() > *keyPtr) && (*keyPtr != '\0'))
			break;  //pTN�� �� ������ ������ �ؾ���. �ϴ� break�ؼ� while�� ������������.
	} // end while for positioning



	/* Secondly, the given key string is a sub-string of an existing key */
	// e.g.) �̹� "abcde" �� �ִµ� "abc" �� �����Ϸ��Ҷ�  
	//������ ���Ե� Ű ���ڿ��� �Ϻΰ� ���ο� Ű ���ڿ��� ���ԵǴ� ���
	if ((pTN->getKey() != '\0') && (*keyPtr == '\0'))
	{
		/* there was a longer key string already !! */
		/* break the longer key string, and connected to the separated key strings */
		pTN_New = new TrieNode<E>('\0', value);  //external��� �߰��ϱ�����
		pTN_New->setParent(pTN->getParent());  //d�� parent�� c. �� ��尡 parent�� �����ǰ�. a-b-c-new
		(pTN->getParent())->setChild(pTN_New);                                             //      -d-e  
		pTN_New->setNext(pTN);  //pTN_New�� next�� pTN�� �ǵ���.
		pTN->setPrev(pTN_New);  //pTN�� prev�� pTN_New�� �ǵ���
		//cout << "key (" << keyWord << ") is inserted" << endl;
		this->num_keys++;
		return;
	}
	//���� �Է��Ϸ��� Ű���� �� ũ�� next�� NULL�̰� key�ܾ ����������
	//ex) abc�ִµ� cat�� �߰��Ϸ��Ҷ�
	//�̹� ���Ե� Ű ���ڿ��麸�� �� ������ ���ο� ���ڿ� ����
	else if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))
	{
		/* at this level, a new substring is inserted as the last nodes */
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
		pTN_New->setParent(pTN->getParent());  //���ο� ����� parent�� pTN�� parent 
		pTN_New->setPrev(pTN);  //pTN_New�� prev�� pTN
		pTN->setNext(pTN_New);  //pTN�� next�� pTN_New
		pTN = pTN_New;  //pTN�� �ٽ� ���������� �Űܰ��� �������κе��� �޼��ְ�. c-a-t
		keyPtr++;
		while (*keyPtr != '\0')
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
			pTN->setChild(pTN_New);  //pTN�� child�� pTN_New
			(pTN->getChild())->setParent(pTN);  //pTN_New�� parent�� pTN
			pTN = pTN->getChild();    //��� ������ ��������
			keyPtr++;
		}

		if (*keyPtr == '\0')
		{
			insertExternalTN(pTN, keyWord, value);  //external ��� �߰�. ��üŰ���带 value������ ��������.
			this->num_keys++;
			return;
		}
	}
	//���� �Է��Ϸ��� key���� �� �������. 
	//�̹� ���Ե� Ű ���ڿ��� ���� �ռ� ������ ���ο� ���ڿ��� ����.
				// �̹� ���Ե� Ű ���ڿ��� �߰��� ���ο� ���ڿ� ����???
	else if ((pTN->getKey() > *keyPtr) && (*keyPtr != '\0'))
	{
		/* insert between two existing trie nodes */
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
		pTN_New->setNext(pTN);  //pTN_New�� next�� pTN
		pTN_New->setParent(pTN->getParent());  //pTN_New�� parent�� pTN�� parent

		if (pTN->getPrev() == NULL)  //pTN�� �� ù��° ��忴�� ����.
		{ /* this pTN_new becomes the new first in this level */
			if (pTN->getParent() != NULL)
				(pTN->getParent())->setChild(pTN_New); //pTN�� parent�� child�� pTN_New ����Ű����
		}
		else //(pTN->getPrev() != NULL)  // pTN->prev - pTN_New - pTN 
		{
			(pTN->getPrev())->setNext(pTN_New);  //pTN�� prev��带 ã�Ƽ� �� ����� next�� pTN_New�� ����Ű��
		}
		pTN_New->setPrev(pTN->getPrev());  //pTN_New�� prev���δ� pTN�� prev��尡 �����ǵ���
		pTN->setPrev(pTN_New);  //pTN�� prev���� pTN_New. 

		pTN = pTN_New;
		keyPtr++;
		while (*keyPtr != '\0')
		{
			//���� ������ ������� while��
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
			pTN->setChild(pTN_New);
			(pTN->getChild())->setParent(pTN);
			pTN = pTN->getChild();	//�����ִ� Ű���� ���ڵ��� �Ʒ������� �������鼭 ���ʴ�� ó���ϵ���
			keyPtr++;
		}
		if (*keyPtr == '\0')  //Ű���� ��ü�� ������ ����
		{
			insertExternalTN(pTN, keyWord, value); //external��� �߰�
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
	char* keyPty; //keyStr�� �ѽ��縵�� ���󰡸� ���� �� �ֵ��� �ϴ� ������
	TrieNode<E>* pTN = NULL;  //�湮���� TrieNode �� ����Ű�� ������
	//TrieNode<E>* found = NULL;  //ã������ ����� found ������?

	keyPty = (char*)keyWord.c_str(); //�� ù��° ����
	if (keyPty == NULL) //ã������ ���ڿ���ü�� ���ǵǾ� ���� ����
		return NULL;
	pTN = this->_root; //root���� �����ؼ� ã�ư�����
	while ((pTN != NULL) && (*keyPty != '\0'))
	{
		while ((pTN != NULL) && (pTN->getKey() < *keyPty))  //next�� ���� ã�ƾ��Ұ��
		{
			if (pTN->getNext() == NULL)
				return NULL;
			pTN = pTN->getNext();
		}
		if ((pTN != NULL) && (pTN->getKey() > *keyPty)) //���ʺ��� ���ʴ�� ã�ư����ִµ�. ���ʿ� �ִٰ� ?
		{
			// key not found
			return NULL;
		}
		else if ((pTN == NULL) && (*keyPty != '\0'))  //�� �̻� ������ ���µ� ���� ���ڰ� �����ִ� ���
		{
			// key not found
			return NULL;
		}
		else if ((pTN->getKey() == *keyPty) && (*keyPty != '\0')) //������ key�� ã�Ұ�, ���� key���ڴ� �����ִ� ���
		{
			pTN = pTN->getChild();  //������ key�� ã�ұ⶧���� child�� �Ѿ�� ��� ã�ƾ���
			keyPty++;
			if (*keyPty == '\0') //��� ������ ã�ƿ°�
			{
				/* key or prefix found */
				if (sm == FULL_MATCH)   //
				{
					if (pTN->getKey() == '\0') //external ������ ã�ƿ�
					{
						/* found the key string as a full-match */
						return pTN;
					}
					else // (pTN->getKey() != '\0'). ���� ã������ keyword���� �� �� Ű���尡 ��忡 �����Ǿ�����
					{
						/* found the key string as a substring of a longer existing string */
						return NULL;
					}
				}

				else if (sm == PREFIX_MATCH)  //���ξ ���� ��쿡�� ��ȯ
				{
					/* found the key string as a full-match or as a substring of a longer existing
					string */
					return pTN;
				}
			}
			else if ((pTN->getKey() == '\0') && (*keyPty != '\0')) //���� ã������ ketword�� �Ϻ� ���ξ�κ��� ����(�� �ڿ��� ���̻��� ��尡 ����)
			{
				if (pTN->getNext() != NULL)
				{
					pTN = pTN->getNext();  //next�� ���� ã�ƺ��� �ֵ���
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
	if (pTN == NULL) //���� �湮���� TrieNode�� NULL ��
		return;
	if (pTN->getChild() == NULL) //EXTERNAL ��忡 ���������� 
	{
		list_keywords.push_back(pTN->getValue()); ////����湮���� TrieNode�� value�� �о� list�� ���
	}
	else  //pTN->getChild() != NULL
	{
		_traverse(pTN->getChild(), list_keywords); //child�� ���� ��� ã�ƺ����ֵ���
	}
	if (pTN->getNext() != NULL)
	{
		_traverse(pTN->getNext(), list_keywords);  //next�� ���� ��� ã�ƺ����ֵ���
	}
}

template<typename E>
void Trie<E>::findPrefixMatch(string keyStr, List_pVoca& predictWords)
{
	//TrieNode<E>* pPtr = NULL;  //trie����� ������
	const char* keyPtr;  //key string�� �ѱ��ھ� ã�ư��� ���
	TrieNode<E>* pTN = NULL;  //trie����� trie��� ������
	//TrieNode<E>* found = NULL;

	keyPtr = (char*)keyStr.c_str();
	if (keyPtr == NULL) //Ű���� �߸������Ǿ�����
		return;

	pTN = this->_root;  //��Ʈ���� �����ؼ� ã�ư�����
	pTN = _find(keyStr, PREFIX_MATCH);
	_traverse(pTN, predictWords);  //ã�Ҵ� ��ġ���� traverse ������ �ش��ϴ� Ű������� List_pVoca�� ���
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
		else if (!(pTN->getPrev()) && pTN->getNext()) //ptN�� prev�� NULL�̰� 
		{
			tmp = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			pTN = pTN->getNext();
			pTN->setPrev(NULL);
			free(tmp);
			break;
		}
		else  //�����ؾ��ϴ� ���ڿ� ��,�޿� ��� TRIE��尡 ���� ���. �θ�� �ö󰡸鼭 ��� �����ؾ���
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
void Trie<E>::eraseTrie()  //������ key���� �������� ����
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