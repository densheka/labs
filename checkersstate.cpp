/**
  checkersstate.cpp
  Purpose: implements the basic functions for the checkers state
*/

#include "checkersstate.h"

CheckersState::CheckersState()
{
	allocate(10);
}

CheckersState::CheckersState(uint8 size)
{
	allocate(size);
}

CheckersState::CheckersState(const CheckersState &source) {
	allocate(source.n);
	for(int i=0; i<n; i++)
		for(int j=0; j<n/2; j++)
			data[i][j] = source.data[i][j];
	xcounts = source.xcounts;
}

CheckersState::CheckersState(const CheckersState *source) {
	allocate(source->n);
	for(int i=0; i<n; i++)
		for(int j=0; j<n/2; j++)
			data[i][j] = source->data[i][j];
	xcounts = source->xcounts;
}

CheckersState::~CheckersState() {
	for(int i=0; i<n; i++)
		delete[] data[i];
	delete[] data;
}

// allocation of state
void CheckersState::allocate(uint8 size) {
	n = size;
	data = new uint8 * [n];
	for(int i=0; i<n; i++)
	{
		data[i] = new uint8[n/2];
		memset( data[i], 0, n/2*sizeof(uint8) );
	}
	tmp = 0;
	p = NULL;
	deletedatmove = 0;
}

// prints state
void CheckersState::print() {
	for(int j = n/2-1; j>=0; j--)
	{
		for(int i=1; i<n; i+=2)
			std::cout << " _ " << (unsigned int)data[i][j] << " ";
		std::cout << std::endl;
		for(int i=0; i<n; i+=2)
			std::cout << " " << (unsigned int)data[i][j] << " _ ";
		std::cout << std::endl;
	}
	std::cout.flush();
}

// size
uint8 CheckersState::size() {
	return n;
}

// counts the number of chips
std::vector <uint8> & CheckersState::counts() {
	return xcounts;
}

// spawns a new state from the current one, takes the move vector as an argument
CheckersState * CheckersState::genNextState(std::vector <point> & v) {
	CheckersState * state = new CheckersState(this);
	uint8 tmp;
	for(unsigned k=0; k<v.size(); k++) {
		uint8 i = v.at(k).x;
		uint8 j = v.at(k).y;
		switch(v.at(k).type) {
			case(MOVEDFROM):
				tmp = state->at(i,j);
				state->at(i,j) = 0;
				break;
			case(MOVEDTO):
				state->at(i,j) = tmp;
				break;
			case(MARKDELETED):
				state->at(i,j) = MARKDELETED;
				break;
			case(DELETED):
				state->at(i,j) = 0;
				break;
			case(TOKING):
				if( tmp == WHITE )
					state->at(i,j) = WHITEKING;
				if( tmp == BLACK )
					state->at(i,j) = BLACKKING;
				break;
			default:
				break;
		}
	}
	state->move() = v;
	state->counts().clear();
	return state;
}

// sets parent
void CheckersState::setParent(CheckersState * parent) {
	p = parent;
}

// parent
CheckersState * CheckersState::parent() {
	return p;
}

// childrens
std::vector < CheckersState * > & CheckersState::childs() {
	return xchilds;
}

// transition from parent to current state
std::vector < point > & CheckersState::move() {
	return xmove;
}

// score
int & CheckersState::score() {
	return xscore;
}

// the number of opponent's chips beaten as a result of the transition to this state
int & CheckersState::deletedAtMove() {
	return deletedatmove;
}

// points for field position
uint8 & CheckersState::at(uint8 i, uint8 j) {
	if(i%2 != j%2) {
		tmp = WHITECELL;
		return tmp;
	}
	return data[i][j/2];
}

// gives color chips
uint8 CheckersState::color(uint8 i, uint8 j) {
	if( at(i,j) == WHITE || at(i,j) == WHITEKING)
		return WHITE;
	if( at(i,j) == BLACK || at(i,j) == BLACKKING)
		return BLACK;
	return false;
}

// chip is white
bool CheckersState::isWhite(uint8 i, uint8 j) {
	if(at(i,j)==WHITE || at(i,j)==WHITEKING)
		return true;
	return false;
}

// chip is black
bool CheckersState::isBlack(uint8 i, uint8 j) {
	if(at(i,j)==BLACK || at(i,j)==BLACKKING)
		return true;
	return false;
}

// chip is king
bool CheckersState::isKing(uint8 i, uint8 j) {
	if(at(i,j)==WHITEKING || at(i,j)==BLACKKING)
		return true;
	return false;
}

// not running cage
bool CheckersState::isNull(uint8 i, uint8 j) {
	if( at(i,j) == WHITECELL )
		return true;
	return !at(i,j);
}

