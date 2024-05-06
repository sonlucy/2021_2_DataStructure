#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <thread>  //////////
#include <process.h>
#include <string>

#include "HeapPrioQueue.h"
#include "Event.h"
#include "SimParams.h"
using namespace std;

enum ROLE {	EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG {INITIALIZE, RUN, TERMINATE };





typedef struct ThreadStatusMonitor  //모니터링을 위한 구조체
{
	int numEventGenerated;  //생성된 이벤트 개수
	int numEventProcessed;  //처리된 이벤트 개수
	int totalEventGenerated; //총 생성된 이벤트 개수
	int totalEventProcessed;  //총 처리한 이벤트 개수
	// used for monitoring only
	Event eventGenerated[TOTAL_NUM_EVENTS];  //생성된이벤트를 담는 변수 
	Event eventProcessed[TOTAL_NUM_EVENTS];  //처리된이벤트를 담는
	THREAD_FLAG* pFlagThreadTerminate; // 스레드 종료를 위함

}; 

typedef struct ThreadParam_Event //스레드 생성 시 인수전달을 위한 구조체
{
	mutex* pCS_main;  //화면 출력에 관련된 임계구역
	mutex* pCS_thrd_mon; //쓰레드에서 공유자원에 관한 임계구역

	FILE* fout;

	HeapPrioQueue <int, Event>* pPriQ_Event; //힙우선순위큐를 담는 변수(할당해주는 변수의 주소값을 담는 포인터)
	ROLE role;
	int myAddr; //쓰레드주소
	int maxRound;
	int targetEventGen;//생성할 이베트의 최대 개수
	LARGE_INTEGER QP_freq;  // used in measurements 시간측정위해
	ThreadStatusMonitor* pThrdMon;  /////////////////////////////////모니터링 변수

}; 

#endif


void EventProc(ThreadParam_Event* pParam);
void EventGen(ThreadParam_Event* pParam);