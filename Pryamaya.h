#pragma once
#include "Figure.h"
#include "Circle.h"

class pryamaya {
public:
	Tochki a, b;
	void Peretin(pryamaya m, pryamaya l);
	void Symetry(Tochki *t, Tochki *l, pryamaya *p);
	Tochki Peretin(pryamaya m, Circle c);
};