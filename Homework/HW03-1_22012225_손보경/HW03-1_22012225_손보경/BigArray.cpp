#include "BigArray.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

BigArray::BigArray(int n) // constructor
	:num_elements(n)
{
	big_array = (int*) new int[num_elements];  //num_elements개수만큼 동적배열 생성
	if (big_array == NULL)
	{
		cout << "Error in creation of dynamic array of size(" << num_elements<< ") !!" << endl;
		exit;
	}
}
BigArray::~BigArray() // destructor
{
	if (big_array != NULL)
		delete[] big_array;  //동적배열 삭제
}

void BigArray::genBigRandArray(int base_offset)
{
	char* flag;
	int count = 0;
	int rand_h, rand_l, big_rand, biased_big_rand;
	srand(time(0));
	flag = (char*) new char[num_elements]; //동적배열 생성
	
	while (count < num_elements)  //함수로부터 전달받은 num_elements크기보다 작을 동안
	{
		rand_h = rand();
		rand_l = rand();
		big_rand = ((long)rand_h << 15) | rand_l;  //왼쪽으로 15비트만큼 shift시키고 다시 rand시켜 비트or연산
		big_rand = big_rand % num_elements;  //모듈로 연산을 통해 범위 지정 
		if (flag[big_rand] == 1)  //이미 생성되었던 난수면
			continue; //그냥 continue해서 다시 while문 실행되게
		else
		{
			flag[big_rand] = 1;  //이미 생성되었던 난수가 아니면 1로 바꿔주어서 생성되었던 난수라는 표시를 해줌
			biased_big_rand = big_rand + base_offset;
			big_array[count] = biased_big_rand;
			count++;
		}
	}
	delete[] flag;
}

void BigArray::getStatistics(ArrayStatistics& stats)
{
	int min = INT_MAX;
	int max = INT_MIN;
	int mean = 0;
	double sum = 0.0;
	double avg = 0.0;
	double diff_sq_sum = 0.0;
	double var, std_dev;
	
	int element;
	for (int i = 0; i < num_elements; i++)
	{
		element = big_array[i];
		sum += element;
		if (element > max)
			max = element;
		if (element < min)
			min = element;
	}
	avg = sum / (double)num_elements;
	mean = sum / num_elements;
	diff_sq_sum = 0.0;
	for (int i = 0; i < num_elements; i++)
	{
		element = big_array[i];
		diff_sq_sum += (element - avg) * (element - avg);
	}
	var = diff_sq_sum / (double)num_elements;
	std_dev = sqrt(var);
	stats.min = min;
	stats.max = max;
	stats.avg = avg;
	stats.mean = mean;
	stats.var = var;
	stats.std_dev = std_dev;
}

void BigArray::fprintStatistics(ostream& fout)
{
	ArrayStatistics stats;
	fout.setf(ios::fixed);
	fout.setf(ios::showpoint);
	fout.precision(2);
	getStatistics(stats);
	fout << "Statistics: " << endl;
	fout << " min (" << stats.min << "), max ("
		<< stats.max << "), avg (" << stats.avg;
	fout <<"), mean (" <<stats.mean << "), var (" << stats.var << "), std_dev ("
		<< stats.std_dev << ")" << endl;
}

void BigArray::suffle()
{
	srand(time(0));
	int index1, index2;
	int rand_1, rand_2;
	int temp;
	for (int i = 0; i < num_elements; i++)
	{
		rand_1 = rand();
		rand_2 = rand();
		index1 = ((rand_1 << 15) | rand_2)% num_elements;

		rand_1 = rand();
		rand_2 = rand();
		index2 = ((rand_1 << 15) | rand_2)% num_elements;

		/* temp 선언하여 뒤섞어주는데 사용 */
		/* swapping big_array[index1] and big_array[index2] */
		temp = big_array[index1];
		big_array[index1] = big_array[index2];
		big_array[index2] = temp;
	}
}

void BigArray::selection_sort()
{
	int min; // index of the element with minimum value
	double minValue; // minimum value
	for (int i = 0; i < num_elements - 1; i++)
	{
		min = i;
		minValue = big_array[i];
		for (int j = i + 1; j < num_elements; j++)
		{
			if (minValue > big_array[j])
			{
				min = j;
				minValue = big_array[j];
			}
		}
		if (min != i) // if a smaller element is found, then swap
		{
			/* minValue is dA[min] */
			big_array[min] = big_array[i];
			big_array[i] = minValue;
		}
	} // end for
}

int _partition(int* array, int size, int left, int right,
	int pivotIndex, int level)
{
	int pivotValue; // pivot value
	int newPI; // store index
	double temp;
	int i;
#ifdef DEBUG_QUICKSORT
	for (i = 0; i < level; i++) // put indentation
		fout << " ";
	fout << " Partition (left " << left << ", right "
		<< right << ", pivotIdex "
		<< pivotIndex << "(pV:"
		<< array[pivotIndex]
		<< ") ) =>";
#endif
	pivotValue = array[pivotIndex];
	temp = array[pivotIndex];
	array[pivotIndex] = array[right];
	array[right] = temp; // Move pivot to end

	newPI = left;
	for (i = left; i <= (right - 1); i++) {
		if (array[i] <= pivotValue) {
			temp = array[i];
			array[i] = array[newPI];
			array[newPI] = temp;
			newPI = newPI + 1;
		}
	}
	// swap array[newPI] and array[right]; 
	// Move pivot to its final place
	temp = array[newPI];
	array[newPI] = array[right];
	array[right] = temp;

	return newPI;
}

void _quick_sort(int* array, int size, int left, int right, int level)
{
	int pI, newPI; // pivot index
	if (left >= right) {
		return;
	}
	else if (left < right)
	{ // subarray of 0 or 1 elements already sorted
	//select a pI (pivotIndex) in the range left ≤ pI ≤ right
		pI = (left + right) / 2;
	}
	newPI = _partition(array, size, left, right, pI, level);
	if (left < (newPI - 1))
	{
		_quick_sort(array, size, left, newPI - 1, level + 1);
		// recursively sort elements on the left of pivotNewIndex
	}
	if ((newPI + 1) < right)
	{
		_quick_sort(array, size, newPI + 1, right, level + 1);
		// recursively sort elements on the right of pivotNewIndex
	}
} // end _quick_sort()

void BigArray::quick_sort()
{
	int pI, newPI; // pivot index
	_quick_sort(big_array, num_elements, 0, num_elements - 1, 0);
}
void BigArray::fprintBigArray(ostream& fout, int elements_per_line)
{
	int count = 0;
	while (count < num_elements)
	{
		fout << setw(5) << big_array[count];
		count++;
		if (count % elements_per_line == 0)
			fout << endl; 
	}
	fout << endl;
}

void BigArray::fprintSample(ostream& fout,
	int elements_per_line,
	int num_sample_lines)
{
	int last_block_start;
	int count = 0;
	for (int i = 0; i < num_sample_lines; i++)  //define한 num_sample_lines 개수만큼 줄이 출력되게
	{
		for (int j = 0; j < elements_per_line; j++)
		{
			if (count > num_elements)
			{
				fout << endl;
				return;
			}
			fout << setw(10) << big_array[count];
			count++;
		}
		fout << endl;
	}

	if (count < (num_elements - elements_per_line * num_sample_lines))  //남아있는 원소개수가 출력될 원소개수보다 크면
		count = num_elements - elements_per_line * num_sample_lines;  //count를 설정해주고

	fout << endl << " . . . . . " << endl;
	for (int i = 0; i < num_sample_lines; i++) //define한 num_sample_lines 개수만큼 줄이 출력되게
	{
		for (int j = 0; j < elements_per_line; j++)
		{
			if (count > num_elements)
			{
				fout << endl;
				return;
			}
			fout << setw(10)
				<< big_array[count];
			count++;
		}
		fout << endl;
	}
	fout << endl;
}

