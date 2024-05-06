#include <iostream>
#include <iomanip>
#include <fstream>
#include "HeapPrioQueue.h"
#include <string>
#include <stdlib.h>
using namespace std;
#define INITIAL_CBT_CAPA 100  //초기용량
#define NUM_DATA 15

void main()
{
	ofstream fout;
	int size;
	int* pD;
	int inputArray[NUM_DATA] = { 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open output.txt file for results !!" << endl;
		exit;
	}

	HeapPrioQueue<int> HeapPriQ_int(INITIAL_CBT_CAPA, string("Heap_Priority_Queue_Int"));

	for (int i = 0; i < NUM_DATA; i++)
	{
		HeapPriQ_int.insert(inputArray[i]);
		fout << "Insert " << setw(3) << inputArray[i];
		fout << " ==> Size of Heap Priority Queue : " << setw(3) << HeapPriQ_int.size() << endl;
	}
	fout << "Final status of insertions : " << endl;
	HeapPriQ_int.fprintCBT_byLevel(fout);
	for (int i = 0; i < NUM_DATA; i++)
	{
		fout << "\nCurrent top priority in Heap Priority Queue : ";
		pD = HeapPriQ_int.getHeapMin();
		fout << setw(3) << *pD << endl;
		pD = HeapPriQ_int.removeHeapMin();
		fout << "RemoveMin (" << *pD << ") from HeapPriQ_int";
		fout << " ==> " << HeapPriQ_int.size() << " elements remains." << endl;
		HeapPriQ_int.fprintCBT_byLevel(fout);
		fout << endl;
	}
	fout.close();
}
