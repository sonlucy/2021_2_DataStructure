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

	string& getTitle() { return title; }  //책 제목 반환
	string getAuthor() { return author; }  //책 작가 반환
	Date getPubDate() { return pubDate; }  //책 발행일 반환

	void setTitle(string bk_title) { title = bk_title; }  //책 제목 설정
	void setAuthor(string bk_author) { author = bk_author; }  //책 저자이름 설정

private:
	string title;
	string author;
	Date pubDate; // date of publish
};
#endif