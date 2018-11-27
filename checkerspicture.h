/**
  checkerspicture.h
  Purpose: implements the basic functions for the checkers picture
*/

#ifndef CHECKERSPICTURE_H
#define CHECKERSPICTURE_H

#include <QtWidgets/QWidget>
#include <QPainter>
#include <QDebug>
#include <QResizeEvent>
#include <QPaintEvent>

#include "checkersstate.h"

class CheckersPicture : public QWidget
{
	Q_OBJECT
public:
	CheckersPicture(QWidget * parent = 0);
	~CheckersPicture();
    /**
     * @brief state
     * @return current state
     */
	CheckersState * state();
    /**
     * @brief setComputerColor
     * @param color
     */
	void setComputerColor(uint8 color);
public slots:
    /**
     * @brief setState
     * @param state
     */
	void setState(CheckersState *state);
    /**
     * @brief setVector
     * @param v
     */
	void setVector(std::vector <point> & v);
    /**
     * @brief deleteVector
     */
	void deleteVector();
    /**
     * @brief setSize
     * @param n
     */
	void setSize(int n);
    /**
     * @brief clear
     */
	void clear();
signals:
    /**
     * @brief mouseClicked
     */
	void mouseClicked(int, int);
protected:
    /**
     * @brief mousePressEvent
     * @param event
     */
	void mousePressEvent(QMouseEvent *event);
    /**
     * @brief paintEvent
     * @param event
     */
	void paintEvent(QPaintEvent *event);
    /**
     * @brief resizeEvent
     * @param event
     */
	void resizeEvent (QResizeEvent * event);
private:
    /**
     * @brief pixelRect
     * @param i
     * @param j
     * @return rectangle in plane
     */
	QRect pixelRect(int i, int j) const;

	CheckersState * curstate;
	std::vector <point> v;
	QPoint p;
	int side;
	int zoom;
	int n;

    uint8 color;										// opponent's checkers color
};

#endif // CHECKERSPICTURE_H
