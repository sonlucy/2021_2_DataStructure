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





typedef struct ThreadStatusMonitor  //����͸��� ���� ����ü
{
	int numEventGenerated;  //������ �̺�Ʈ ����
	int numEventProcessed;  //ó���� �̺�Ʈ ����
	int totalEventGenerated; //�� ������ �̺�Ʈ ����
	int totalEventProcessed;  //�� ó���� �̺�Ʈ ����
	// used for monitoring only
	Event eventGenerated[TOTAL_NUM_EVENTS];  //�������̺�Ʈ�� ��� ���� 
	Event eventProcessed[TOTAL_NUM_EVENTS];  //ó�����̺�Ʈ�� ���
	THREAD_FLAG* pFlagThreadTerminate; // ������ ���Ḧ ����

}; 

typedef struct ThreadParam_Event //������ ���� �� �μ������� ���� ����ü
{
	mutex* pCS_main;  //ȭ�� ��¿� ���õ� �Ӱ豸��
	mutex* pCS_thrd_mon; //�����忡�� �����ڿ��� ���� �Ӱ豸��

	FILE* fout;

	HeapPrioQueue <int, Event>* pPriQ_Event; //���켱����ť�� ��� ����(�Ҵ����ִ� ������ �ּҰ��� ��� ������)
	ROLE role;
	int myAddr; //�������ּ�
	int maxRound;
	int targetEventGen;//������ �̺�Ʈ�� �ִ� ����
	LARGE_INTEGER QP_freq;  // used in measurements �ð���������
	ThreadStatusMonitor* pThrdMon;  /////////////////////////////////����͸� ����

}; 

#endif


void EventProc(ThreadParam_Event* pParam);
void EventGen(ThreadParam_Event* pParam);