//cписок на массиве
#include <iostream>
#include <vector>
#include <string>
#include "ListArr.h"


using namespace std;


template <typename T>
List1<T>::List1()
{

	dynamicArray = new T[0];

	length = 0;

}

template <typename T>
void List1<T>::showAll()

{

	for (int i = 0; i < length; ++i)

	{

		cout << dynamicArray[i] << ' ';

	}

	cout << '\n';

}

template <typename T>
void List1<T>::pushBack(T value)

{

	int *newArray = new int[length + 1];



	for (int i = 0; i < length; ++i)

	{

		newArray[i] = dynamicArray[i];

	}

	newArray[length] = value;



	delete[] dynamicArray;



	dynamicArray = newArray;

	++length;

}

template <typename T>
void List1<T>::popBack()

{

	if (length != 0)

	{

		T *newArray = new T[length - 1];



		for (int i = 0; i < length - 1; ++i)

		{

			newArray[i] = dynamicArray[i];

		}



		delete[] dynamicArray;



		dynamicArray = newArray;

		--length;

	}

}

template <typename T>
void List1<T>::pushFront(T value)

{

	T *newArray = new T[length + 1];



	for (int i = 0; i < length; ++i)

	{

		newArray[i + 1] = dynamicArray[i];

	}

	newArray[0] = value;



	delete[] dynamicArray;



	dynamicArray = newArray;

	++length;

}

template <typename T>
void List1<T>::popFront()

{

	if (length != 0)

	{

		T *newArray = new T[length - 1];



		for (int i = 0; i < length - 1; ++i)

		{

			newArray[i] = dynamicArray[i + 1];

		}



		delete[] dynamicArray;



		dynamicArray = newArray;

		--length;

	}

}

template <typename T>
void List1<T>::addElement(T value, int position)

{

	if (position < 0 || position > length)

	{

		return;

	}

	else if (position == 0)

	{

		pushFront(value);

	}

	else if (position == length)

	{

		pushBack(value);

	}

	else

	{

		T *newArray = new T[length + 1];



		for (int i = 0; i < position; ++i)

		{

			newArray[i] = dynamicArray[i];

		}

		newArray[position] = value;

		for (int i = position; i < length; ++i)

		{

			newArray[i + 1] = dynamicArray[i];

		}

		delete[] dynamicArray;



		dynamicArray = newArray;

		++length;

	}

}


template <typename T>
void List1<T>::deleteElement(int position)

{

	if (position < 0 || position >= length)

	{

		return;

	}

	else if (position == 0)

	{

		popFront();

	}

	else if (position == length - 1)

	{

		popBack();

	}

	else

	{

		T *newArray = new T[length - 1];



		for (int i = 0; i < position; ++i)

		{

			newArray[i] = dynamicArray[i];

		}

		for (int i = position; i < length - 1; ++i)

		{

			newArray[i] = dynamicArray[i + 1];

		}

		delete[] dynamicArray;



		dynamicArray = newArray;

		--length;

	}

}

template <typename T>
int List1<T>::getElement(int position)

{

	if (position < 0 || position >= length)

	{

		return 0;

	}

	else

	{

		return dynamicArray[position];

	}

}

template <typename T>
int List1<T>::getIndex(T value)

{

	for (int i = 0; i < length; ++i)

	{

		if (dynamicArray[i] == value)

		{

			return i;

		}

	}



	return -1;

}

template <typename T>
void List1<T>::reverse()

{

	for (int i = 0; i < length / 2; ++i)

	{

		swap(dynamicArray[i], dynamicArray[length - 1 - i]);

	}

}

template <typename T>
void List1<T>::clear()

{

	delete[] dynamicArray;

	dynamicArray = new int[0];

	length = 0;

}

template <typename T>
int List1<T>::getSize()

{

	return length;

}

template <typename T>
void List1<T>::insertion_sort() {

	for (int i = 1; i < length; i++)
		for (int j = i; j > 0 && dynamicArray[j - 1] > dynamicArray[j]; j--)
			swap(dynamicArray[j - 1], dynamicArray[j]);
}

template <typename T>
void List1<T>::quick_sort() {

	qsort(0, length - 1);

}

template <typename T>
void List1<T>::qsort(int a, int b) {

	int l = a, r = b;

	int piv = dynamicArray[(l + r) / 2];

	while (l <= r)

	{

		while (dynamicArray[l] < piv)

			l++;

		while (dynamicArray[r] > piv)

			r--;

		if (l <= r)

			swap(dynamicArray[l++], dynamicArray[r--]);

	}

	if (a < r)

		qsort(a, r);

	if (b > l)

		qsort(l, b);
}

template <typename T>
void List1<T>::Merge_Sort_Rec(T * temp, int left, int right) {

	if (right <= -1 || right >= sizeof(dynamicArray)) {

		right = sizeof(dynamicArray) - 1;

	}

	if (left < 0 || left >= sizeof(dynamicArray)) {

		left = 0;

	}

	//exit

	if (left == right) {

		return;

	}

	//rec

	Merge_Sort_Rec(temp, left, (right - left) / 2 + left); Merge_Sort_Rec(temp, (right - left) / 2 + 1 + left, right);



	//init

	int i_1 = left, i_2 = (right - left) / 2 + 1 + left; int i = left;


	for (int i = left; i <= right; i++) temp[i] = dynamicArray[i];



	//main loop

	while (true) {

		if (i_1 > (right - left) / 2 + left && i_2 > (right - left) / 2 + 1 + left) break;

		if (i_1 <= (right - left) / 2 + left && (temp[i_1] < temp[i_2])) {

			dynamicArray[i] = temp[i_1];

			i++;

			i_1++;

		}

		else {

			dynamicArray[i] = temp[i_2];

			i++;

			i_2++;

		}

	}

}

template <typename T>
void List1<T>::Merge_Sort(int left, int right) {

	T * temp = new T[sizeof(dynamicArray)];

	Merge_Sort_Rec(temp, left, right);

	delete[] temp;

}
