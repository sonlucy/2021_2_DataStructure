#ifndef T_ARRAY_H 
#define T_ARRAY_H 
#include <iostream> 
#include <iomanip> 
#include "Date.h" 
#include "Time.h" 
//#include "Student.h"
using namespace std;

enum SortingOrder { INCREASING, DECREASING };
template<typename V>

class T_Array
{
public:
	T_Array(int n, string nm); // constructor 
	~T_Array(); // destructor 

	int size() { return num_elements; }
	bool empty() { return num_elements == 0; }
	string getName() { return name; }

	void insert(int i, V element);  //�ڷ��� V ��ü�� t_array�迭 i��°�� ����
	void insertBack(V element); //�� �ڿ� ����
	int sequential_search(V search_key); //����Ž�� search and return the index; -1 if not found 
	int binary_search(V search_key); // ����Ž�� search and return the index; -1 if not found 
	void selection_sort(string keyName, SortingOrder sortOrder);  //��������

	/* ������ */
	int _partition(V* array, int size, int left, int right, int pivotIndex, string keyName, SortingOrder sortOrder);
	void _quickSort(V* array, int size, int left, int right, string keyName, SortingOrder sortOrder);
	void quick_sort(string keyName, SortingOrder sortOrder);

	/* �������� */
	//void _mergeSort(T* array, T* tmp_array, int left, int right, string keyName, SortingOrder sortOrder);
	//void mergeSort(T* array, int size);
	void mergeSort(string keyName, SortingOrder sortOrder);

	void print(int elements_per_line);
	bool isValidIndex(int i);
	void reserve(int new_capacity);
	void remove(int i);
	void shuffle();
	//TA_string
	V& operator[](int index) { return t_array[index]; }

private:
	void _mergeSort(V* array, V* tmp_array, int left, int right, string keyName, SortingOrder sortOrder);
	V* t_array;
	int num_elements;
	int capacity;
	string name;
};


template<typename V>
T_Array<V>::T_Array(int new_capacity, string nm) // constructor 
{
	t_array = /*(T*)*/ new V[new_capacity];

	if (t_array == NULL)
	{
		cout << "Error in creation of dynamic array of size (" << new_capacity << ") !!" << endl;
		exit;
	}
	capacity = new_capacity;
	num_elements = 0;
	name = nm;
}

template<typename V>
T_Array<V>::~T_Array() // destructor 
{
	/*if (t_array != NULL)
		delete[] t_array;*/
}

template<typename V>
bool T_Array<V>::isValidIndex(int index)
{
	if ((index < 0) || (index > num_elements))
		return false;
	else
		return true;
}

template<typename V>
void T_Array<V>::insert(int i, V new_element)
{
	if (num_elements >= capacity)//���밡���� �뷮���� �� ũ��
	{
		int new_capacity = capacity * 2;  //2�� Ȯ��
		V* t_newGA = (V*) new V[new_capacity];
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
template<typename V>
void T_Array<V>::insertBack(V element)
{
	if (num_elements >= capacity)//���밡���� �뷮���� �� ũ��
	{
		int new_capacity = capacity * 2;  //2�� Ȯ��
		V* t_newGA = (V*) new V[new_capacity];
		for (int k = 0; k < num_elements; k++)
		{
			t_newGA[k] = t_array[k];
		}
		delete[]t_array;
		t_array = t_newGA;
		capacity = new_capacity;
	}

	t_array[num_elements] = element;

	num_elements++;
}

template<typename V>
int T_Array<V>::sequential_search(V search_key)
{
	int index;
	string keytype;

	void* y;  ////////////
	y = &search_key;  //////////////////

	keytype = typeid(V).name();
	if (keytype == "int") // student_ID 
	{
		for (int index = 0; index < num_elements; index++)
		{
			if (t_array[index].getIntKey() == search_key)
				return index;
		}
	}
	///////////////////////////////////////////////////////////////
	/*else if (keytype == "class Time")
	{
		for (int index = 0; index < num_elements; index++)
		{
			if (t_array[index].getArrivalTime() == *(Time*)y)
				return index;
		}
	}*/
	else if (keytype == "double")
	{
		for (int index = 0; index < num_elements; index++)
		{
			if (t_array[index].getDoubleKey() == *(double*)y)
				return index;
		}
	}
	else if (keytype == "class Date")
	{
		for (int index = 0; index < num_elements; index++)
		{
			if (t_array[index].getDoB() == *(Date*)y)
				return index;
		}
	}
	else
	{
		for (int index = 0; index < num_elements; index++)
		{
			if (t_array[index].getName() == *(string*)y)
				return index;
		}
	}
	return -1;
}

template<typename V>
int T_Array<V>::binary_search(V search_key)
{
	int low, mid, high;
	int loop = 1;

	low = 0;
	high = num_elements - 1;
	while (low <= high)
	{
		cout << setw(2) << loop << "-th loop: current search range ["
			<< setw(3) << low << ", " << setw(3) << high << "]" << endl;
		mid = (low + high) / 2;
		if (t_array[mid] == search_key)
			return mid;
		else if (t_array[mid] > search_key)
			high = mid - 1;
		else
			low = mid + 1;
		loop++;
	}
}

template<typename V>
void T_Array<V>::selection_sort(string keyName, SortingOrder sortOrder)
{
	int index_min, index_max; // index of the element with minimum value
	V tempElement;
	V minKey, maxKey, key;

	for (int i = 0; i < num_elements - 1; i++)
	{
		if (sortOrder == INCREASING)  //��������
		{
			index_min = i;
			t_array[i].getKey(keyName, &key);  //i��° ���Ҹ� �츮�� �����ϴ� keyName�� key�� �ּ� ��ġ�� ���� (call-by-pointer)
			minKey = (V)key;  //KŸ������ ����ȯ���� minKey�� ����

			for (int j = i + 1; j < num_elements; j++)
			{
				t_array[j].getKey(keyName, &key);  //j��° Ű �о����

				if ((V)key < minKey)  //�о�� Ű ����ȯ �� minKey�� ��
				{
					index_min = j;
					minKey = (V)key; //
				}

			}
			if (index_min != i) // �� ���� ���� ������ swap
			{
				tempElement = t_array[index_min];
				t_array[index_min] = t_array[i];
				t_array[i] = tempElement;
			}
		}
		else  //��������
		{
			index_max = i;
			t_array[i].getKey(keyName, &key);
			maxKey = (V)key;  ///
			for (int j = i + 1; j < num_elements; j++)
			{
				t_array[j].getKey(keyName, &key);  //
				if ((V)key > maxKey)
				{
					index_max = j;
					maxKey = (V)key;
				}
			}
			if (index_max != i) // �� ���� ���� ������ swap
			{
				tempElement = t_array[index_max];
				t_array[index_max] = t_array[i];
				t_array[i] = tempElement;
			}
		}
	} // end for


}

template<typename V>
void T_Array<V>::reserve(int new_capacity)        ////////////////////////////////////////////
{
	if (capacity >= new_capacity)
		return;
	V* t_newGA = (V*) new V[new_capacity];
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

template<typename V>
void T_Array<V>::remove(int i)  ////////////////////////////////
{
	if (isValidIndex(i))
	{
		for (int j = i + 1; j < num_elements; j++)
		{
			t_array[j - 1] = t_array[j];
		}
		num_elements--;
	}

	if (num_elements < (capacity / 2))
	{
		int new_capacity = capacity / 2;
		V* t_newGA = (V*) new V[new_capacity];
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

template<typename V>
void T_Array<V>::shuffle()  //////////////////////
{
	srand(time(NULL));
	int index1, index2, rand_1, rand_2;
	//<V> temp;
	V temp;

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


template<typename V>
void T_Array<V>::print(int elements_per_line)
{
	int count = 0;
	while (count < num_elements)
	{
		for (int i = 0; i < elements_per_line; i++)
		{
			cout << t_array[count] << " ";
			count++;
			if (count % elements_per_line == 0)
				cout << endl;
		}
	}
	cout << endl;
}



template<typename V>
int T_Array<V>::_partition(V* array, int size, int left, int right, int pivotIndex, string keyName, SortingOrder sortOrder)
{
	V pivotValue, temp; // pivot value
	V key, key_min;  /////////////
	int newPI; // new pivot index

	// �Ǻ� ���Ҹ� �� ������ �ڸ��� ��ġ 
	pivotValue = array[pivotIndex];
	array[pivotIndex] = array[right];
	array[right] = pivotValue; // Move pivot to array[right]
	newPI = left; // newPI is the index that points the position 

	// where pivot element will be finally re-located
	for (int i = left; i <= (right - 1); i++)
	{
		array[i].getKey(keyName, &key_min);   /////////////////
		if (sortOrder == INCREASING) // �������� �����̸�
		{
			pivotValue.getKey(keyName, &key); ///////////////
			//if (array[i] <= pivotValue) // T must provide operator<=() overloading !!
			if (key_min < key)
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;

				newPI = newPI + 1;
				// note: all elements in left of index newPI are equal or smaller than pivot_value
			}
		}
		else // �������� ����
		{
			pivotValue.getKey(keyName, &key);  /////////////
			//if (array[i] > pivotValue) // T must provide operator>() overloading !!
			if (key_min > key)
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

template<typename V>
void T_Array<V>::_quickSort(V* array, int size, int left, int right, string keyName, SortingOrder sortOrder)
{
	int pI, newPI; // pivot index
	if (left >= right)
	{
		return;
	}
	else
	{ //select a pI (pivotIndex) in the range left �� pI �� right
		pI = (left + right) / 2;
	}
	newPI = _partition(array, size, left, right, pI, keyName, sortOrder);

	if (left < (newPI - 1))
	{
		_quickSort(array, size, left, newPI - 1, keyName, sortOrder);
		// recursively sort elements on the left of pivotNewIndex
	}
	if ((newPI + 1) < right)
	{
		_quickSort(array, size, newPI + 1, right, keyName, sortOrder);
		// recursively sort elements on the right of pivotNewIndex
	}
}

template<typename V>
void T_Array<V>::quick_sort(string keyName, SortingOrder sortOrder)
{
	int pI, newPI; // pivot index
	_quickSort(this->t_array, num_elements, 0, num_elements - 1, keyName, sortOrder);
}




template<typename V>
void T_Array<V>::_mergeSort(V* array, V* tmp_array, int left, int right, string keyName, SortingOrder sortOrder)
{
	//K l, r;
	V key_i, key_j;

	if (left >= right)
		return;
	//else
	//����
	int i, j, k, mid = (left + right) / 2;
	_mergeSort(array, tmp_array, left, mid, keyName, sortOrder);     //����Լ� ȣ��
	_mergeSort(array, tmp_array, mid + 1, right, keyName, sortOrder);


	/* merge step 1 : copy 2nd half to tmp_array[] */
	for (i = mid; i >= left; i--)  // <-mid
		tmp_array[i] = array[i];
	for (j = 1; j <= right - mid; j++)  // <-right
		tmp_array[right - j + 1] = array[j + mid];

	/* merge step 2 : merge sub-arrays back to array[] */
	for (i = left, j = right, k = left; k <= right; k++)
	{
		/* �ش� keyName�� �ڷ����� �ش��ϴ� ������ ����� key_i, key_j�� ����� */
		tmp_array[i].getKey(keyName, &key_i);
		tmp_array[j].getKey(keyName, &key_j);
		//if (tmp_array[i] < tmp_array[j])
		if (sortOrder == INCREASING)
		{
			if (key_i < key_j)  // ������ ������
				array[k] = tmp_array[i++];   //���� �ְ�
			else
				array[k] = tmp_array[j--];  //�ƴϸ� ������ �ְ�
		}
		else
		{
			if (key_i > key_j)  // �������� ������
				array[k] = tmp_array[i++];   //���� �ְ�
			else
				array[k] = tmp_array[j--];  //�ƴϸ� ������ �ְ�
		}
	}

	/* for debugging of merge_sort() */
/*#ifdef DEBUG_MERGESORT
	printf("After merging (left=%d, mid=%d, right=%d):\n", left, mid, right);
	printf("tempA: ");
	for (int i = left; i <= right; i++)
		printf("%5d", tmp_array[i]);
	printf("\n");
	printf(" A: ");
	for (int i = left; i <= right; i++)
		printf("%5d", array[i]);
	printf("\n");
#endif*/
}



template<typename V>
void T_Array<V>::mergeSort(string keyName, SortingOrder sortOrder)
{
	V* tmp_array = new V[num_elements]; //= (T*)calloc(num_elements, sizeof(T));
	if (tmp_array == NULL)
	{
		printf("Error in creation of tmp_array (size = %d) in mergeSort() !!!\n");
		exit;
	}
	//void _mergeSort(T * array, T * tmp_array, int left, int right, string keyName, SortingOrder sortOrder);
	_mergeSort(this->t_array, tmp_array, 0, num_elements - 1, keyName, sortOrder);  ////
}

#endif
