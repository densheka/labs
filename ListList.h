#pragma once
#include <iostream>
#include <string>
#include <vector>

template <typename T>
struct Node

{

	T value;

	Node *next = nullptr;

	Node(T value) : value(value) {}

};


template <typename T>
class List3
{

protected:

	Node *head = nullptr;

	Node *tail = nullptr;

	int length;



	Node *getNode(int position);




public:

	List3();

	void showAll();
	void pushBack(T value);
	void popBack();
	void pushFront(T value);
	void popFront();
	void addElement(T value, int position);
	void deleteElement(int position);
	int& getElement(int position);
	int getIndex(T value);
	void reverse();
	void clear();
	int getSize();
	void insertion_sort();
	void qsort(int a, int b);
	void quick_sort();
	void Merge_Sort_Rec(T * a, T * temp, int l, int left = 0, int right = -1);
	void Merge_Sort(T * a, int left = 0, int right = -1);


	int& operator[](int pos) {

		int i = 0;

		if (size == 0) {

			Node * nd = new Node(NULL);

			head = nd;

			tail = nd;

			return nd->value;

		}

		if (abs(pos) >= size) {

			cout << "element [" << pos << "] not found" << endl;

			cout << "press ENTER to finish . . .";

			cin.get();

			exit(2);

		}



		if (pos < 0) pos = size - abs(pos);

		Node * temp = head;

		while (i < pos) {

			temp = temp->next;

			i++;

		}

		return temp->value;

	}

	size_t size, max_size;
};
