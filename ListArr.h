#pragma once
template <typename T>
class List1 {

protected:

	T *dynamicArray;

	int length;

	void Merge_Sort_Rec(T * temp, int left = 0, int right = -1);

	void qsort(int a, int b);

public:

	List1();

	void showAll();
	void pushBack(T value);
	void popBack();
	void pushFront(T value);
	void popFront();
	void addElement(T value, int position);
	void deleteElement(int position);
	int getElement(int position);
	int getIndex(T value);
	void reverse();
	void clear();
	int getSize();
	void insertion_sort();
	void quick_sort();
	void Merge_Sort(int left = 0, int right = -1);
	size_t size, max_size;
};