/*
* Lab08
*   Heap Priority Queue [ insert(), removeMin() ]
*     CompleteBinaryTree [ add_at_end(elem), getRootElement() ]
*       TA_Entry [ insert(i, element), remove(i), at(i), set(i, element), operator[] ]
* 
* 
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자: 2021-10-28 
*/
#include <iostream>
#include <fstream>
#include "Event.h"
#include "HeapPrioQueue.h"
#include <string>
#include <stdlib.h>
using namespace std;
#define INITIAL_CBT_CAPA 100
#define TEST_HEAP_PRIO_Q_EVENT  
#define NUM_EVENTS 15  


void main()
{
	ofstream fout;
	string tName = "";
	char tmp[10];
	int priority = -1;
	int current_top_priority;
	int duration = 0;
	int size;
	int* pE;

	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open output.txt file for results !!" << endl;
		exit;
	}


	if (fout.fail())
	{
		cout << "Fail to open output.txt file for results ! " << endl;
		exit;
	}
	Event events[NUM_EVENTS] =  //이벤트 번호, 우선순위, 이름, 생성
	{
		Event(0, 14, "evt_00", 0), Event(1, 13, "evt_01", 1), Event(2, 12, "evt_02", 2),
		Event(3, 11, "evt_03", 3),Event(4, 10, "evt_04", 4),Event(5, 9, "evt_05", 5),
		Event(6, 8, "evt_06", 6),Event(7, 7, "evt_07", 7),Event(8, 6, "evt_08", 8),
		Event(9, 5, "evt_09", 9),Event(10, 4, "evt_10", 10),Event(11, 3, "evt_11", 11),
		Event(12, 2, "evt_12", 12),Event(13, 1, "evt_13", 13),Event(14, 0, "evt_14", 14),
	};

	//이벤트가 가지는 주소 Event*
	HeapPrioQueue<int, Event*> HeapPriQ_Event(INITIAL_CBT_CAPA, string("Event_Heap_Priority_Queue"));
	Event* pEv;
	T_Entry<int, Event*> entry_event, * pEntry_Event;

	for (int i = 0; i < NUM_EVENTS; i++)
	{
		entry_event.setKey(events[i].getEventPri());  //이벤트의 우선순위
		entry_event.setValue(&events[i]);  ///이벤트항목의 주소
		HeapPriQ_Event.insert(entry_event);  ///////////////////////////////
		fout << "Insert " << events[i];  //어떤 항목이 들어갔는지 확인할수있도록 출력
		fout << " ==> Size of Heap Priority Queue : " << setw(3) << HeapPriQ_Event.size() << endl; //변경된크기 확인
	}

	fout << "Final status of insertions : " << endl;
	HeapPriQ_Event.fprintCBT_byLevel(fout); //레벨별로 들여쓰기되면서 출력되게

	for (int i = 0; i < NUM_EVENTS; i++)
	{
		fout << "\nCurrent top priority in Heap Priority Queue : ";
		pEntry_Event = HeapPriQ_Event.getHeapMin();  //지금 현재 root 확인
		fout << *pEntry_Event << endl;   //그 항목 출력
		pEntry_Event = HeapPriQ_Event.removeHeapMin(); ///////////////////////////////
		fout << "Remove " << *pEntry_Event;  //누가 제거되었는지 확인
		fout << "==> " << HeapPriQ_Event.size() << " elements remains." << endl;
		HeapPriQ_Event.fprintCBT_byLevel(fout);  //제거된 상태 출력
		fout << endl;

	}


	fout.close();
}