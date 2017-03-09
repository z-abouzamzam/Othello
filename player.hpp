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

    Move *doSimpleMove (Move* opponentsMove, int msLeft);
    Move *doBetterMove (Move* opponentsMove, int msLeft);

    Move *doBestCurrentMove(Move* opponentsMove);


    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    
private:
	Board *board;
	Side playerSide;
	Side opponentSide;
	int strengths[8][8];

};

#endif
