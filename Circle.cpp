#include "Circle.h"
#include "ListBib.cpp"

double Circle::radius() {
	double r = sqrt(pow(center.x - d.x, 2) + pow(center.y - d.y, 2));
	return r;
}

double Circle::square() {
	return atan(1) * 4 * pow(radius(), 2);
}

Tochki Circle::Invert(Circle c, Tochki t) {
	Tochki t1;
	double m = t.x - c.center.x;
	double l = t.y - c.center.y;
	if (m < c.center.x) {
		t1.x = (c.center.x*l*l + c.center.x*m*m - m * c.radius()*c.radius()) / (l * l + m * m);
		t1.y = (c.center.y*l*l + c.center.y*m*m - l * c.radius()*c.radius()) / (l * l + m * m);
	}
	else
	{
		t1.x = (c.center.x*l*l + c.center.x*m*m + m * c.radius()*c.radius()) / (l * l + m * m);
		t1.y = (c.center.y*l*l + c.center.y*m*m + l * c.radius()*c.radius()) / (l * l + m * m);
	}
	return t1;
}

Tochki Circle::Peretin(Circle k, Circle c) {
	Tochki peretin;
	double d = sqrt((k.center.x - c.center.x)*(k.center.x - c.center.x) + (k.center.y - c.center.y)*(k.center.y - c.center.y));
	if ((!d && k.radius == c.radius) || d > k.radius + c.radius || d < abs(k.radius - c.radius)) {
		// circles are coincident or separate or one contained within the other
	}
	else {
		double a = (k.radius*k.radius - c.radius*c.radius + d * d) / (2 * d);
		Tochki t;
		t.x = k.center.x + (c.center.x - k.center.x)*a / d;
		t.y = k.center.y + (c.center.y - k.center.y)*a / d;

		double h = sqrt(k.radius*k.radius - a * a);
		Tochki t1;
		t1.x = t.x + h*(c.center.y - k.center.y) / d;
		t1.y = t.y + h*(c.center.x - k.center.x) / d;

		return t1;
		
		if (d == k.radius + c.radius) { /*One intersection point*/ }
		else
		{
			Tochki t2;
			t2.x = t.x - h * (c.center.y - k.center.y) / d;
			t2.y = t.y - h * (c.center.x - k.center.x) / d;
			return t2;
	}
}