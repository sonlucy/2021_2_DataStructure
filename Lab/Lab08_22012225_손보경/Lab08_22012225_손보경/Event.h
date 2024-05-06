//#pragma once 
#ifndef EVENT_H
#define EVENT_H
#include <Windows.h>
//#include <iostream>
//#include <string>
//#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;
enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
#define MAX_EVENT_PRIORITY 100
#define NUM_EVENT_GENERATORS 10

class Event
{
	friend ostream& operator<<(ostream& fout, const Event& e);
public:
	Event(); //{ /*event_no = 0, event_gen_addr = 0, event_handler_addr = 0, event_pri = 0, eventStatus = GENERATED;*/ } // default constructor
	Event(int event_id, int event_pri, string title, int genAddr); //constructor
	void printEvent(ostream& fout);

	void setEventHandlerAddr(int evtHndlerAddr) { event_handler_addr = evtHndlerAddr; }
	void setEventGenAddr(int genAddr) { event_gen_addr = genAddr; }
	void setEventNo(int evtNo) { event_no = evtNo; }
	void setEventPri(int pri) { event_pri = pri; }
	void setEventStatus(EventStatus evtStatus) { eventStatus = evtStatus; }
	int getEventPri() { return event_pri; }
	int getEventNo() { return event_no; }
	//우선순위 비교 연산자
	bool operator>(Event& e) { return (event_pri > e.event_pri); }
	bool operator<(Event& e) { return (event_pri < e.event_pri); }
private:
	int event_no;  //이벤트 번호
	string event_title; ////////
	int event_gen_addr;  //생성 주소
	int event_handler_addr;  ///////////////////////////////처리 주소
	int event_pri; // event_priority
	EventStatus eventStatus;  //////////////////////////////////////
};
//Event* genRandEvent(int evt_no);
#endif
