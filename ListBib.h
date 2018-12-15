#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <string>


template <typename T>
class List2{


	list <T> list;

public:

	List2();



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
	void Merge_Sort_Rec(T & a, int * temp, int left = 0, int right = -1);
	void Merge_Sort(T & a, int left = 0, int right = -1);

	size_t size, max_size;

};