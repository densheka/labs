#include "Figure.h"
#include "Pryamaya.h"
#include <cmath>


void pryamaya::Symetry(Tochki *t, Tochki *l, pryamaya *p) {
	Tochki n;
	n.x = (p->a.y - p->b.y);
	n.y = (p->b.x - p->a.x);
	float len = sqrt(n.x*n.x + n.y*n.y);
	n.x /= len;
	n.y /= len;
	float dot2 = 2 * (n.x*t->x + n.y*t->y);
	l->x = t->x - dot2 * n.x;
	l->y = t->y - dot2 * n.y;
}

void pryamaya::Peretin(pryamaya m, pryamaya l) {
	double a;
	double b;
	b = (m.a.x - l.a.x + l.a.y*((l.b.x - l.a.x) / (l.b.y - l.a.y)) + m.a.y*((m.b.x - m.a.x) / (m.b.y - m.a.y))) / ((l.b.x - l.a.x) / (l.b.y - l.a.y) - (m.b.x - m.a.x) / (m.b.y - m.a.y));
	a = (b - m.a.y) / (m.b.y - m.a.y) * (m.b.x - m.a.x) + m.a.x;
}

Tochki pryamaya::Peretin(pryamaya m, Circle c) {
	double x, y;
	Tochki a;
	a.y = (c.radius*c.radius - c.center.x*c.center.x - m.a.x*m.a.x + 2 * m.a.x*c.center.x + 2 * m.a.x*m.a.y*((m.b.x - m.a.x) / (m.b.y - m.a.y)) - 2 * c.center.x*m.a.y*((m.b.x - m.a.x) / (m.b.y - m.a.y)) - c.center.y*c.center.y) / (2 * m.a.x*((m.b.x - m.a.x) / (m.b.y - m.a.y)) - 2 * c.center.x*((m.b.x - m.a.x) / (m.b.y - m.a.y)) + 1 - 2 * c.center.y);
	a.x = m.a.x + ((m.b.x - m.a.x)*(a.y - m.a.y)) / (m.b.y - m.a.y);
}