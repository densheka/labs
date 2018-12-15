#include <iostream>
#include "Circle.h"
#include "Pryamaya.h"
#include "ListArr.h"
#include "ListList.h"
#include "ListBib.h"
#include <string>

using namespace std;



int main() {
	List1<Circle> list;
	Tochki a, b;
	a.x = 0;
	a.y = 0;
	b.x = 2;
	b.y = 0;
	Circle o;
	o.center = a;
	o.d = b;

	Tochki a1, b1;
	a1.x = 0;
	a1.y = 0;
	b1.x = 2;
	b1.y = 0;
	Circle o1;
	o1.center = a1;
	o1.d = b1;

	Tochki a2, b2;
	a2.x = 0;
	a2.y = 0;
	b2.x = 2;
	b2.y = 0;
	Circle o2;
	o2.center = a2;
	o2.d = b2;

	list.pushBack(o);
	list.pushFront(o1);
	list.addElement(o2, 1);
	list.showAll();


}
