/**
  checkersgame.h
  Purpose: implements the basic functions for the game
*/


#ifndef CHECKERSGAME_H
#define CHECKERSGAME_H

#include <QObject>
#include <QVector>
#include <vector>
#include "checkersstate.h"

// rule types
enum GameType{
	RUSSIAN = 1,
	INTERNATIONAL = 2,
};

class CheckersGame : public QObject
{
	Q_OBJECT
public:
    CheckersGame();
	~CheckersGame();
    /**
     * @brief setGameType
     * @param type
     * @return Russian or International game type
     */
    bool setGameType(uint8 type);
    /**
     * @brief setMaxLevel
     * @param level
     */
	void setMaxLevel(int level);
    /**
     * @brief startNewGame
     * @param color
     */
    void startNewGame(uint8 color);
    /**
     * @brief endGame
     */
	void endGame();
public slots:
    /**
     * @brief setClicked
     * @param i
     * @param j
     */
	void setClicked(int i, int j);
    /**
     * @brief historyShowFirst
     */
	void historyShowFirst();
    /**
     * @brief historyShowLast
     */
	void historyShowLast();
    /**
     * @brief historyShowPrev
     */
	void historyShowPrev();
    /**
     * @brief historyShowNext
     */
	void historyShowNext();
signals:
    /**
     * @brief stateChanged
     */
    void stateChanged(CheckersState *);	// state has changed, it is necessary to redraw
    /**
     * @brief vectorChanged
     * @param v
     */
	void vectorChanged(std::vector <point> & v);
    /**
     * @brief vectorDeleted
     */
	void vectorDeleted();
    /**
     * @brief gameEnded
     */
	void gameEnded(uint8);
private:
    /**
     * @brief firstClick
     * @param i
     * @param j
     */
    void firstClick(int i, int j);
    /**
     * @brief secondClick
     * @param i
     * @param j
     */
    void secondClick(int i, int j);

    // intelligent algorithm functions
    /**
     * @brief go
     */
    void go();
    /**
     * @brief goRecursive
     * @param state
     * @param level
     * @param alpha
     * @param beta
     * @return state of checker
     */
    int goRecursive(CheckersState * state, int level, int alpha, int beta);
    /**
     * @brief calcCounts
     * @param state
     */
	void calcCounts(CheckersState * state);
    /**
     * @brief evaluation
     * @param state
     * @return true value of an arbitrary state
     */
    int evaluation(CheckersState * state);
    /**
     * @brief pp
     * @param state
     * @param color
     */
    void pp(CheckersState * state, uint8 color);
    /**
     * @brief checkTerminatePosition
     * @param state
     * @return state of chips on the playing field
     */
    bool checkTerminatePosition(CheckersState * state);
    /**
     * @brief movesCount
     * @param state
     * @param i
     * @param j
     * @return possible number of moves
     */
	int movesCount(CheckersState * state, int i, int j);
    /**
     * @brief searchMove
     * @param state
     * @param i
     * @param j
     * @param vp
     * @return possible moves of checkers
     */
    int searchMove(CheckersState * state, int i, int j, std::vector <point> & vp);
    /**
     * @brief checkCoordinate
     * @param x
     * @return does the coordinate belong to the playing field
     */
    bool checkCoordinate(char x);
    /**
     * @brief clearTree
     * @param state
     * @param clearlists
     * @param onlychilds
     */
	void clearTree(CheckersState * state, bool clearlists = true, bool onlychilds = false);
    /**
     * @brief clearTreeRecursive
     * @param state
     * @param clearlists
     */
	void clearTreeRecursive(CheckersState * state, bool clearlists = false);
    /**
     * @brief move
     * @param p1
     * @param p2
     * @return is a transition possible
     */
    bool move(point p1, point p2);
    /**
     * @brief whoWin
     * @param state
     * @return winner
     */
    uint8 whoWin(CheckersState * state);

    std::vector <std::vector <point> > history;		// history of moves starting from the first
	std::vector <CheckersState *> historyStates;
	int historynum;
    /**
     * @brief historyShow
     */
	void historyShow();

    // different temporary variables needed for the algorithm
	std::vector <CheckersState *> movesearch;
    std::vector < point > tmpvector;	// temporary vector to store different points
	point tmppoint;
    /**
     * @brief printPointVector
     * @param v
     */
	void printPointVector(std::vector <point> & v);

    CheckersState * first;			// first game state
    CheckersState * current;		// current game state
	CheckersState * tmp;
    uint8 n;						// board size
    uint8 k_start;						// the number of rows of checkers at the start
    uint8 type;						// type of game (Russian, international checkers)
    uint8 computercolor;			// computer player color
    uint8 humancolor;				// the color of the human player

    int level;						// tree depth level
    uint8 click;					// click number
    char ix[4];						// walking directions
    char jx[4];						// used at the stage of searching for possible moves

    // various flags that control search restrictions, etc .:
	bool capturefound;
	bool calccounts;
    bool gamerunning;				// the game is running now
    int maxlevel;				// maximum depth of search in levels. root - level 0

    // state counters
	int cleared;
	int created;
};

#endif // CHECKERSGAME_H
