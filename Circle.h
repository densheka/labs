#pragma once

#include <cmath>

#include "Figure.h"



class Circle : public Tochki
{
public: 

	Tochki Invert(Circle c, Tochki t);
	Tochki center, d;
	Tochki Peretin(Circle k, Circle c);
	
	double radius();
	double square();
	
	
};