/*
* Lab09 
* Tread Event
* 
* 작성자: 정보통신공학과 22012225 손보경
* 작성일자: 2021-11-04
* 마지막 수정일자: 2021-11-05
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
	/* 스레드 파라미터의 항목들을 설정하여 파라미터 준비. */
	thrdMon.numEventProcessed = 0;
	thrdParam_EventHndlr.role = EVENT_HANDLER;
	thrdParam_EventHndlr.myAddr = 1;
	thrdParam_EventHndlr.pCS_main = &cs_main;
	thrdParam_EventHndlr.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventHndlr.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventHndlr.maxRound = MAX_ROUND;
	thrdParam_EventHndlr.QP_freq = QP_freq;
	thrdParam_EventHndlr.pThrdMon = &thrdMon;
	
	thread thrd_EvProc(EventProc, &thrdParam_EventHndlr); ///////////////event를 처리하는 thread 생성 및 실행. Thread_EventHandler.cpp의 EventProc()함수
	cs_main.lock();
	printf("Thread_EventGen is created and activated ///\n");
	cs_main.unlock();



	/* Create and Active Thread_EventGen */
	/* 스레드 파라미터의 항목들을 설정하여 파라미터 준비. */
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

	thread thed_EvGen(EventGen, &thrdParam_EventGen);   //////////event를 생성하는 thread 생성 및 실행.  Thread_EventGenerator.cpp의 EventGen()함수
	cs_main.lock();
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();


	/* periodic monitoring in main() */
	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();
		cls(consHndlr);
		gotoxy(consHndlr, 0, 0);  //맨 왼쪽위로 커서 이동
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n", //지금까지 총 생성/처리된 이벤트 개수 
			round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);

		printf("\n******************************************\n");
		numEventGenerated = thrdMon.numEventGenerated; //////////////현재 생성된 이벤트 수
		printf("Events generated (current total = %2d)\n", numEventGenerated);  //현재 생성된 이벤트 수 출력

		count = 0;
		for (int ev = 0; ev < numEventGenerated; ev++)
		{
			pEvent = &thrdMon.eventGenerated[ev];   //
			if (pEvent != NULL)
			{
				cout << *pEvent << " ";  //생성된 이벤트들 출력
				if (((ev + 1) % EVENTS_PER_LINE) == 0)
					printf("\n");
			}
		}

		printf("\n\n******************************************\n");
		num_events_in_PriQ = heapPriQ_Event.size(); ////
		printf("Events currently in Priority_Queue (%d) : \n", num_events_in_PriQ);
		heapPriQ_Event.fprint(cout);  //////queue에 대기하고 있는 이벤트들 출력
		printf("\n\n******************************************\n");

		numEventProcessed = thrdMon.totalEventProcessed;  //전체 처리된 이벤트 수
		printf("Events processed (current total = %d):\n", numEventProcessed);

		count=0;
		total_elapsed_time = 0.0;
		for (int ev = 0; ev < numEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev];    ///////////////////////////
			if (pEvent != NULL)
			{
				////////////////////////////////cout << *pEvent << " ";
				pEvent->printEvent_proc();                ////////처리한 이벤트 출력
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
		if (numEventProcessed >= TOTAL_NUM_EVENTS)  //처리된 이벤트 개수가 TOTAL_NUM_EVENTS 이상이면(목표치 이상)
		{
			eventTheadFlag = TERMINATE;  //Tread의 동작이 멈추게 flag를 TERMINATE로. 
			cs_main.unlock();
			break;
		}

		cs_main.unlock();
		Sleep(100);

	}

	/*스레드가 종료할때까지 기다려줌*/
	thrd_EvProc.join();
	thed_EvGen.join();

	printf("Hit any key to terminate . . .:");
	_getch();

}
