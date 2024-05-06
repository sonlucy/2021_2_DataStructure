#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include "Date.h"

class Book
{
	friend ostream& operator<<(ostream& fout, Book& bk)
	{
		fout.setf(ios::left);
		fout << "[" << setw(8) << bk.title << ", " << setw(8) << bk.author << ", " << bk.pubDate << "]";
		return fout;
	}
public:
	Book(string bk_title, string bk_author, Date dt) :
		title(bk_title), author(bk_author), pubDate(dt) {}

	string& getTitle() { return title; }  //å ���� ��ȯ
	string getAuthor() { return author; }  //å �۰� ��ȯ
	Date getPubDate() { return pubDate; }  //å ������ ��ȯ

	void setTitle(string bk_title) { title = bk_title; }  //å ���� ����
	void setAuthor(string bk_author) { author = bk_author; }  //å �����̸� ����

private:
	string title;
	string author;
	Date pubDate; // date of publish
};
#endif