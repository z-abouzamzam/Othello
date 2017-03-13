#include "board.hpp"

/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

/*
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    return newBoard;
}

bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}

bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

vector<Move*> Board::getPossibleMoves(Side side)
{
    vector<Move*> currMoves;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move* move = new Move(i, j);
            if (checkMove(move, side))
            {
                currMoves.push_back(move);
                //std::cerr << "Hello" << '\n';
            }
        }
    }
    //std::cerr << "I am finding moves : " << currMoves.size() << std::endl;
    return currMoves;
}


int Board::getWeightedScore(Side side)
{
    //int m_strengths[8][8];
    //m_strengths[0]={10, -5, 6, 5, 5, 6, -5, 10};
    //m_strengths[1]={-5, -10, 0, 0, 0, 0, -10, -5};
    //m_strengths[2]={6, 0, 0, 0, 0, 0, 0, 6};
    //m_strengths[3]={5, 0, 0, 0, 0, 0, 0, 5};
    //m_strengths[4]={5, 0, 0, 0, 0, 0, 0, 5};
    //m_strengths[5]={6, 0, 0, 0, 0, 0, 0, 6};
    //m_strengths[6]={-5, -10, 0, 0, 0, 0, -10, -5};
    //m_strengths[7]={10, -5, 6, 5, 5, 6, -5, 10};

    int strengths[8][8];
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

    int score=0;
    vector<Move*> currMoves;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //Move* move = new Move(i, j);
            if (occupied(i, j))
            {
                if (get(side, i, j)){
                    score += strengths[i][j];
                }
                // std::// cerr << "Hello" << '\n';
            }
        }
    }
    return score;
}


bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}


/*
 * Returns true if the game is finished; false otherwise. The game is finished
 * if neither side has a legal move.
 */
bool Board::isDone() {
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

/*
 * Returns true if there are legal moves for the given side.
 */
bool Board::hasMoves(Side side) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (checkMove(&move, side)) return true;
        }
    }
    return false;
}

int Board::calcCapturedSpaces(Move* m, Side side)
{
    // for each valid move calc space between move
    int X = m->getX();
    int Y = m->getY();

    // cerr << X << "x " << Y << "y\n";
    Side other = (side == BLACK) ? WHITE : BLACK;

    int between = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y))
                {
                    // add difference - 1 spaces
                    // cerr << "sdhjf\n";
                    // if its diagonal or in x direction
                    if(dx == dy || dy == 0)
                    {
                        between += (abs(X - x) - 1);
                    }

                    // if in y direction
                    else
                    {
                        between += (abs(Y - y) - 1);
                    }
                }
            }
        }
        // cerr << "Between = " << between << "\n";
    }

    return between;

}

/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == nullptr) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side) {
    // A nullptr move means pass.
    if (m == nullptr) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}
