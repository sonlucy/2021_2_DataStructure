/*
* Lab09 
* Tread Event
* 
* �ۼ���: ������Ű��а� 22012225 �պ���
* �ۼ�����: 2021-11-04
* ������ ��������: 2021-11-05
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <iostream>
#include "Multi_Thread.h"
#include "HeapPrioQueue.h"
#include "Event.h"
#include "ConsoleDisplay.h"
#include "SimParams.h"
#include <time.h>
#include <conio.h>
using namespace std;


void main()
{
	LARGE_INTEGER QP_freq, t_befor, t_after;
	LONGLONG t_diff;
	double elapsed_time, min_elapsed_time, max_elapsed_time;
	double avg_elapsed_time, total_elapsed_time;

	HeapPrioQueue<int, Event> heapPriQ_Event(30, string("HeapPriorityQueue_Event"));
	Event* pEvent, * pEv_min_elapsed_time, * pEv_max_elapsed_time;
	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr;
	mutex cs_main;
	mutex cs_thrd_mon;
	ThreadStatusMonitor thrdMon;
	HANDLE consHndlr;
	THREAD_FLAG eventTheadFlag = RUN;
	int count, numEventGenerated, numEventProcessed;
	int num_events_in_PriQ;
	Event eventProcessd[TOTAL_NUM_EVENTS];

	consHndlr = initConsoleHandler();
	QueryPerformanceFrequency(&QP_freq);
	srand(time(NULL));

	thrdMon.pFlagThreadTerminate = &eventTheadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].setEventNo(-1);
		thrdMon.eventProcessed[ev].setEventPri(-1);
	}



	/* Create and Active Thread_EventHandlr */
	/* ������ �Ķ������ �׸���� �����Ͽ� �Ķ���� �غ�. */
	thrdMon.numEventProcessed = 0;
	thrdParam_EventHndlr.role = EVENT_HANDLER;
	thrdParam_EventHndlr.myAddr = 1;
	thrdParam_EventHndlr.pCS_main = &cs_main;
	thrdParam_EventHndlr.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventHndlr.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventHndlr.maxRound = MAX_ROUND;
	thrdParam_EventHndlr.QP_freq = QP_freq;
	thrdParam_EventHndlr.pThrdMon = &thrdMon;
	
	thread thrd_EvProc(EventProc, &thrdParam_EventHndlr); ///////////////event�� ó���ϴ� thread ���� �� ����. Thread_EventHandler.cpp�� EventProc()�Լ�
	cs_main.lock();
	printf("Thread_EventGen is created and activated ///\n");
	cs_main.unlock();



	/* Create and Active Thread_EventGen */
	/* ������ �Ķ������ �׸���� �����Ͽ� �Ķ���� �غ�. */
	thrdMon.numEventGenerated = 0;
	thrdParam_EventGen.role = EVENT_GENERATOR;
	thrdParam_EventGen.myAddr = 0;
	thrdParam_EventGen.pCS_main = &cs_main;
	thrdParam_EventGen.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventGen.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;
	thrdParam_EventGen.maxRound = MAX_ROUND;
	thrdParam_EventGen.QP_freq = QP_freq;
	thrdParam_EventGen.pThrdMon = &thrdMon;

	thread thed_EvGen(EventGen, &thrdParam_EventGen);   //////////event�� �����ϴ� thread ���� �� ����.  Thread_EventGenerator.cpp�� EventGen()�Լ�
	cs_main.lock();
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();


	/* periodic monitoring in main() */
	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();
		cls(consHndlr);
		gotoxy(consHndlr, 0, 0);  //�� �������� Ŀ�� �̵�
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n", //���ݱ��� �� ����/ó���� �̺�Ʈ ���� 
			round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);

		printf("\n******************************************\n");
		numEventGenerated = thrdMon.numEventGenerated; //////////////���� ������ �̺�Ʈ ��
		printf("Events generated (current total = %2d)\n", numEventGenerated);  //���� ������ �̺�Ʈ �� ���

		count = 0;
		for (int ev = 0; ev < numEventGenerated; ev++)
		{
			pEvent = &thrdMon.eventGenerated[ev];   //
			if (pEvent != NULL)
			{
				cout << *pEvent << " ";  //������ �̺�Ʈ�� ���
				if (((ev + 1) % EVENTS_PER_LINE) == 0)
					printf("\n");
			}
		}

		printf("\n\n******************************************\n");
		num_events_in_PriQ = heapPriQ_Event.size(); ////
		printf("Events currently in Priority_Queue (%d) : \n", num_events_in_PriQ);
		heapPriQ_Event.fprint(cout);  //////queue�� ����ϰ� �ִ� �̺�Ʈ�� ���
		printf("\n\n******************************************\n");

		numEventProcessed = thrdMon.totalEventProcessed;  //��ü ó���� �̺�Ʈ ��
		printf("Events processed (current total = %d):\n", numEventProcessed);

		count=0;
		total_elapsed_time = 0.0;
		for (int ev = 0; ev < numEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev];    ///////////////////////////
			if (pEvent != NULL)
			{
				////////////////////////////////cout << *pEvent << " ";
				pEvent->printEvent_proc();                ////////ó���� �̺�Ʈ ���
				if (((ev + 1) % EVENTS_PER_LINE) == 0)
					printf("\n");
			}
			if (ev == 0)
			{
				min_elapsed_time = max_elapsed_time = total_elapsed_time = pEvent->getEventElapsedTime();
				pEv_min_elapsed_time = pEv_max_elapsed_time = pEvent;
			}
			else
			{
				if (min_elapsed_time > pEvent->getEventElapsedTime())
				{
					min_elapsed_time = pEvent->getEventElapsedTime();
					pEv_min_elapsed_time = pEvent;
				}
				if (max_elapsed_time < pEvent->getEventElapsedTime())
				{
					max_elapsed_time = pEvent->getEventElapsedTime();
					pEv_max_elapsed_time = pEvent;
				}

				total_elapsed_time += pEvent->getEventElapsedTime();

			}
		}


		printf("\n");
		if (numEventProcessed > 0)
		{
			printf("numEventProcessed = %d\n", numEventProcessed);
			printf("min_elpsed_time = %8.2lf[ms]; ", min_elapsed_time);
			cout << *pEv_min_elapsed_time << endl;

			printf("max_elpsed_time = %8.2lf[mx]; ", max_elapsed_time);
			cout << *pEv_max_elapsed_time << endl;

			avg_elapsed_time = total_elapsed_time / numEventProcessed;  ///////
			printf("avg_elapsed_time = %8.2lf[ms]; \n", avg_elapsed_time);

		}
		if (numEventProcessed >= TOTAL_NUM_EVENTS)  //ó���� �̺�Ʈ ������ TOTAL_NUM_EVENTS �̻��̸�(��ǥġ �̻�)
		{
			eventTheadFlag = TERMINATE;  //Tread�� ������ ���߰� flag�� TERMINATE��. 
			cs_main.unlock();
			break;
		}

		cs_main.unlock();
		Sleep(100);

	}

	/*�����尡 �����Ҷ����� ��ٷ���*/
	thrd_EvProc.join();
	thed_EvGen.join();

	printf("Hit any key to terminate . . .:");
	_getch();

}
