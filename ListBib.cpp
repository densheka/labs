//список на библ.
#include "ListBib.h"

using namespace std;

template <typename T>

List2<T>::List2() {}

template <typename T>

void List2<T>::showAll()

{

	for (auto i = list.begin(); i != list.end(); ++i)

	{

		cout << *i << ' ';

	}

	cout << '\n';

}


template<typename T>

void List2<T>::pushBack(T value)

{

	list.push_back(value);

}



template<typename T>

void List2<T>::popBack()

{

	list.pop_back();

}



template<typename T>

void List2<T>::pushFront(T value)

{

	list.push_front(value);

}



template<typename T>

void List2<T>::popFront()

{

	list.pop_front();

}

template <typename T>

void List2<T>::addElement(T value, int position)

{

	if (position < 0 || position > list.size())

	{

		return;

	}

	else if (position == 0)

	{

		list.push_front(value);

	}

	else if (position == list.size())

	{

		list.push_back(value);

	}

	else

	{

		auto i = list.begin();

		for (int j = 0; j < position; ++j)

		{

			++i;

		}

		list.insert(i, value);

	}

}

template <typename T>

void List2<T>::deleteElement(int position)

{

	if (position < 0 || position >= list.size())

	{

		return;

	}

	else if (position == 0)

	{

		list.pop_front();

	}

	else if (position == list.size() - 1)

	{

		list.pop_back();

	}

	else

	{

		auto i = list.begin();

		for (int j = 0; j < position; ++j)

		{

			++i;

		}

		list.erase(i);

	}

}

template <typename T>

int& List2<T>::getElement(int position)

{

	if (position < 0 || position >= list.size())

	{

		cout << "element [" << position << "] not found" << endl;

		cout << "press ENTER to finish . . .";

		cin.get();

		exit(2);

	}

	else

	{

		auto i = list.begin();

		for (int j = 0; j < position; ++j)

		{

			++i;

		}

		return *i;

	}

}

template <typename T>

int List2<T>::getIndex(T value)

{

	int index = 0;



	for (auto i = list.begin(); i != list.end(); ++i)

	{

		if (*i == value)

		{

			return index;

		}

		++index;

	}

	return -1;

}

template<typename T>

void List2<T>::reverse()

{

	list.reverse();

}



template<typename T>

void List2<T>::clear()

{

	list.clear();

}

template<typename T>

int List2<T>::getSize()

{

	return int(list.size());

}

template <typename T>

void List2<T>::insertion_sort() {

	for (int i = 1; i < list.size(); i++)
		for (int j = i; j > 0 && this->getElement(j - 1) > this->getElement(j); j--)
			swap(this->getElement(j - 1), this->getElement(j));
}

template <typename T>

void List2<T>::quick_sort() {

	qsort(0, list.size() - 1);

}

template <typename T>

void List2<T>::qsort(int b, int e) {

	int l = b, r = e;

	int piv = getElement((l + r) / 2);

	while (l <= r)

	{

		while (getElement(l) < piv)

			l++;

		while (getElement(r) > piv)

			r--;

		if (l <= r)

			swap(getElement(l++), getElement(r--));

	}

	if (b < r)

		qsort(b, r);

	if (e > l)

		qsort(l, e);
}

template <typename T>

void List2<T>::Merge_Sort_Rec(T & a, int * temp, int left, int right) {

	if (right <= -1 || right >= getElement(size)) {

		right = getElement(size) - 1;

	}

	if (left < 0 || left >= getElement(size)) {

		left = 0;

	}

	//exit

	if (left == right) {

		return;

	}

	//rec

	Merge_Sort_Rec(a, temp, left, (right - left) / 2 + left); Merge_Sort_Rec(a, temp, (right - left) / 2 + 1 + left, right);



	//init

	int i_1 = left, i_2 = (right - left) / 2 + 1 + left; int i = left;



	for (int i = left; i <= right; i++) temp[i] = getElement(i);



	//main loop

	while (true) {

		if (i_1 > (right - left) / 2 + left && i_2 > (right - left) / 2 + 1 + left) break;

		if (i_1 <= (right - left) / 2 + left && (temp[i_1] < temp[i_2])) {

			getElement(i) = temp[i_1];

			i++;

			i_1++;

		}

		else {

			getElement(i) = temp[i_2];

			i++;

			i_2++;

		}

	}

}

template <typename T>

void List2<T>::Merge_Sort(T & a, int left, int right) {

	int * temp = new int[getElement(size)];

	Merge_Sort_Rec(a, temp, left, right);

	delete[] temp;

}
