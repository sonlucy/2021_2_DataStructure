
#ifndef TA_Entry_H
#define TA_Entry_H
#include "T_Entry.h"
#include <iomanip>
#include <string>
#include <fstream>
enum SortingDirection {INCREASING, DECREASING};

template<typename K, typename V>
class TA_Entry
{
public:
	TA_Entry(int n, string nm); // constructor
	~TA_Entry();  // destructor

	int size() { return num_elements; }
	bool empty() { return num_elements == 0; }
	string getName() { return name; }

	void reserve(int new_capacity);
	void insert(int i, T_Entry<K, V> new_element);
	void remove(int i);
	T_Entry<K, V>& at(int i) { if (isValidIndex(i)) return t_array[i]; }
	void set(int i, T_Entry<K, V>& element) { if (isValidIndex(i)) t_array[i] = element; }

	void fprint(ofstream& fout, int elements_per_line);
	void fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines);
	bool isValidIndex(int i);
	T_Entry<K, V>& operator[](int index) { return t_array[index]; }


	void suffle();
	/*int sequential_search(T_Entry<K, V> search_key);
	int binary_search(T_Entry<K, V> search_key);
	void selection_sort(SortingDirection sd);
	void quick_sort(SortingDirection sd);
	void _quicksort(T_Entry<K, V>* array, int size, int left, int right, SortingDirection sortOrder);
	int _partition(T_Entry<K, V>* array, ins size, int left, int right, int pivotindex, SortingDirection sortOrder);
	*/

protected:

	T_Entry<K, V>* t_array;  ///////T_Entry 배열화
	int num_elements;  //들어있는 이벤트수
	int capacity;  //용량
	string name;
};

template<typename K, typename V>
TA_Entry<K, V>::TA_Entry(int n, string nm)
{
	t_array = (T_Entry<K, V>*) new T_Entry<K, V>[n];  /////////////

	if (t_array == NULL)
	{
		cout << "Error in creation of dynamic array of size (" << capacity << ") !!" << endl;
		exit;
	}
	num_elements = 0;
	capacity = n;  /////////
	name = nm;
}

template<typename K, typename V>
TA_Entry<K, V>::~TA_Entry()
{
	if (t_array != NULL)
	{
		delete[] t_array;
	}
}



template<typename K, typename V>
void TA_Entry<K, V>::reserve(int new_capacity)       ////////////////////////////////////////////
{
	if (capacity >= new_capacity)
		return;
	T_Entry<K, V>* t_newGA = (T_Entry<K, V>*) new T_Entry<K, V>[new_capacity];
	if (t_newGA == NULL)
	{
		cout << "Error in creation of dynamic array of size (" << new_capacity << ") ." << endl;
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


template<typename K, typename V>
void TA_Entry<K, V>::insert(int i, T_Entry<K, V> new_element)
{
	if (num_elements >= capacity)//수용가능한 용량보다 더 크면
	{
		int new_capa;// = capacity * 2;  //2배 확장
		new_capa = ((2 * capacity) > 1) ? (2 * capacity) : 1;
		reserve(new_capa);

		/**T* t_newGA = (T*) new T[new_capacity];
		for (int k = 0; k < num_elements; k++)
		{
			t_newGA[k] = t_array[k];
		}
		delete[]t_array;
		t_array = t_newGA;
		capacity = new_capacity;
	}*/
		if (isValidIndex(i))
		{
			for (int j = num_elements - 1; j >= i; j--)
				t_array[j + 1] = t_array[j]; //shift up elements in one position 

			t_array[i] = new_element;
			num_elements++;
		}
	}
}



template<typename K, typename V>
void TA_Entry<K, V>::remove(int i)  ////////////////////////////////
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
		int new_capa = capacity / 2;
		T_Entry<K, V>* t_newGA = (T_Entry<K, V>*) new T_Entry<K, V>[new_capa+1];
		if (t_newGA == NULL)
		{
			return;
		}

		cout << this->getName() << " reduces capacity to " << setw(3) << new_capa << endl;
		for (int i = 0; i < num_elements; i++)
		{
			t_newGA[i] = t_array[i];
		}
		delete[] t_array;
		t_array = t_newGA;
		capacity = new_capa;
	}
}




template<typename K, typename V>
void TA_Entry<K, V>::fprint(ofstream& fout, int elements_per_line)
{

	int count = 0;
	while (count < num_elements)
	{

		t_array[count].fprint(fout);
		count++;

		if (elements_per_line == 1)
		{
			fout << endl;
			continue;
		}
		else
		{
			fout << "   ";
			if (count % elements_per_line == 0)
				fout << endl;
		}
	}
	fout << endl;


}

template<typename K, typename V>
void TA_Entry<K, V>::fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines)
{
	string T_type;

	int last_block_start;
	int count = 0;

	T_type = typeid(K).name();

	for (int i = 0; i < num_sample_lines; i++)
	{
		for (int j = 0; j < elements_per_line; j++)
		{
			if (count >= num_elements)
			{
				fout << endl;
				return;
			}

			if ((T_type == string("int")) || (T_type == string("double")) || (T_type == string("class std::basic_string<char, struct std::char_traits<char>, classstd::allocator<char> >")))
				fout << setw(10) << t_array[count];
			else
				fout << t_array[count] << "   ";

			count++;
		}
		fout << endl;

		if (count < (num_elements - elements_per_line * num_sample_lines))
			count = num_elements - elements_per_line * num_sample_lines;

		fout << " . . . . . . " << endl;

		for (int i = 0; i < num_sample_lines; i++)
		{
			for (int j = 0; i < elements_per_line; j++)
			{
				if (count >= num_elements)
				{
					fout << endl;
					return;
				}

				if ((T_type == string("int")) || (T_type == string("double")) || (T_type == string("class std::basic_string<char, struct std::char_traits<char>, classstd::allocator<char> >")))
					fout << setw(10) << t_array[count];
				else
				{
					fout << t_array[count] << "    ";
				}


				count++;
			}

			fout << endl;
		}

		fout << endl;
	}
}




template<typename K, typename V>
bool TA_Entry<K, V>::isValidIndex(int index)
{
	if ((index < 0) || (index > num_elements))   ///////////////////
		return false;
	else
		return true;
}

template<typename K, typename V>
void TA_Entry<K, V>::suffle()
{
	int idx_1, idx_2;
	int rand_1, rand_2;
	TA_Entry<K, V> tmp;

	for (int i = 0; i < num_elements; i++)
	{
		rand_1 = rand();
		rand_2 = rand();
		idx_1 = ((rand_1 << 15) | rand_2) % num_elements;

		rand_1 = rand();
		rand_2 = rand();
		idx_2 = ((rand_1 << 15) | rand_2) % num_elements;

		if (idx_1 != idx_2)
		{
			tmp = t_array[idx_1];
			t_array[idx_1] = t_array[idx_2];
			t_array[idx_2] = tmp;
		}
	}
}

#endif
