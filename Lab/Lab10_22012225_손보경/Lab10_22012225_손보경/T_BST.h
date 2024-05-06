#ifndef T_BST_H
#define T_BST_H
using namespace std;
#include "T_BSTN.h"
#include "T_Entry.h"
#include "T_Array.h"

template<typename K, typename V>
class T_BST
{
public:
	T_BST(string nm) : _root(NULL), num_entry(0), name(nm) {} // constructor 
	string getName() { return name; }
	int size() const { return num_entry; }
	bool empty() const { return num_entry == 0; }
	void clear() {};

	T_BSTN<K, V>* getRoot() { return _root; }  //root읽어오기
	T_BSTN<K, V>** getRootAddr() { return &_root; } //root의주소 읽어오기
	T_Entry<K, V>& getRootEntry() { return _root->getEntry(); }  //rote의 entry 읽어오기
	T_BSTN<K, V>* eraseBSTN(T_BSTN<K, V>** pp); //노드 삭제
	void insertInOrder(const T_Entry<K, V> entry); //순서에 맞춰 집어넣기 
	void insertAndRebalance(T_Entry<K, V> e);

	void traversal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value);  //순서에 맞춰 차례대로  탐색
	void traversal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);  //부모-왼쪽-오른쪽
	void traversal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);  //왼쪽-오른-부모

	T_BSTN<K, V>* searchBSTN(K k);
	V searchBST(K k);  //////////////////////////////////////////////

	T_Entry<K, V>& minEntry();//제일 작은 entry 찾기
	T_Entry<K, V>& maxEntry();  //제일 큰 entry 찾기

	void fprint_with_Depth(ostream& fout);   //들여쓰기 통한 출력
	void fprint_inOrder(ostream& fout);  //오름차순 출력

protected:
	T_BSTN<K, V>* _maxBSTN(T_BSTN<K, V>* subRoot);
	T_BSTN<K, V>* _minBSTN(T_BSTN<K, V>* subRoot);

	T_BSTN<K, V>* _insertInOrder(T_BSTN<K, V>** pp, T_BSTN<K, V>* parenPos, const T_Entry<K, V> ent);
	T_BSTN<K, V>* _insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e);

	T_BSTN<K, V>* _rotate_LL(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_RR(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_RL(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_LR(T_BSTN<K, V>* pCurSubRoot);

	int _getHeight(T_BSTN<K, V>* pTN);
	int _getHeightDiff(T_BSTN<K, V>* pTN);
	T_BSTN<K, V>* _reBalance(T_BSTN<K, V>** ppTN);
	T_BSTN<K, V>* _searchBSTN(T_BSTN<K, V>* pos, K k);
	void _fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth);
	void _fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout);
private:
	T_BSTN<K, V>* _root; // pointer to the root
	int num_entry; // number of tree nodes
	string name;
};

/*template<typename K, typename V>
void T_BST<K, V>::clear()
{

}*/

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_insertInOrder(T_BSTN<K, V>** pp, T_BSTN<K, V>* parenPos, const T_Entry<K, V> entry)
{
	T_BSTN<K, V>* newPos, ** pChildPos;
	T_BSTN<K, V>* pos;
	T_Entry<K, V> ent;
	if (pp == NULL)
	{
		cout << "Error in creation of BinarySearchTree :" << "address of the pointer to the Root Node is NULL !!₩n";
			exit;
	}
	pos = *pp;
	if (pos == NULL)
	{
		pos = new T_BSTN<K, V>(entry);
		if (parenPos == NULL)
		{
			_root = pos; // initialize the root node
		}
		pos->setpPr(parenPos);
		*pp = pos;
		num_entry++; // increment the number of elements
		return pos;
	}
	ent = pos->getEntry();
	if (entry < ent)  //현재 방문하고 있는 ent보다 작으면 왼쪽트리으로 가야함
	{
		pChildPos = pos->getppLc();
		newPos = _insertInOrder(pChildPos, pos, entry);
		if (newPos != NULL)
			pos->setpLc(newPos);
		return NULL; // only the leaf child is set correctly, while the intermediate node is skipped
	}
	else if (entry >= ent)  //현재 방문하고 있는 ent와 같거나 크면 오른쪽트리로 가야함
	{
		pChildPos = pos->getppRc();
		newPos = _insertInOrder(pChildPos, pos, entry);
		if (newPos != NULL)
			pos->setpRc(newPos);
		return NULL; // only the leaf child is set correctly, while the intermediate node is skipped
	}
}

template<typename K, typename V>
void T_BST<K, V>::insertInOrder(const T_Entry<K, V> entry)
{
	_insertInOrder(&_root, NULL, entry);
}

template<typename K, typename V>
void T_BST<K, V>::traversal_inOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
	pLc = pos->getpLc();
	pRc = pos->getpRc();
	traversal_inOrder(pLc, array_value);  //왼
	//자기자신
	entry = pos->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);
	traversal_inOrder(pRc, array_value); //오
}

template<typename K, typename V>void T_BST<K, V>::traversal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
	pLc = pos->getpLc();
	pRc = pos->getpRc();
	//자기자신
	entry = pos->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);

	traversal_preOrder(pLc, array_value); //왼
	traversal_preOrder(pRc, array_value);   //오
}


template<typename K, typename V>void T_BST<K, V>::traversal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
	pLc = pos->getpLc();
	pRc = pos->getpRc();
	traversal_postOrder(pLc, array_value);   //왼
	traversal_postOrder(pRc, array_value);  //오
	//자기자신
	entry = pos->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);
}


template<typename K, typename V>T_BSTN<K, V>* T_BST<K, V>::_searchBSTN(T_BSTN<K, V>* pos, K k)
{
	K ent_k;
	T_BSTN<K, V>* pos_result = NULL;
	if (pos == NULL)
		return NULL;
	ent_k = pos->getKey();
	if (ent_k == k)
		pos_result = pos;
	// given entry was found here !!
	else if (ent_k > k)
		pos_result = _searchBSTN(pos->getpLc(), k); //왼쪽자식
	else if (ent_k < k)
		pos_result = _searchBSTN(pos->getpRc(), k); //오른쪽자식
		
		return pos_result;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::searchBSTN(K key)
{
	T_BSTN<K, V>* pEntry;
	pEntry = _searchBSTN(_root, key);
	return pEntry;
}
template<typename K, typename V>
V T_BST<K, V>::searchBST(K key)
{
	T_BSTN<K, V>* pEntry;
	V value;
	pEntry = _searchBSTN(_root, key);  //루트부터 차례대로 찾기
	value = pEntry->getValue();
	return value;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_minBSTN(T_BSTN<K, V>* subRoot)
{
	T_BSTN<K, V>* pos;//, * pLc;
	if ((subRoot == NULL) || (NULL == subRoot->getpLc()))
		return subRoot;
	//서브루트가 NULL이 아니면
	pos = subRoot;
	while ((pos->getpLc()) != NULL) //서브루트의 왼쪽자식이 있는 동안
		pos = pos->getpLc(); //pos의 왼쪽자식을 pos에 넣어 왼쪽자식이 없을때까지 계속 내려가서 min을 찾을 수 있게.
	return pos;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_maxBSTN(T_BSTN<K, V>* subRoot)
{
	T_BSTN<K, V>* pos;//, * pLc;
	if ((subRoot == NULL) || (NULL == subRoot->getpRc()))
		return subRoot;
	pos = subRoot;
	while ((pos->getpRc()) != NULL)//서브루트의 오른쪽자식이 있는 동안
		pos = pos->getpRc();//pos의 오른쪽자식을 pos에 넣어 오른쪽자식이 없을때까지 계속 내려가서 max을 찾을 수 있게.
	return pos;
}

template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::minEntry()
{
	T_BSTN<K, V>* pMin;
	pMin = _minBSTN(_root);
	return pMin->getEntry();
}

template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::maxEntry()
{
	T_BSTN<K, V>* pMax;
	pMax = _maxBSTN(_root);
	return pMax->getEntry();
}

template<typename K, typename V>
void T_BST<K, V>::_fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout)
{
	T_BSTN<K, V>* pRc, * pLc;
	if ((pLc = pTN->getpLc()) != NULL)
		_fprint_inOrder(pLc, fout);  //가장 왼쪽에 있는 부분이 가장 먼저 출력되는
	fout << pTN->getEntry() << endl;  //자신
	if ((pRc = pTN->getpRc()) != NULL)
		_fprint_inOrder(pRc, fout); //오른쪽
}

template<typename K, typename V>
void T_BST<K, V>::fprint_inOrder(ostream& fout)
{
	T_BSTN<K, V>* root = getRoot();  //root를 읽어내고
	if (num_entry == 0)
	{
		fout << getName() << " is empty now !!" << endl;
		return;
	}
	_fprint_inOrder(root, fout);  //root기준으로 재귀함수 호출
}


template<typename K, typename V>
void T_BST<K, V>::_fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth)
{
	T_BSTN<K, V>* pRc, * pLc;
	T_Entry<K, V>* pEntry;
	if ((pRc = pTN->getpRc()) != NULL)
		_fprint_with_Depth(pRc, fout, depth + 1);  //오른쪽 자식 먼저 출력
	for (int i = 0; i < depth; i++)
	{
		fout << "     ";  //들여쓰기
	}
	fout << pTN->getEntry() << endl;  ///////자신
	if ((pLc = pTN->getpLc()) != NULL)  
		_fprint_with_Depth(pLc, fout, depth + 1);  //왼쪽자식
}

template<typename K, typename V>
void T_BST<K, V>::fprint_with_Depth(ostream& fout)
{
	T_BSTN<K, V>* root = getRoot();
	if (num_entry == 0)
	{
		fout << getName() << " is empty now !!" << endl;
		return;
	}
	_fprint_with_Depth(root, fout, 0);
}


template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::eraseBSTN(T_BSTN<K, V>** pptoBeErased) /////////////////////////////////////////////
// remove BSTN considering balance of the BST
{
	T_BSTN<K, V>* newSubRoot, * temp, * w, * wlc;
	T_BSTN<K, V>* toBeErased;
	toBeErased = *pptoBeErased;
	if (toBeErased == NULL)
		return NULL;
	if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() == NULL)) // 삭제대상 노드의 자식 없으면
	{
		newSubRoot = NULL;
	}
	else if ((toBeErased->getpLc() != NULL) && (toBeErased->getpRc() == NULL)) //삭제 대상 노드 왼쪽자식만 있으면
	{
		newSubRoot = toBeErased->getpLc();  //그 왼쪽자식을 새로운서브루트로 지정해주고
		newSubRoot->setpPr(toBeErased->getpPr());  //이 새로운서브루트의 부모를 삭제대상노드의 부모로.
	}
	else if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() != NULL))  //오른쪽 자식만 있으면
	{
		newSubRoot = toBeErased->getpRc();  //그 오른쪽자식을 새로운서브루트로 지정해주고
		newSubRoot->setpPr(toBeErased->getpPr());  //이 새로운서브루트의 부모는 삭제대상노드의 부모로.
	}
	else  //왼쪽, 오른쪽 자식 둘다 있는 경우
	{ 
		int heightDiff = _getHeightDiff(toBeErased);  //삭제대상노드를 기준으로 왼/오 height를 계산
		T_BSTN<K, V>* parDel = toBeErased->getpPr();
		T_BSTN<K, V>* lChild = toBeErased->getpLc();
		T_BSTN<K, V>* rChild = toBeErased->getpRc();
		T_BSTN<K, V>* ioSs = NULL, * rcIoSs, * parIoSs;
		T_BSTN<K, V>* ioPd = NULL, * lcIoPd, * parIoPd;
		if (heightDiff > 0) //왼쪽 height이 더 높은 경우
			// left subtree is higher, so put the ioPd in the place of the erased node
		{
			ioPd = _maxBSTN(lChild); // in-order predecessor (ioPd). 왼쪽자식들 중 가장 큰거 ioPd에 담아두고
			lcIoPd = ioPd->getpLc();  //이 ioPd의 왼쪽자식
			parIoPd = ioPd->getpPr();  //ioPd의 부모
			newSubRoot = ioPd;  //새로운 서브루트를 ioPd로 설정.
			if (ioPd->getpPr() != toBeErased)  //ioPd의 부모가 삭제대상 노드가 아니라면
			{
				newSubRoot->setpLc(lChild);  //새로운 서브루트의 왼쪽자식 <= 원래 삭제대상노드의 왼쪽자식
				parIoPd->setpRc(lcIoPd);  //ioPd의 부모의 오른쪽자식 <= 원래 ioPd의 왼쪽자식
				if (lcIoPd != NULL)  //ioPd의 왼쪽자식이 존재한다면
					lcIoPd->setpPr(parIoPd);  //ioPd의 왼쪽자식의 부모는 원래 ioPd의 부모.,,,
			}
			newSubRoot->setpRc(rChild);  //새로운 서브루트의 오른쪽자식= 삭제대상노드의 오른쪽자식
			newSubRoot->setpPr(toBeErased->getpPr()); //새로운서브루트의 부모 = 삭제대상노드의 부모
		}
		else  //오른쪽 서브트리의 height이 더 높은 경우
			// right subtree is higher, so put the ioSs in the place of the erased node
		{
			ioSs = _minBSTN(rChild); // in-order successor (ioSs). 오른쪽자식들 중 가장 작은거 ioSs에 담아두고
			rcIoSs = ioSs->getpRc();  //rcloSs: 이 ioSs의 오른쪽자식
			parIoSs = ioSs->getpPr();  //parloSs : 이 ioSs의 부모
			newSubRoot = ioSs;  //새로운 서브루트를 ioSs로 설정.
			if (ioSs->getpPr() != toBeErased)  //ioSs의 부모가 삭제대상 노드가 아니라면
			{
				newSubRoot->setpRc(rChild); //새로운서브루트의 오른쪽자식 <= 삭제대상노드의 오른쪽자식
				parIoSs->setpLc(rcIoSs); // ioSs의 부모의 왼쪽자식 <= 원래 ioSs의 오른쪽자식
				if (rcIoSs != NULL)  //ioSs의 오른쪽자식이 존재한다면
					rcIoSs->setpPr(parIoSs);  //ioSs의 오른쪽자식의 부모는 원래 ioSs의 부모
			}
			newSubRoot->setpLc(lChild);  //새로운 서브루트의 왼쪽자식= 삭제대상노드의 왼쪽자식
			newSubRoot->setpPr(toBeErased->getpPr());  //새로운서브루트의 부모 = 삭제대상 노드의 부모
		}
		if (lChild != ioPd) //삭제대상노드의 왼쪽자식 != 삭제대상노드의 왼쪽자식들 중 가장 큰노드
			lChild->setpPr(newSubRoot);  //삭제대상노드의 왼쪽자식의 부모 = 새로운서브루트로.
		if (rChild != ioSs)  //삭제대상노드의 오른쪽자식 != 삭제대상노드의 오른쪽자식들 중 가장 작은노드
			rChild->setpPr(newSubRoot);  //삭제대상노드의 오른쪽자식의 부모 = 새로운서브루트로. 
	}
	if (toBeErased == _root) //삭제대상 노드가 root라면
		_root = newSubRoot;  //root를 새로운서브루트로.
	num_entry--; // decrement the number of entries in the BST
	free(toBeErased);
	*pptoBeErased = newSubRoot;

	return newSubRoot;
}


template<typename K, typename V>
int T_BST<K, V>::_getHeight(T_BSTN<K, V>* pTN)
{
	int height = 0;
	int height_Lc, height_Rc;
	if (pTN != NULL)  //더 이상 자식이 없을때깢지
	{
		height_Lc = _getHeight(pTN->getpLc());
		height_Rc = _getHeight(pTN->getpRc());
		//height이 더 큰 자식 노드에 1을 더해서 height 결정.
		if (height_Lc > height_Rc)
			height = 1 + height_Lc;
		else
			height = 1 + height_Rc;
	}
	return height;
}

template<typename K, typename V>
int T_BST<K, V>::_getHeightDiff(T_BSTN<K, V>* pTN)
{
	int heightDiff = 0;
	if (pTN == NULL)
		return 0;
	heightDiff = _getHeight(pTN->getpLc()) - _getHeight(pTN->getpRc());
	return heightDiff;
}


template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBR, * pCurParent;
	pCurParent = pCurSubRoot->getpPr();  //현재부모는 현재서브루트의 부모
	pNewSubRoot = pCurSubRoot->getpLc();  //새로운 서브루트는 원래 서브루트의 왼쪽자식
	pBR = pNewSubRoot->getpRc();  //새로운 서브루트의 오른쪽자식이 pBR
	pCurSubRoot->setpLc(pBR);  //현재서브루트의 왼쪽자식을 pBR로
	if (pBR != NULL)  //만약 pBR이 존재하면
		pBR->setpPr(pCurSubRoot);  //pBR의 부모는 현재서브루트
	pNewSubRoot->setpRc(pCurSubRoot);  //새로운 서브루트의 오른쪽자식을 원래 서브루트로,
	pNewSubRoot->setpPr(pCurParent);  //새로운 서브루트의 부모는 pCurParent로(현재서브루트의 부모였던게 얘의 부모로 바뀜)
	pCurSubRoot->setpPr(pNewSubRoot);  //현재서브루트의 부모는 새로운 서브루트

	return pNewSubRoot;
}


template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBL, * pCurParent;
	pCurParent = pCurSubRoot->getpPr(); //현재서브루트의부모를 pCurParent
	pNewSubRoot = pCurSubRoot->getpRc(); //일단 새로운서브루트는 현재서브루트의 오른쪽자식임
	pBL = pNewSubRoot->getpLc();  //새로운서브루트의 왼쪽자식이 pBL

	pCurSubRoot->setpRc(pBL);  //현재서브루트의 오른쪽자식을 pBL로.
	if (pBL != NULL)  //pBL이 존재한다면
		pBL->setpPr(pCurSubRoot);  //pBL의 부모는 현재서브루트
	pNewSubRoot->setpLc(pCurSubRoot); //새로운 서브루트의 왼쪽자식은 현재서브루트
	pNewSubRoot->setpPr(pCurParent);  //새로운 서브루트의 부모는 pCurParent
	pCurSubRoot->setpPr(pNewSubRoot);  //현재서브루트의 부모는 새로운 서브루트가 됨.

	return pNewSubRoot;
}


template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR;
	pC = pCurSubRoot;  
	pCurParent = pCurSubRoot->getpPr();  //일단 현재서브루트의 부모가 현재부모
	pA = pC->getpLc();  //pC의 왼쪽자식은 pA
	pB = pA->getpRc(); //pA의 오른쪽자식은 pB
	pBL = pB->getpLc();  //pB의 왼쪽자식은 pBL
	pBR = pB->getpRc();  //pB의 오른쪽자식은 pBR

	pSubRoot = _rotate_RR(pA);  //먼저 A를 기준으로 오른쪽으로 치우친걸 정리해줌. pSubRoot로는 pB가 됨
	pCurSubRoot->setpLc(pSubRoot);  //현재서브루트의 왼쪽자식을 위에서 얻은 pSubRoot(=pB)로.
	pNewSubRoot = _rotate_LL(pC); //그 다음 C를 기준으로 왼쪽으로 치우친걸 정리해줌. pB가 반환됨.
	pNewSubRoot->setpPr(pCurParent);  //이 새로운 서브루트의 부모는 pCurParent가 되고
	pA->setpPr(pNewSubRoot);  //A의 부모가 pNewSubRoot(=B)
	pC->setpPr(pNewSubRoot);  //C의 부모가 pNewSubRoot(=B)
	if (pBL != NULL)
		pBL->setpPr(pA);  //pBL(원래 B의 왼쪽자식이었던것)의 부모는 A
	if (pBR != NULL)
		pBR->setpPr(pC);  //pBR(원래 B의 오른쪽쪽자식이었던것)의 부모는 C

	return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR;
	pA = pCurSubRoot;  //일단 현재 서브루트는 pA
	pCurParent = pCurSubRoot->getpPr();  //현재서브루트의 부모
	pC = pA->getpRc();  //pA의 오른쪽자식이 pC
	pB = pC->getpLc();  //pC의 왼쪽자식이 pB
	pBL = pB->getpLc();  //pB의 왼쪽자식 
	pBR = pB->getpRc();  //pB의 오른쪽자식

	pSubRoot = _rotate_LL(pC);  //일단 c를 기준으로 왼쪽으로 몰려있으니까(pC-pB-pBL) 바로 잡아줌. 반환되는 값은 pB 
	pCurSubRoot->setpRc(pSubRoot); //현재서브루트의 오른쪽자식은 위에서 반환받은 값(pB)로 .
	pNewSubRoot = _rotate_RR(pA);  //A를 기준으로 오른쪽으로 몰려있으니까(pA-pB-pC) 바로잡아줌. 반환값은 pB

	pNewSubRoot->setpPr(pCurParent); //새로운 서브루트의 부모 설정해주고
	pA->setpPr(pNewSubRoot);  //pA의 부모는 pB
	pC->setpPr(pNewSubRoot);  //pC의 부모는 pB
	if (pBL != NULL)
		pBL->setpPr(pA);  //원래 B의 왼쪽자식이었던 애의 부모는 A가 되고
	if (pBR != NULL)
		pBR->setpPr(pC);  //원래 B의 오른쪽자식이었던 애의 부모는 C가 됨

	return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_reBalance(T_BSTN<K, V>** ppTN)
{
	int heightDiff = 0;
	heightDiff = _getHeightDiff(*ppTN);
	if (heightDiff > 1) // left subtree is higher
	{
		if (_getHeightDiff((*ppTN)->getpLc()) > 0)  //더 밑에 자식에서도 왼쪽트리로 몰려있는 경우
			*ppTN = _rotate_LL(*ppTN);
		else   
			*ppTN = _rotate_LR(*ppTN);
	}
	else if (heightDiff < -1) // right subtree is higher
	{
		if (_getHeightDiff((*ppTN)->getpRc()) < 0)  //더 밑에 자식에서도 오른쪽으로 몰려있는 경우
			*ppTN = _rotate_RR(*ppTN);
		else
			*ppTN = _rotate_RL(*ppTN);
	}
	return *ppTN;
}


template<typename K, typename V>
void T_BST<K, V>::insertAndRebalance(T_Entry<K, V> entry)
{
	_insertAndRebalance(&_root, NULL, entry);
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> entry)
{ //삽입하고 밸런싱해주는 함수
	T_BSTN<K, V>* pTN, ** ppLc, ** ppRc;
	if (*ppTN == NULL) // attach a new tree node at the currently external node
	{
		pTN = new T_BSTN<K, V>(entry);
		*ppTN = pTN;
		if (pPr != NULL) // if not root
			pTN->setpPr(pPr);
		(*ppTN)->setpLc(NULL);
		(*ppTN)->setpRc(NULL);
		num_entry++;
		return *ppTN;
	}

	T_Entry<K, V> bstn_entry;
	bstn_entry = (*ppTN)->getEntry();
	if (entry < bstn_entry) // T_Entry<K, V> must provide ‘<’ operator overloading !! 
	{ //새롭게 입력해야하는 entry가 현재 방문 중인 bstn_entry 값보다 작으면 
		ppLc = (*ppTN)->getppLc();//왼쪽자식의 포인터를 가져와서
		pTN = _insertAndRebalance(ppLc, *ppTN, entry);  //이 왼쪽자식을 기준으로. 재귀함수 호출
		if (ppTN != NULL)
		{
			(*ppTN)->setpLc(pTN);
			*ppTN = _reBalance(ppTN);  //부모노드 기준으로 밸런싱시키기
		}
	}
	else // entry >= bstn_entry
	{ //새롭게 입력해야하는 entry가 현재 방문 중인 bstn_entry 값보다 같거나 크면
		ppRc = (*ppTN)->getppRc();  //오른쪽자식의 포인터 가져와서
		pTN = _insertAndRebalance(ppRc, *ppTN, entry);  //이 오른쪽 자식 기준으로 해서 재귀함수 호출
		if (ppTN != NULL)
		{
			(*ppTN)->setpRc(pTN);
			*ppTN = _reBalance(ppTN);  //부모노드 기준으로 밸런싱시키기
		}
	}
	return *ppTN;

}



#endif