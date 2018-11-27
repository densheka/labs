/**
  checkersgame.cpp
  Purpose: implements the basic functions for the game
*/

#include "checkersgame.h"

CheckersGame::CheckersGame()
{
	setGameType(RUSSIAN);
	srand(time(NULL));
	cleared = 0;
	created = 0;
	current = NULL;
	first = NULL;
	current = NULL;
}

CheckersGame::~CheckersGame() {
	endGame();
}
// sets game type variables
bool CheckersGame::setGameType(uint8 type) {
	if(type == RUSSIAN) {
		this->type = type;
		n = 8; k_start = 3;
		return true;
	}
	if(type == INTERNATIONAL) {
		this->type = type;
		n = 10; k_start = 4;
		return true;
	}
	return false;
}
// sets the depth of search
void CheckersGame::setMaxLevel(int level) {
	if(level >=3 && level <=7)
		maxlevel = level;
	else
		maxlevel = 3;
}
// starts a new game, the argument is the color of the computer's checkers
void CheckersGame::startNewGame(uint8 color) {
	computercolor = color;
	if(color == WHITE)
		humancolor = BLACK;
	else
		humancolor = WHITE;
	first = new CheckersState(n);
	created++;

	for(int i=0; i<n; i++) {
		for(int j=0; j<k_start; j++) {
			if(i%2 == j%2)
				first->at(i,j) = WHITE;
		}
		for(int j=n-k_start; j<n; j++) {
			if(i%2 == j%2)
				first->at(i,j) = BLACK;
		}
	}
	if(current)
		delete current;
	current = new CheckersState(first);
	historyStates.push_back(first);
	created++;
	click = 0;
	historynum = 0;
	// установка направлений обхода
	ix[0] = -1; ix[1] = 1; ix[2] = -1; ix[3] = 1;
	jx[0] = 1; jx[1] = 1; jx[2] = -1; jx[3] = -1;
	gamerunning = true;
	if(computercolor == WHITE) {
		go();
	} else {
		emit stateChanged(current);
		pp(current,humancolor);
		std::cout << "Created: " << created << " Deleted: " << cleared << "\n"; std::cout.flush();
	}
}
// ends game
void CheckersGame::endGame() {
	cleared = 0;
	created = 0;
	gamerunning = false;
	if(current) {
		clearTree(current, true, true);
		current = NULL;
	}
		first = NULL;
	history.clear();
	for(unsigned i=0; i<historyStates.size(); i++)
		delete historyStates.at(i);
	historyStates.clear();
}

// generating procedure for a given state and color of player chips
void CheckersGame::pp(CheckersState * state, uint8 color) {
	std::vector <point> vp;
	capturefound = false;
	for(unsigned i=0; i<n; i++) {
		for(unsigned j=0; j<n; j++) {
			if(i%2 == j%2 && state->color(i,j) == color) {
				searchMove(state, i, j, vp);
                clearTree(state, false, true);  // clear the tree, leaving sheets and parent
			}
		}
	}
	// если найден хоть один ход с боем, мы должны исключить простые ходы
	if(capturefound) {
		for(unsigned i=0; i<movesearch.size(); i++) {
			if( movesearch.at(i)->move().size() == 2 ) {
				delete movesearch.at(i);
				movesearch.erase( movesearch.begin()+i );
				i--;
			} else {
				break;
			}
		}
	}
    // in international checkers we are obliged to choose the best course of battle
	if(type == INTERNATIONAL) {
		int max_deleted = 0;
		for(unsigned i=0; i<movesearch.size(); i++) {
			if( movesearch.at(i)->deletedAtMove() > max_deleted )
				max_deleted = movesearch.at(i)->deletedAtMove();
		}
		for(unsigned i=0; i<movesearch.size(); i++) {
			if( movesearch.at(i)->deletedAtMove() < max_deleted ) {
				delete movesearch.at(i);
				movesearch.erase( movesearch.begin()+i );
				i--;
			}
		}
	}
    // we make the found lists by children of the state under consideration
	for(unsigned i=0; i<movesearch.size(); i++) {
		std::vector<point>::iterator it;
		for ( it=movesearch.at(i)->move().begin() ; it < movesearch.at(i)->move().end(); it++ ) {
			if( it->type == DELETED )
				movesearch.at(i)->at( it->x, it->y ) = 0;
		}
		movesearch.at(i)->setParent(state);
		state->childs().push_back( movesearch.at(i) );
	}
	movesearch.clear();
}

// maximum number of moves for checkers
int CheckersGame::movesCount(CheckersState * state, int i, int j) {
	uint8 color = state->color(i,j);
	int moves = 0;
	if(!color)
		return 0;
    int sidx, eidx, pidx = 1; // shift numbers, the maximum possible number of steps for checkers
	if(color == WHITE) {
		sidx = 0; eidx = 1;
	}
	if(color == BLACK) {
		sidx = 2; eidx = 3;
	}
	if( state->isKing(i,j) ) {
        sidx = 0; eidx = 3; pidx = n; // king can walk around the playing field and in any direction.
	}
    // transition check
	for(char k=sidx; k<=eidx; k++) {
		for(char pk=1; pk <= pidx; pk++) {
			char xi = i + pk*ix[(int)k];
			char xj = j + pk*jx[(int)k];
            if( !checkCoordinate(xi) || !checkCoordinate(xj) ) // if you went beyond the playing field
				break;
			if(state->isNull(xi,xj)) {
				moves ++;
			} else {
				break;
			}
		}
	}
	bool captureflag;
	for(int k=0; k<=3; k++) {
		captureflag = false;
		for(char pk=1; pk <= pidx+1; pk++) {
			char xi = i + pk*ix[k];
			char xj = j + pk*jx[k];
			if( !checkCoordinate(xi) || !checkCoordinate(xj) )
				break;
			if( !captureflag && state->isNull(xi,xj) )
				continue;
			if( state->color(xi,xj) == color || state->at(xi,xj) == MARKDELETED )
				break;
			if( !captureflag && state->color(xi, xj)!= color ) {
				captureflag = true;
				continue;
			}
			if(captureflag) {
				if( !state->isNull(xi,xj) ) {
					captureflag = false;
					break;
				}
				moves++;
			}
		}
	}
	return moves;
}

// recursively looking for possible moves for a given chip and state
int CheckersGame::searchMove(CheckersState *state, int i, int j, std::vector <point> & vp) {
    std::vector < std::vector <point> > vpp; // array for simple moves
	std::vector <point> tmp_vp;
	point cp;
	int normmoves = 0, delmoves = 0;

	uint8 color = state->color(i,j);
	bool isking = state->isKing(i,j);
	if(!color)
		return false;

    int sidx, eidx, pidx = 1; // shift numbers, the maximum possible number of steps for checkers
	if(color == WHITE) {
		sidx = 0; eidx = 1;
	}
	if(color == BLACK) {
		sidx = 2; eidx = 3;
	}
	if( state->isKing(i,j) ) {
        sidx = 0; eidx = 3; pidx = n; // king can walk around the playing field and in any direction
	}
    // transition check
	for(char k=sidx; k<=eidx && !capturefound; k++) {
		for(char pk=1; pk <= pidx; pk++) {
			char xi = i + pk*ix[(int)k];
			char xj = j + pk*jx[(int)k];
			if( !checkCoordinate(xi) || !checkCoordinate(xj) ) // усли вышли за пределы игрового
				break;
			if(state->isNull(xi,xj)) {
                // create a new state
				tmp_vp.clear();
				tmp_vp.push_back(point(i,j,MOVEDFROM));
				if ( (color==BLACK && xj==0 && !isking) || (color==WHITE && xj==n-1 && !isking)  ) {
					tmp_vp.push_back(point(xi,xj,TOKING));
				} else {
					tmp_vp.push_back(point(xi,xj,MOVEDTO));
				}
				vpp.push_back(tmp_vp);
				normmoves ++;
//				std::cout << "Can move to " << (int)xi << " " << (int)xj << " \n"; std::cout.flush();
			} else {
				break;
			}
		}
	}
	bool captureflag;
    // check the possibility to beat
	for(int k=0; k<=3; k++) {
		captureflag = false;
		for(char pk=1; pk <= pidx+1; pk++) {
			char xi = i + pk*ix[k];
			char xj = j + pk*jx[k];
            if( !checkCoordinate(xi) || !checkCoordinate(xj) )	// validation of coordinates
				break;
            if( !captureflag && state->isNull(xi,xj) )				// if not found a downed chip and an empty cell
				continue;
            // met on the way the same color - can not get around and jump
			if( state->color(xi,xj) == color || state->at(xi,xj) == MARKDELETED )
				break;
            // if a downed chip is not found and in the current position another chip by color
			if( !captureflag && state->color(xi, xj)!= color ) {
				captureflag = true;
				cp.x = xi; cp.y = xj; cp.type = MARKDELETED;
				continue;
			}
            // if a chip is found that can be beaten
			if(captureflag) {
                    // if a non-empty cell cannot be beaten
				if( !state->isNull(xi,xj) ) {
					captureflag = false;
					break;
				}
                // building a new state, launching a search for a possible next beat from this state
				capturefound = true;
				delmoves++;

                // preparation of the generating vector
				tmp_vp.clear();
				tmp_vp.push_back(point(i,j,MOVEDFROM));
				tmp_vp.push_back(cp);
                if ( (color==BLACK && xj==0 && !isking) || (color==WHITE && xj==n-1 && !isking)  ) // king check
					tmp_vp.push_back(point(xi,xj,TOKING));
				else
					tmp_vp.push_back(point(xi,xj,MOVEDTO));

                CheckersState *tmpstate = state->genNextState(tmp_vp);		// spawn of a new state
				created++;

                // preparation of the history vector
				std::vector <point> history_vector = vp;
				if( vp.size() ) {
					(history_vector.end()-1)->type = MOVEDTHROUGH;
					(history_vector.end()-2)->type = DELETED;
					tmpstate->deletedAtMove() = state->deletedAtMove()+1;
				} else {
					history_vector.push_back( tmp_vp.at(0) );
					tmpstate->deletedAtMove() = 1;
				}
				cp.type = DELETED;
				history_vector.push_back( cp );
				history_vector.push_back( tmp_vp.at(2) );
				//
				tmpstate->move() = history_vector;
				tmpstate->setParent(state);
				state->childs().push_back(tmpstate);
				if(! searchMove(tmpstate, xi, xj, history_vector ))
					movesearch.push_back(tmpstate);
			}
		}
	}


    // there are states from which the chips fight, remove simple transitions as not conforming to the rules
	if(capturefound) {
		normmoves = 0;
	} else {
		for(unsigned i=0; i<vpp.size(); i++) {
			CheckersState * tmpstate = state->genNextState(vpp.at(i));
			created++;
			tmpstate->setParent(state);
			state->childs().push_back(tmpstate);
			movesearch.push_back(tmpstate);
		}
	}
	return normmoves + delmoves;
}

// implementation of the computer step from the current state
void CheckersGame::go() {
	goRecursive(current, 1, -9999, 9999);
	/// выбор из потомков самого лучшего
	int xmax = -9999;
	int id = 0;
	for(unsigned i=0; i<current->childs().size(); i++) {
		if( current->childs().at(i)->score() > xmax ) {
			xmax = current->childs().at(i)->score();
		}
	}
	std::vector <CheckersState *> tmp;
	for(unsigned i=0; i<current->childs().size(); i++) {
		if( current->childs().at(i)->score() == xmax ) {
			tmp.push_back( current->childs().at(i) );
		}
	}
	id = rand() % tmp.size();
	std::cout << tmp.size() << "\n";
	move( tmp.at(id)->move().front(), tmp.at(id)->move().back() );
	pp(current,humancolor);
}

// recursive search tree construction
int CheckersGame::goRecursive(CheckersState *state, int level, int alpha, int beta) {
	bool max = true;
	if(computercolor == WHITE)
		max = false;
	uint8 color = humancolor;
	if(level%2) {
		color = computercolor;
		max = !max;
	}
	if(level == maxlevel || checkTerminatePosition(state)) {
		state->score() = evaluation(state);
		return state->score();
	}
	pp(state, color);
	unsigned i;
	for(i=0; i< state->childs().size(); i++) {
		alpha = std::max( alpha, - goRecursive( state->childs().at(i), level+1 , -beta, -alpha ) );
		if ( beta < alpha ) {
			break;
		}
	}
	int xmax=-9999, xmin=9999;
	for(unsigned j=0; j<state->childs().size(); j++) {
		if(max) {
			if( state->childs().at(j)->score() > xmax )
				xmax = state->childs().at(j)->score();
		} else {
			if( state->childs().at(j)->score() < xmin )
				xmin = state->childs().at(j)->score();
		}
	}
	if(max)
		state->score() = xmax;
	else
		state->score() = xmin;
	return alpha;
}

// checks the coordinate of the playing field
bool CheckersGame::checkCoordinate(char x) {
	if(x>=0 && x<n)
		return true;
	return false;
}

// calculate counts
void CheckersGame::calcCounts(CheckersState * state) {
	std::vector <CheckersState *> tmp;
//	if something is already counted, then the generative procedure was performed earlier for
//	one of the colors
	state->counts().clear();
	state->counts().resize(8,0);
	int movescount;
	for(unsigned i=0; i<n; i++) {
		for(unsigned j=0; j<n; j++) {
			if(i%2!=j%2)
				continue;
			movescount = movesCount(state, i, j);
			if(state->at(i,j)==WHITE) {
				state->counts()[0]++;
				state->counts()[2] += movescount;
			}
			if(state->at(i,j)==WHITEKING) {
				state->counts()[1]++;
				state->counts()[2] += movescount;
			}
			if(state->at(i,j)==BLACK) {
				state->counts()[4]++;
				state->counts()[6] += movescount;
			}
			if(state->at(i,j)==BLACKKING) {
				state->counts()[5]++;
				state->counts()[6] += movescount;
			}
		}
	}
	if(tmp.size()) {
		state->childs() = tmp;
	}
}

// evaluation function for an arbitrary state
int CheckersGame::evaluation(CheckersState * state) {
	if(!state->counts().size())
		calcCounts(state);
	int evaluation = 0;
	evaluation += 4 * ( state->counts()[0] - state->counts()[4] );
	evaluation += 6 * ( state->counts()[1] - state->counts()[5] );
	evaluation += ( state->counts()[2] - state->counts()[6] );
	return evaluation;
}

// check position for terminality
bool CheckersGame::checkTerminatePosition(CheckersState * state) {
	if(!state->counts().size())
		calcCounts(state);
    // if all the chips are beaten
	if ( !(state->counts()[0]+state->counts()[1]) ||
		 !(state->counts()[4]+state->counts()[5]) )
		return true;
    // if all the chips are blocked
	if( !state->counts()[2] || !state->counts()[6] )
		return true;
	return false;
}

// chooses winner
uint8 CheckersGame::whoWin(CheckersState *state) {
	if ( !(state->counts()[0]+state->counts()[1]) || !state->counts()[2] )
        return BLACK;	// black won
	if ( !(state->counts()[4]+state->counts()[5]) || !state->counts()[6] )
        return WHITE;	// white won
	return -1;
}

// recursive cleaning of the state tree
void CheckersGame::clearTree(CheckersState * state, bool clearlists, bool onlychilds) {
    if (onlychilds) {		// if we only clean children without removing the root node
		for(unsigned i =0; i < state->childs().size(); i++) {
            clearTreeRecursive( state->childs().at(i), clearlists ); // remove all children
		}
		state->childs().clear();
	} else {
        clearTreeRecursive( state, clearlists ); // delete all
	}
}

// helper function for cleaning the state tree
void CheckersGame::clearTreeRecursive(CheckersState * state, bool clearlists) {
    // if the node in question has no descendants, then it is a list
	if( state->childs().size() == 0 && clearlists ) {
		cleared ++;
		delete state;
	} else {
		for(unsigned i =0; i < state->childs().size(); i++) {
			clearTreeRecursive( state->childs().at(i), clearlists );
		}
		state->childs().clear();
		if(clearlists) {
			cleared ++;
			delete state;
		}
	}
}

// creates a vector point
void CheckersGame::printPointVector(std::vector <point> & v) {
	for(unsigned i=0; i<v.size(); i++) {
		std::cout << (int)v.at(i).x << " " << (int)v.at(i).y << " " << (int)v.at(i).type << "\n";
	}
	std::cout.flush();
}

// sets clicking
void CheckersGame::setClicked(int i, int j) {
	if(i>=0 && i<n && j>=0 && j<n && i%2==j%2 && gamerunning) {
		std::cout << "Clicked at " << (int)i << " " << (int)j << " = "<< (int)current->at(i,j) << std::endl;
		if(click == 0)
			firstClick(i, j);
		else
			secondClick(i, j);
	} else {
		emit vectorDeleted();
		click = 0;
	}
}

// the player clicked the mouse for the first time
void CheckersGame::firstClick(int i, int j) {
	if( (humancolor == current->color(i,j))) {
		std::cout << "Click 0" << "\n"; std::cout.flush();
		tmppoint.x = i; tmppoint.y = j; tmppoint.type = MOVEDFROM;
		tmpvector.clear();
		for(unsigned ii=0; ii< current->childs().size(); ii++ ) {
			if( current->childs().at(ii)->move().at(0) == tmppoint ) {
				for( unsigned jj=0; jj<current->childs().at(ii)->move().size(); jj++ ) {
					tmpvector.push_back( current->childs().at(ii)->move().at(jj) );
				}
			}
		}
		if(tmpvector.size()) {
			click = 1;
			emit vectorChanged(tmpvector);
			return;
		}
	}
	emit vectorDeleted();
}

// the player clicked the mouse second time
void CheckersGame::secondClick(int i, int j) {
	std::cout << "Click 1" << "\n"; std::cout.flush();
	bool move = false;
	if ( (tmppoint.x == i && tmppoint.y == j) ) {
		return;
	}
	if( current->isNull(i,j) )
		move = this->move( tmppoint , point(i,j,MOVEDTO) );
	if( !move ) {
		click =0;
		firstClick(i, j);
	} else {
        // the move is successful
		if(gamerunning)
            go(); // do move with a computer
		click = 0;
	}
}

// the function checks the possibility of the transition p1 >> p2 and implements it, if possible
bool CheckersGame::move(point p1, point p2) {
	for(unsigned i=0; i< current->childs().size(); i++ ) {
		if( current->childs().at(i)->move().front() == p1 &&
			current->childs().at(i)->move().back().x == p2.x &&
			current->childs().at(i)->move().back().y == p2.y )
		{
            // perform a transition operation
			std::cout << "Move ok!!!\n"; std::cout.flush();
			CheckersState * tmpstate = current->childs().at(i);
			current->childs().erase(current->childs().begin()+i);
			clearTree(current,true);
			clearTree(tmpstate,true,true);
			current = tmpstate;
            history.push_back( current->move() );	// save history
			tmp = new CheckersState(current); 	tmp->childs().clear();
			historyStates.push_back( tmp );
			emit stateChanged(current);
			historynum = historyStates.size()-1;
			if(checkTerminatePosition(current)) {
				emit gameEnded( whoWin(current) );
				gamerunning = false;
			}
			return true;
		}
	}
	return false;
}

// shows history beginning
void CheckersGame::historyShowFirst() {
	historynum = 0;
	historyShow();
}

// shows history ending
void CheckersGame::historyShowLast() {
	historynum = historyStates.size()-1;
	historyShow();
}

// shows previous action
void CheckersGame::historyShowPrev() {
	historynum --;
	historyShow();
}

// shows next action
void CheckersGame::historyShowNext() {
	historynum ++;
	historyShow();
}

// function showing actions taken at some time
void CheckersGame::historyShow() {
	gamerunning = false;
	if(historynum <0)
		historynum =0;
	if(historynum > (int)historyStates.size()-1)
		historynum = historyStates.size()-1;
	if( historynum == (int)historyStates.size()-1 ) {
		gamerunning = true;
		click = 0;
		emit stateChanged( current );
		return;
	}
	emit stateChanged( historyStates.at(historynum) );
}

