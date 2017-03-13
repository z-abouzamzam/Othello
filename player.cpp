
#include "player.hpp"
//#include <board.hpp>
#include <cstdlib>
#include <vector>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */

Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    // std::cout<<"side: "<<side;

    /*
     * Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.asa
     */

     // set edge values
    for (int i = 0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            strengths[i][j] = 0;
        }
    }

    for (int i = 0; i<8; i++)
    {
        strengths[0][i] = 2;
        strengths[7][i] = 2;
        strengths[i][0] = 2;
        strengths[i][7] = 2;
    }

    strengths[0][0] = 5;
    strengths[7][0] = 5;
    strengths[0][7] = 5;
    strengths[7][7] = 5;

    strengths[1][1] = -5;
    strengths[1][6] = -5;
    strengths[6][1] = -5;
    strengths[6][6] = -5;

    strengths[0][1] = -2;
    strengths[0][6] = -2;
    strengths[1][0] = -2;
    strengths[1][7] = -2;
    strengths[6][0] = -2;
    strengths[6][7] = -2;
    strengths[7][1] = -2;
    strengths[7][6] = -2;


    board = new Board();
    playerSide = side;

    if (playerSide == BLACK)
    {
        opponentSide = WHITE;
        std::cerr<<"playerside = Black\n";
    }
    else
    {
        opponentSide = BLACK;
        std::cerr<<"playerside = White\n";
    }
    //std::cerr<<"playerside = "<<playerSide;


}

/*
 * Destructor for the player
 */
Player::~Player()
{
    delete board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft)
{
    /*
     * Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    // comment in the function to test
    // doBestMove calculates move based on amount of spaces it switches over,
    // and doBetterMove uses weighted edge values to choose the best move

    // both better and best seem to beat simple player consistently

    // a future implementation may combine better and best to form the bestest
    // move to beat simple player

    return doBestMove(opponentsMove, msLeft);
    //return doBetterMove(opponentsMove, msLeft);
    // return doSimpleMove(opponentsMove, msLeft);
}


Move* Player::doMinimaxMove(Move* opponentsMove, int depth, int maxDepth)
{
    board->doMove(opponentsMove, opponentSide);
    vector<Move*> currMoves = board->getPossibleMoves(playerSide);


}




// determines the best move by  determining how many spaces each move captures
Move* Player::doBestMove(Move* opponentsMove, int msLeft)
{
    board->doMove(opponentsMove, opponentSide);
    vector<Move*> currMoves = board->getPossibleMoves(playerSide);
    // cerr << board->hasMoves(playerSide) << "\n";
    // cerr << "got current moves \n" << currMoves.size();
    int maxIndex = 0, max = 0;
    for(int i = 0; i < currMoves.size(); i++)
    {
        // cerr << "calcing spaces \n";
        if(max >= board->calcCapturedSpaces(currMoves[i], playerSide))
        {
            maxIndex = i;
        }
    }
    // cerr << "returning\n";
    board->doMove(currMoves[maxIndex], playerSide);
    return currMoves[maxIndex];
}

// determines the best move by using weighted edge values
Move *Player::doBetterMove(Move* opponentsMove, int msLeft)
{
    //if (m == nullptr) return;
    board->doMove(opponentsMove, opponentSide);
    vector<Move*> currMoves;
    Move *best;
    int max = -50;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move* move = new Move(i, j);
            if (board->checkMove(move, playerSide))
            {
                // board->doMove(move, playerSide);
                currMoves.push_back(move);
                if (strengths[i][j]>max){
                    max = strengths[i][j];
                    best = max;
                }
            }
        }

    }
    if (currMoves.size() > 0){
        board->doMove(best, playerSide);
        return best;
    }

    return nullptr;
}


Move *Player::doSimpleMove(Move* opponentsMove, int msLeft)
{
    // vector<Move*> validMoves;
    board->doMove(opponentsMove, opponentSide);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move* move = new Move(i, j);
            if (board->checkMove(move, playerSide))
            {
                board->doMove(move, playerSide);
                return move;
            }
        }

    }

    // we now juoves(0);st choose a random valid move
    //  if board.hasMov[])is.splayerSide
    return nullptr;
}
