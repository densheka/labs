#pragma once
//список на списках
#include "ListList.h"

using namespace std;


template <typename T>
Node<T> *List3<T>::getNode(int position)

{

	Node<T> *node = head;

	for (int i = 0; i < position; ++i)

	{

		node = node->next;

	}

	return node;

}

template <typename T>
List3<T>::List3() {

	length = 0;

}

template <typename T>
void List3<T>::showAll()

{

	Node<T> *node = head;

	for (int i = 0; i < length; ++i)

	{

		cout << node->value << ' ';

		node = node->next;

	}

	cout << '\n';

}

template <typename T>
void List3<T>::pushBack(T value)
{

	Node<T>  *newNode = new Node<T>(value);

	if (length == 0)

	{

		head = newNode;

		tail = newNode;

	}

	else

	{

		tail->next = newNode;

		tail = newNode;

	}

	++length;

}

template <typename T>
void List3<T>::popBack()

{

	if (length != 0)

	{

		Node<T> *node = getNode(length - 2);

		tail = node;

		node = node->next;

		tail->next = nullptr;

		delete node;

		--length;

	}

}

template <typename T>
void List3<T>::pushFront(T value)

{

	Node<T> *newNode = new Node<T>(value);

	if (length == 0)

	{

		head = newNode;

		tail = newNode;

	}

	else

	{

		newNode->next = head;

		head = newNode;

	}

	++length;

}

template <typename T>
void List3<T>::popFront()

{

	if (length != 0)

	{

		Node<T> *node = head;

		head = head->next;

		delete node;

		--length;

	}

}

template <typename T>
void List3<T>::addElement(T value, int position)

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

		Node<T> *node = getNode(position - 1);

		Node<T> *newNode = new Node<T>(value);

		newNode->next = node->next;

		node->next = newNode;

		++length;

	}

}

template <typename T>
void List3<T>::deleteElement(int position)

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

		Node<T> *node = getNode(position - 1);

		Node<T> *newNode;

		newNode = node->next;

		node->next = node->next->next;

		delete newNode;

		--length;

	}

}



template <typename T>
int& List3<T>::getElement(int position)

{

	if (position < 0 || position >= length)

	{

		cout << "element [" << position << "] not found" << endl;

		cout << "press ENTER to finish . . .";

		cin.get();

		exit(2);

	}

	else

	{

		Node<T> *node = getNode(position);

		return node->value;

	}

}


template <typename T>
int List3<T>::getIndex(T value)

{

	int index = 0;



	Node<T> *node = head;

	while (node->value != value)

	{

		if (node->next == nullptr)

		{

			return -1;

		}

		node = node->next;

		++index;

	}

	return index;

}


template <typename T>
void List3<T>::reverse()

{

	Node<T> *nodeLast = head;

	Node<T> *nodeNow = head;

	Node<T> *nodeNext = head->next;

	nodeLast->next = nullptr;

	tail = nodeLast;

	nodeNow = nodeNext;

	nodeNext = nodeNext->next;

	for (int i = 1; i < length - 1; ++i)

	{

		nodeNow->next = nodeLast;

		nodeLast = nodeNow;

		nodeNow = nodeNext;

		nodeNext = nodeNext->next;

	}

	nodeNow->next = nodeLast;

	head = nodeNow;

}

template <typename T>
void List3<T>::clear()

{

	while (length > 0)

	{

		popFront();

	}

}

template <typename T>
int List3<T>::getSize()
{

	return length;

}

template <typename T>
void List3<T>::insertion_sort() {

	for (int i = 1; i < length; i++)
		for (int j = i; j > 0 && this->getElement(j - 1) > this->getElement(j); j--)
			swap(this->getElement(j - 1), this->getElement(j));
}

template <typename T>
void List3<T>::quick_sort() {

	qsort(0, length - 1);

}

template <typename T>
void List3<T>::qsort(int a, int b) {

	int l = a, r = b;

	auto piv = this->getElement(l + r / 2);

	while (l <= r)

	{

		while (this->getElement(l) < piv)

			l++;

		while (this->getElement(r) > piv)

			r--;

		if (l <= r)

			swap(this->getElement(l++), this->getElement(r--));

	}

	if (a < r)

		qsort(a, r);

	if (b > l)

		qsort(l, b);
}

template <typename T>
void List3<T>::Merge_Sort_Rec(T * a, T * temp, int l, int left, int right) {

	if (right <= -1 || right >= l) {

		right = l - 1;

	}

	if (left < 0 || left >= l) {

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


	for (int i = left; i <= right; i++) temp[i] = a[i];



	//main loop

	while (true) {

		if (i_1 > (right - left) / 2 + left && i_2 > (right - left) / 2 + 1 + left) break;

		if (i_1 <= (right - left) / 2 + left && (temp[i_1] < temp[i_2])) {

			a[i] = temp[i_1];

			i++;

			i_1++;

		}

		else {

			a[i] = temp[i_2];

			i++;

			i_2++;

		}

	}

}

template <typename T>
void List3<T>::Merge_Sort(T * a, int left, int right) {
	int l = this->size;
	T * temp = new T[l];

	Merge_Sort_Rec(a, temp, left, right, l);

	delete[] temp;

}

