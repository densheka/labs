/**
  checkersstate.h
  Purpose: implements the basic functions for the checkers state
*/

#ifndef CHECKERSSTATE_H
#define CHECKERSSTATE_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

typedef unsigned char uint8;

enum checker {
    WHITE = 1,				// white checker
    BLACK = 2,				// black checker
    WHITEKING = 3,			// white king
    BLACKKING = 4,			// black king
    WHITECELL = 10,			// not running cage, i%2 != j%2

    MOVEDFROM = 20,
    MOVEDTO = 21,
    MOVEDTHROUGH = 22,
    DELETED = 23,			// beaten
    MARKDELETED = 24,		// marked as beaten
    TOKING = 25				// turning into king
};

class point {
public:
	point() {
		x=0; y=0; type=0;
	}
	point(int x, int y, int type) {
		this->x = x;
		this->y = y;
		this->type = type;
	}
	uint8 x;
	uint8 y;
	uint8 type;
bool operator == (const point & p ) {
		if( x==p.x && y==p.y && type==p.type )
			return true;
		return false;
	}
};

class CheckersState
{
public:
    CheckersState();
	CheckersState(uint8 size);
	~CheckersState();
	CheckersState(const CheckersState &source);
	CheckersState(const CheckersState *source);

    /**
     * @brief genNextState
     * @param v
     * @return new state
     */
    CheckersState * genNextState(std::vector <point> & v);

    /**
     * @brief setParent
     * @param parent
     */
	void setParent(CheckersState * parent);

    /**
     * @brief counts
     * @return number of chips
     */
	std::vector <uint8> & counts();
    /**
     * @brief parent
     * @return parents
     */
	CheckersState * parent();
    /**
     * @brief childs
     * @return childrens
     */
	std::vector < CheckersState * > & childs();
    /**
     * @brief move
     * @return move from parent to given state
     */
	std::vector < point > & move();
    /**
     * @brief deletedAtMove
     * @return number of opponent's chips
     */
    int & deletedAtMove();
    /**
     * @brief score
     * @return score
     */
    int & score();
    /**
     * @brief print
     */
	void print();
    /**
     * @brief size
     * @return size
     */
	uint8 size();
    /**
     * @brief at
     * @param i
     * @param j
     * @return points
     */
	uint8 & at(uint8 i, uint8 j);
    /**
     * @brief color
     * @param i
     * @param j
     * @return chips color
     */
    uint8 color(uint8 i, uint8 j);
    /**
     * @brief isWhite
     * @param i
     * @param j
     * @return white chips
     */
	bool isWhite(uint8 i, uint8 j);
    /**
     * @brief isBlack
     * @param i
     * @param j
     * @return black chips
     */
	bool isBlack(uint8 i, uint8 j);
    /**
     * @brief isKing
     * @param i
     * @param j
     * @return kings
     */
	bool isKing(uint8 i, uint8 j);
    /**
     * @brief isNull
     * @param i
     * @param j
     * @return not running cages
     */
	bool isNull(uint8 i, uint8 j);
private:
	CheckersState * p;
	std::vector < CheckersState * > xchilds;
    std::vector < point > xmove;								// description of one move from parent to given state
    std::vector < uint8 > xcounts;								// number of chips of different types
    /**
     * @brief allocate
     * @param size
     */
    void allocate(uint8 size);
	uint8 ** data;
	uint8 n;
	uint8 tmp;
	int xscore;
	int deletedatmove;
};

#endif // CHECKERSSTATE_H
