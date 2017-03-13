#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    Board *board;
    Move *doSimpleMove(Move* opponentsMove, int msLeft);
    Move *doBetterMove(Move* opponentsMove, int msLeft);
    Move *doBestMove(Move* opponentsMove, int msLeft);
    int doMinimaxMove(Move* opponentsMove, Board *board, int depth, int maxDepth, Side mySide);


    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
	
	Side playerSide;
	Side opponentSide;
	int strengths[8][8];
	int m_strengths[8][8];
	int maxDepth=4;

};

#endif
