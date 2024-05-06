#include <Windows.h>
#include "Multi_Thread.h"
#include "HeapPrioQueue.h" 
#include "Event.h"
#include "SimParams.h"
#include <iostream>

using namespace std; 
using std::this_thread::sleep_for; 

void EventProc(ThreadParam_Event* pParam)
{

	ThreadParam_Event* pThrdParam;
	HeapPrioQueue<int, Event>* pPriQ_Event;
	int myRole; 
	int myAddr; 
	THREAD_FLAG* pFlagThreadTerminate;
	int maxRound; 

	T_Entry<int, Event>* pEntry;
	Event event, * pEvent, * pEventProc;
	int event_no = 0;
	int eventPriority = 0; 
	int event_gen_count = 0;
	int num_pkt_processed = 0;
	int targetEventGen;

	LARGE_INTEGER QP_freq, t_gen, t_proc;  ////이벤트 시간 측정 관련 변수
	LONGLONG t_diff; double elapsed_time; 
	ThreadStatusMonitor* pThrdMon;

	pThrdParam = (ThreadParam_Event*)pParam;
	myRole = pThrdParam->role; 
	myAddr = pThrdParam->myAddr; 
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon; 
	maxRound = pThrdParam->maxRound;
	QP_freq = pThrdParam->QP_freq;
	targetEventGen = pThrdParam->targetEventGen;

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break;
		//else
		if (!pPriQ_Event->isEmpty())
		{
			pEntry = pPriQ_Event->removeHeapMin();
			event = pEntry->getValue();
			pThrdParam->pCS_thrd_mon->lock();  /////공유자원 ㅆㄹ때 사용하는 
			//pThrdMon->pEventsg[pThrdMon->numEventProcs] = pEvent;
			
			event.setEventHandlerAddr(myAddr);


			//////////////////////////////////// 이벤트 생성~처리까지 걸리는 시간 계산
			QueryPerformanceCounter(&t_proc);  //처리된 시간 측정해서
			event.setEventProcTime(t_proc);    //처리된 시간 세팅

			t_gen = event.getEventGenTime();   //생성된 시간을 getEventGenTime로부터 받아오고

			t_diff = t_proc.QuadPart - t_gen.QuadPart;   ////처리된시간 - 생성된시간

			elapsed_time = ((double)t_diff / QP_freq.QuadPart); // in second , 주파수로 나눠줌
			event.setEventElaspsedTime(elapsed_time * 1000); // in milli-second

			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = event;     ////처리된 이벤트들을 계속 담아주기
			pThrdMon->numEventProcessed++;
			pThrdMon->totalEventProcessed++;
			pThrdParam->pCS_thrd_mon->unlock();
		} // end if

		
		sleep_for(std::chrono::milliseconds(100 + rand() % 100));    //슬립안걸면 너무 빨리 처리가 되어서 generated만 실행되면서 무한으로 생성되고, 처리는 잘 안될 수 있음
	} // end for
}
