#include <Windows.h>
#include "Multi_Thread.h"
#include "HeapPrioQueue.h"
#include "Event.h"
#include "SimParams.h"
#include<iostream>
#define myExitCode 0
using namespace std;
using std::this_thread::sleep_for;

void EventGen(ThreadParam_Event* pParam)
{
	ThreadParam_Event* pThrdParam;
	HeapPrioQueue<int, Event>* pPriQ_Event;
	int myRole;
	THREAD_FLAG* pFlagThreadTerminate;
	int maxRound;
	T_Entry<int, Event>* pEntry, entry_event;
	Event event, * pEvent;
	int event_no = 0;
	int event_priority = 0;
	int event_gen_count = 0;
	int targetEventGen;
	int myAddr = -1;
	int event_handler_addr;
	LARGE_INTEGER QP_freq, t_gen;
	ThreadStatusMonitor* pThrdMon;
	
	pThrdParam = (ThreadParam_Event*)pParam;
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	targetEventGen = pThrdParam->targetEventGen;
	for (int round = 0; round < maxRound; round++)
	{
		if (event_gen_count >= targetEventGen)
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
			else
			{
				sleep_for(std::chrono::milliseconds(500));
				continue;
			}
		}
		//else (��ǥ�� �̺�Ʈ �������� ������ �� �����ϵ���
		event_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr;
		event_priority = targetEventGen - event_gen_count - 1;
		event.setEventNo(event_no);
		event.setEventPri(event_priority);
		event.setEventGenAddr(myAddr);
		event.setEventHandlerAddr(-1); // event handler is not defined yet !!
		QueryPerformanceCounter(&t_gen);
		event.setEventGenTime(t_gen);       ///////////////////////////////////////////////////
		event.setEventStatus(GENERATED);
		entry_event.setKey(event.getEventPri());
		entry_event.setValue(event);


		pThrdParam = (ThreadParam_Event*)pParam;
		myRole = pThrdParam->role;
		myAddr = pThrdParam->myAddr;
		pPriQ_Event = pThrdParam->pPriQ_Event;
		pThrdMon = pThrdParam->pThrdMon;
		maxRound = pThrdParam->maxRound;
		targetEventGen = pThrdParam->targetEventGen;


		for (int round = 0; round < maxRound; round++)
		{
			if (event_gen_count >= targetEventGen)
			{
				if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
					break;
				else
				{
					sleep_for(std::chrono::milliseconds(500));
					continue;

				}
			}
			event_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr;
			event_priority = targetEventGen - event_gen_count - 1;
			event.setEventNo(event_no);
			event.setEventPri(event_priority);
			event.setEventGenAddr(myAddr);
			event.setEventHandlerAddr(-1); // event handler is not defined yet !!
			QueryPerformanceCounter(&t_gen);
			event.setEventGenTime(t_gen);  ///////////////////////////////////////////////
			event.setEventStatus(GENERATED);


			entry_event.setKey(event.getEventPri());
			entry_event.setValue(event);


			while (pPriQ_Event->insert(entry_event) == NULL)  //������������
			{
				pThrdParam->pCS_main->lock();
				cout << "PriQ_Event is Full, waiting ..." << endl;
				pThrdParam->pCS_main->unlock();
				sleep_for(std::chrono::milliseconds(100));
				/*
				pThrdParam->pCS_main->lock();
				cout << "Trying to insert an event into PriQ_Event " << endl;
				pThrdParam->pCS_main->unlock();
				sleep_for(std::chrono::milliseconds(100));
				*/
			}
			pThrdParam->pCS_main->lock();  //ȭ����� ���� mutex
			cout << "Successfully inserted into PriQ_Event " << endl;
			pThrdParam->pCS_main->unlock();

			pThrdParam->pCS_thrd_mon->lock(); //�����ڿ� ���� ����ϴ� mutex
			pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = event;  //������ �̺�Ʈ���� ��� ����ֱ�
			pThrdMon->numEventGenerated++;
			pThrdMon->totalEventGenerated++;
			pThrdParam->pCS_thrd_mon->unlock();
			event_gen_count++;
			//Sleep(100 + rand() % 300);
			sleep_for(std::chrono::milliseconds(100));  //�־��� �ð����� �Ͻ� ���� ���°� �ǰ�, �ð��� ������ �ٽ� ���� ��� ���·� ���ư���.
														
		}
	}
}
