/*
* HW10
* class: Book, Date, T_Array, T_Entry, T_BST, T_BSTN
*
* �ۼ���: ������Ű��а� 22012225 �պ���
* �ۼ���: 2021-11-12
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
//#include "T_BSTv5.h"
#include "T_BST.h"
#include "T_BSTN.h"
#include "T_Entry.h"
#include "T_Array.h"
#include "Book.h"
#include "Date.h"

using namespace std;
#define NUM_BOOKS 15 
void main()
{
	Book books[NUM_BOOKS] =
	{
		//Book( string bk_title, string bk_author, Date dt)
		Book(string("Book_01"), string("Kim"), Date(2020, 1, 1)),
		Book(string("Book_02"), string("Kim"), Date(2010, 1, 1)),
		Book(string("Book_03"), string("Kim"), Date(2013, 1, 1)),
		Book(string("Book_04"), string("Lee"), Date(2011, 1, 1)),
		Book(string("Book_05"), string("Hwang"), Date(2001, 1, 1)),
		Book(string("Book_06"), string("Choi"), Date(2003, 1, 1)),
		Book(string("Book_07"), string("Park"), Date(2009, 1, 1)),
		Book(string("Book_08"), string("Brown"), Date(2012, 1, 1)),
		Book(string("Book_09"), string("Alpha"), Date(1980, 1, 1)),
		Book(string("Book_10"), string("Chalie"), Date(1970, 1, 1)),
		Book(string("Book_11"), string("Tango"), Date(1985, 1, 1)),
		Book(string("Book_12"), string("Yankee"), Date(1977, 1, 1)),
		Book(string("Book_13"), string("Zulu"), Date(2018, 1, 1)),
		Book(string("Book_14"), string("Foxtrot"), Date(2015, 1, 1)),
		Book(string("Book_15"), string("Delta"), Date(2000, 1, 1)),
		/* */
	};
	ofstream fout("output.txt");
	if (fout.fail())
	{
		cout << "Fail to create output.txt for results !!" << endl;
		exit;
	}

	fout << "Input books[] array : " << endl;
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		fout << books[i] << endl;
	}
	fout << endl;
	fout << endl << "Testing Binary Search Tree with Rebalancing " << endl;
	T_Entry<string, Book*> entry_title_pBK;
	T_BST<string, Book*> BBST_BK_keyTitle("BBST_BK_keyTitle");
	T_BSTN<string, Book*>* pRoot, ** ppBBST_BK_root;
	ppBBST_BK_root = BBST_BK_keyTitle.getRootAddr();
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		/* key�� value �����ϰ�*/
		entry_title_pBK.setKey(books[i].getTitle());
		entry_title_pBK.setValue(&books[i]);
		//fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;
		BBST_BK_keyTitle.insertAndRebalance(entry_title_pBK);  //�����ϰ� ������� �뷱�����ֱ�
	}

	fout << "\nEntries in " << BBST_BK_keyTitle.getName() << " (in order of Book Title) : " << endl;
	fout << "BBST_BK_keyTitle : current size (" << BBST_BK_keyTitle.size() << ")" << endl;
	BBST_BK_keyTitle.fprint_inOrder(fout);  ////////////////////////////////////////////////
	///BBST_BK_keyTitle.fprint_with_Depth(fout);   //å ����������� ����
	//fout << endl << "Balanced Binary Search Tree (BBST) with key book-author" << endl;
	T_Entry<string, Book*> entry_Author_pBK;
	T_BST<string, Book*> BBST_BK_keyAuthor("BBST_BK_keyAuthor");
	T_BSTN<string, Book*>** ppRoot_BBST_BK_keyAuthor, * pBBST_BK_keyAuthor;
	ppRoot_BBST_BK_keyAuthor = BBST_BK_keyAuthor.getRootAddr();
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		/* key�� value �����ϰ�*/
		entry_Author_pBK.setKey(books[i].getAuthor());
		entry_Author_pBK.setValue(&books[i]);
		//fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;
		BBST_BK_keyAuthor.insertAndRebalance(entry_Author_pBK);  //�����ϰ� �����̸����� �뷱�����ֱ�
	}
	fout << "\nEntries in " << BBST_BK_keyAuthor.getName() << " (in order of Book Author) : " << endl;
	fout << "BBST_BK_keyAuthor : current size (" << BBST_BK_keyAuthor.size() << ")" << endl;
	BBST_BK_keyAuthor.fprint_inOrder(fout);  //////////////////////////////////////////////
	///BBST_BK_keyAuthor.fprint_with_Depth(fout);    //�����̸� �������� ����
	// Testing Search on Binary Search Tree




	/* ���ڸ� �Է¹޾� ����Ž��Ʈ�� �˻��ϰ�, �� ���ڰ� ������ ��� ������ ���*/
	string InputAuthor = books[0].getAuthor();  //ù��° ���� => kim
	Book* pBk0;
	T_Array<Book*> a_pBook(1, string("Array_Book"));
	cout << "<���ڸ� �Է¹޾� ����Ž��Ʈ�� �˻��ϰ�, �� ���ڰ� ������ ��� ������ ���>\n";
	cout << "�����̸� �Է�:";
	cin >> InputAuthor;
	pBBST_BK_keyAuthor = BBST_BK_keyAuthor.searchBSTN(InputAuthor);  //author = books[0].getAuthor()
	BBST_BK_keyAuthor.traversal_inOrder(pBBST_BK_keyAuthor, a_pBook);  //�����ڽ�->�ڽ�->�������ڽ�
	fout << "\nBooks of author (" << InputAuthor << ") :" << endl;
	for (int i = 0; i < a_pBook.size(); i++)
	{
		if (a_pBook[i]->getAuthor() == InputAuthor)  //
		{
			pBk0 = a_pBook[i]; //�ش��� ����ų�� �ְ�
			fout << *(a_pBook[i]) << endl; 
		}
	}


	/* ������ �� ��¥ ���̿� ���ǵǾ��� ��� ������ ��� */
	string author = books[0].getAuthor();  //ù��° ���� => kim
	Date d1, d2;
	Book* pBk1;
	T_Array<Book*> array_pBook(1, string("Array_Book"));
	d1.setDate(2010, 1, 1);
	d2.setDate(2015, 12, 31);

	cout << "<������ �ΰ� �Է� �޾�, ������ �� ��¥ ���� ���ǵǾ��� ������ ���>\n";
	cout << "��¥1(�� �� ��) �Է�:";
	cin >> d1;
	cout << "��¥2(�� �� ��) �Է�:";
	cin >> d2;


	pBBST_BK_keyAuthor = BBST_BK_keyAuthor.searchBSTN(author);  //author = books[0].getAuthor()
	BBST_BK_keyAuthor.traversal_inOrder(pBBST_BK_keyAuthor, array_pBook);  //�����ڽ�->�ڽ�->�������ڽ�
	//fout << "\nBooks of author (" << author << ") published during " << d1 << " ~ " << d2 << ":" << endl;
	fout << "\nPublished during " << d1 << "~" << d2 << ":";
	for (int i = 0; i < array_pBook.size(); i++)
	{
		pBk1 = array_pBook[i]; //�ش��� ����ų�� �ְ�
		if ((pBk1->getPubDate() >= d1) && (pBk1->getPubDate() <= d2)) 
			fout << *(array_pBook[i]) << endl; ///d1 , d2 ���� �������� ��� ���
	}


	//fout << endl << "Balanced Binary Search Tree (BBST) with key publication date" << endl;
	T_Entry<Date, Book*> entry_PubDate_pBK;
	T_BST<Date, Book*> BBST_BK_keyPubDate("BBST_BK_keyPubDate");
	T_BSTN<Date, Book*>** ppRoot_BBST_BK_keyPubDate;
	ppRoot_BBST_BK_keyPubDate = BBST_BK_keyPubDate.getRootAddr();
	for (int i = 0; i < NUM_BOOKS; i++)
	{
		/* key�� value �����ϰ�*/
		entry_PubDate_pBK.setKey(books[i].getPubDate());
		entry_PubDate_pBK.setValue(&books[i]);
		//fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;
		BBST_BK_keyPubDate.insertAndRebalance(entry_PubDate_pBK);//�����ϰ� �����ϱ��� �뷱�����ֱ�
	}
	fout << "\nEntries in " << BBST_BK_keyPubDate.getName() << " (in order of Book Publication Date) : " << endl;
	fout << "BBST_BK_keyPubDate : current size (" << BBST_BK_keyPubDate.size() << ")" << endl;
	BBST_BK_keyPubDate.fprint_inOrder(fout);  /////////////////////////////
	//BBST_BK_keyPubDate.fprint_with_Depth(fout);   //������ �������� ����


	/*���ڿ� ������ �Է¹޾� �� ���ڰ� ������ ������ ���Ŀ� ������ ��� ���� ���*/
	string inputAuthor= books[0].getAuthor();  
	Date d;
	d.setDate(2010, 1, 1);  
	Book* pBk2;
	T_Array<Book*> arr_pBook(1, string("Array_Book"));

	cout << "\n<���ڸ�� ������ �Է¹ް�, �ش� ������ �Էµ� ������ ���� ���ǵ� ��� ���� ���>";
	cout << "\n���ڸ� �Է�:";
	cin >> inputAuthor;
	cout << "������ �Է�:";
	cin >> d;

	pBBST_BK_keyAuthor = BBST_BK_keyAuthor.searchBSTN(inputAuthor);  //author = books[0].getAuthor()
	BBST_BK_keyAuthor.traversal_inOrder(pBBST_BK_keyAuthor, arr_pBook);  //�����ڽ�->�ڽ�->�������ڽ�
	fout << "\nBooks of author (" << author << ") published after " << d<<":" << endl;
	for (int i = 0; i < arr_pBook.size(); i++)
	{
		if (arr_pBook[i]->getAuthor() == inputAuthor)  //
		{
			pBk2 = arr_pBook[i]; //�ش��� ����ų�� �ְ�
			if ((pBk2->getPubDate() >= d)) //d1=(2010, 1, 1), d2=(2015, 12, 31);
				fout << *(arr_pBook[i]) << endl; ///kim������ 2010-1-1 ~ 2015-12-31 ���� �������� ��� ���
		}
	}



	fout << "\nClearing BBST_BKs . . . " << endl;
	BBST_BK_keyTitle.clear();
	BBST_BK_keyAuthor.clear();
	BBST_BK_keyPubDate.clear();
	fout << "All BBST_BKs cleared !! " << endl;
	fout.close();
}
