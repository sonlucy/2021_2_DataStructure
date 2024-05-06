#ifndef T_ARRAY_H
#define T_ARRAY_H
#include <string>

#include <iostream> 
#include <iomanip> 
#include "Date.h" 
#include "Time.h" 
//#include "Student.h"
using namespace std;

enum SortingOrder { INCREASING, DECREASING };

template<typename T>
class T_Array
{
public:
	T_Array(int n, string nm); // constructor
	~T_Array(); // destructor

	string getName() { return name; }
	
	void reserve(int new_capacity);
	void insert(int i, T element);  //i위치에 원소 넣기
	void remove(int i);  //i번째 원소 삭제

	T& at(int i);  //i번째 원소의 주소를 반환해 값을 읽거나 변경할 수 있게 해주는 함수
	void set(int i, T& element);  //i번째 원소를 지정된 element값으로 변경
	
	void shuffle();

	/* 도착시간에 따라 정렬 */
	void selection_sort(SortingOrder sortOrder = INCREASING);   //선택정렬
	/*퀵정렬 관련 함수*/
	void quick_sort(SortingOrder sortOrder = INCREASING);
	void _quickSort(T* array, int size, int left, int right, SortingOrder sortOrder = INCREASING);
	int _partition(T* array, int size, int left, int right, int pivotIndex, SortingOrder sortOrder);

	void fprint(ofstream& fout, int elements_per_line);

	bool isValidIndex(int i);  //유효한 인덱스인지
	T& operator[](int index) { return t_array[index]; }
private:
	T* t_array;
	int num_elements;
	int capacity;
	string name;
};

template<typename T>
T_Array<T>::T_Array(int n, string nm) // constructor 
{
	t_array = /*(T*)*/ new T[n];

	if (t_array == NULL)
	{
		cout << "Error in creation of dynamic array of size (" << n << ") !!" << endl;
		exit;
	}
	capacity = n;
	num_elements = 0;
	name = nm;
}

template<typename T>
T_Array<T>::~T_Array() // destructor 
{
	/*if (t_array != NULL)
		delete[] t_array;*/
}

template<typename T>
bool T_Array<T>::isValidIndex(int index)
{
	if ((index < 0) || (index > num_elements))
		return false;
	else
		return true;
}

template<typename T>
void T_Array<T>::insert(int i, T new_element)
{
	if (num_elements >= capacity)//수용가능한 용량보다 더 크면
	{
		int new_capacity = capacity * 2;  //2배 확장
		T* t_newGA = (T*) new T[new_capacity];
		for (int k = 0; k < num_elements; k++)
		{
			t_newGA[k] = t_array[k];
		}
		delete[]t_array;
		t_array = t_newGA;
		capacity = new_capacity;
	}
	if (isValidIndex(i))
	{
		for (int j = num_elements - 1; j >= i; j--)
			t_array[j + 1] = t_array[j]; //shift up elements in one position 
		t_array[i] = new_element;
		num_elements++;
	}
}


template<typename T>
void T_Array<T>::selection_sort(SortingOrder sortOrder)  //도착시간 기준으로 정렬
{

	int index_min, index_max; // index of the element with minimum value
	T minValue, maxValue, tempElement;

	for (int i = 0; i < num_elements - 1; i++)
	{
		if (sortOrder == INCREASING)  //오름차순
		{
			index_min = i;
			minValue = t_array[i];  ////////////
			for (int j = i + 1; j < num_elements; j++)
			{

				if (t_array[j]  < minValue)  
				{
					index_min = j;
					minValue = t_array[j];
				}

			}
			if (index_min != i) // 더 작은 원소 있으면 swap
			{
				tempElement = t_array[index_min];
				t_array[index_min] = t_array[i];
				t_array[i] = tempElement;
			}
		}
		else  //내림차순
		{
			index_min = i;
			minValue = t_array[i];
			for (int j = i + 1; j < num_elements; j++)
			{

				if (t_array[j] > minValue)  
				{
					index_min = j;
					minValue = t_array[j];
				}

			}
			if (index_min != i) // 더 작은 원소 있으면 swap
			{
				tempElement = t_array[index_min];
				t_array[index_min] = t_array[i];
				t_array[i] = tempElement;
			}
		}
	} // end for


}

template<typename T>
void T_Array<T>::reserve(int new_capacity)
{
	if (capacity >= new_capacity)
		return;
	T* t_newGA = (T*) new T[new_capacity];
	if (t_newGA == NULL)
	{
		cout << "Error in creation of dynamic array of size (";
		cout << new_capacity << ") ." << endl;
		exit;
	}

	cout << this->getName() << " expands capacity to " << new_capacity << endl;
	for (int i = 0; i < num_elements; i++)
	{
		t_newGA[i] = t_array[i];
	}
	delete[] t_array;
	t_array = t_newGA;
	capacity = new_capacity;

}

template<typename T>
void T_Array<T>::remove(int i)
{
	if (isValidIndex(i))
	{
		for (int j = i + 1; j < num_elements; j++)
		{
			t_array[j - 1] = t_array[j];  //i+1번째 이후 원소들을 한칸씩 앞으로
		}
		num_elements--;
	}

	if (num_elements < (capacity / 2))
	{
		int new_capacity = capacity / 2;
		T *t_newGA = ( T* ) new T[new_capacity];
		if (t_newGA == NULL)
		{
			return;
		}

		cout << this->getName() << " reduces capacity to " << new_capacity << endl;
		for (int i = 0; i < num_elements; i++)
		{
			t_newGA[i] = t_array[i];
		}
		delete[] t_array;
		t_array = t_newGA;
		capacity = new_capacity;
	}
}

template<typename T>
void T_Array<T>::shuffle()
{
	srand(time(NULL));
	int index1, index2, rand_1, rand_2;
	T temp; 

	for (int i = 0; i < num_elements; i++)
	{
		rand_1 = rand();
		rand_2 = rand();
		index1 = ((rand_1 << 15) | rand_2) % num_elements;

		rand_1 = rand();
		rand_2 = rand();
		index2 = ((rand_1 << 15) | rand_2) % num_elements;

		temp = t_array[index1];
		t_array[index1] = t_array[index2];
		t_array[index2] = temp;
	}
}


template<typename T>
void T_Array<T>::fprint(ofstream &fout, int elements_per_line)
{
	int count = 0;
	while (count < num_elements)
	{
		for (int i = 0; i < elements_per_line; i++)
		{
			fout << t_array[count] << " ";
			count++;
			if (count % elements_per_line == 0)
				fout << endl;
		}
	}
	fout << endl ;
}



template<typename T>
int T_Array<T>::_partition(T* array, int size, int left, int right, int pivotIndex,  SortingOrder sortOrder)
{
	T pivotValue, temp; // pivot value
	int newPI; // new pivot index

	// 피봇 원소를 맨 오른쪽 자리에 위치 
	pivotValue = array[pivotIndex];
	array[pivotIndex] = array[right];
	array[right] = pivotValue; // Move pivot to array[right]
	newPI = left; // newPI is the index that points the position 

	// where pivot element will be finally re-located
	for (int i = left; i <= (right - 1); i++)
	{
		
		if (sortOrder == INCREASING) // 오름차순 정렬이면
		{
			
			if (array[i] <= pivotValue) // T must provide operator<=() overloading !!
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;

				newPI = newPI + 1;
				// note: all elements in left of index newPI are equal or smaller than pivot_value
			}
		}
		else // 내림차순 정렬
		{
			if (array[i] > pivotValue) // T must provide operator>() overloading !!
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;

				newPI = newPI + 1;
				// note: all elements in left of index newPI are greater than pivot_value
			}
		}
	} // end for

	// swap 
	temp = array[newPI];
	array[newPI] = array[right];
	array[right] = temp;

	return newPI;
}

template<typename T>
void T_Array<T>::_quickSort(T* array, int size, int left, int right, SortingOrder sortOrder)
{
	int pI, newPI; // pivot index
	if (left >= right)
	{
		return;
	}
	else
	{ //select a pI (pivotIndex) in the range left ≤ pI ≤ right
		pI = (left + right) / 2;
	}
	newPI = _partition(array, size, left, right, pI,  sortOrder);

	if (left < (newPI - 1))
	{
		_quickSort(array, size, left, newPI - 1,  sortOrder);
		// recursively sort elements on the left of pivotNewIndex
	}
	if ((newPI + 1) < right)
	{
		_quickSort(array, size, newPI + 1, right,  sortOrder);
		// recursively sort elements on the right of pivotNewIndex
	}
}

template<typename T>
void T_Array<T>::quick_sort( SortingOrder sortOrder)
{
	int pI, newPI; // pivot index
	_quickSort(this->t_array, num_elements, 0, num_elements - 1, sortOrder);
}


template<typename T>
T& T_Array<T>:: at(int i)  //i번째 원소의 주소를 반환해 값을 읽거나 변경할 수 있게 해주는 함수
{
	if (isValidIndex(i))
	{
		return t_array[i];
	}
}

template<typename T>
void T_Array<T>::set(int i, T& element)  //i번째 원소를 지정된 element값으로 변경
{
	if (isValidIndex(i))
	{
		t_array[i] = element;
	}
}



#endif
