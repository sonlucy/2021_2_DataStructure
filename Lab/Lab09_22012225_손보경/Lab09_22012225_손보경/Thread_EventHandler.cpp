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

	LARGE_INTEGER QP_freq, t_gen, t_proc;  ////�̺�Ʈ �ð� ���� ���� ����
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
			pThrdParam->pCS_thrd_mon->lock();  /////�����ڿ� ������ ����ϴ� 
			//pThrdMon->pEventsg[pThrdMon->numEventProcs] = pEvent;
			
			event.setEventHandlerAddr(myAddr);


			//////////////////////////////////// �̺�Ʈ ����~ó������ �ɸ��� �ð� ���
			QueryPerformanceCounter(&t_proc);  //ó���� �ð� �����ؼ�
			event.setEventProcTime(t_proc);    //ó���� �ð� ����

			t_gen = event.getEventGenTime();   //������ �ð��� getEventGenTime�κ��� �޾ƿ���

			t_diff = t_proc.QuadPart - t_gen.QuadPart;   ////ó���Ƚð� - �����Ƚð�

			elapsed_time = ((double)t_diff / QP_freq.QuadPart); // in second , ���ļ��� ������
			event.setEventElaspsedTime(elapsed_time * 1000); // in milli-second

			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = event;     ////ó���� �̺�Ʈ���� ��� ����ֱ�
			pThrdMon->numEventProcessed++;
			pThrdMon->totalEventProcessed++;
			pThrdParam->pCS_thrd_mon->unlock();
		} // end if

		
		sleep_for(std::chrono::milliseconds(100 + rand() % 100));    //�����Ȱɸ� �ʹ� ���� ó���� �Ǿ generated�� ����Ǹ鼭 �������� �����ǰ�, ó���� �� �ȵ� �� ����
	} // end for
}
