README.txt

Over the past few weeks, Michelle and I have been working pretty well together
on this assignment. Through the first week, we worked mostly together to
implement the basic player class. After that, we created new functions
separately to attempt to beat the SimplePlayer. Michelle first created one
class which uses weight tables to choose the highest weighted space when
applicable, or chooses simply the first open space when not applicable. I
implemented a different function, which bases moves off of how many spaces
the AI would capture per move, choosing the move which takes the most pieces
at a given time. Both these functions could beat the SimplePlayer class
consistently. This week, Michelle and I worked on a better AI to beat the
ConstantTimePlayer and submit to the Othello tournament. Here, Michelle
did more of the implementation, and I helped her debug and go through
the logic. All of the code we pushed to github.

To make our AI tournament worthy, we implemented the minimax function. It works
using weight tables to choose certain spaces which represent the graph, and
looks ahead a certain depth to choose the best move. It compares these future
moves and chooses the best one based on the weight tables. I think our
strategy will work well based on the strengths we gave to each move, and also
based on how quickly it chooses the moves. I don't particularly want to
disclose more information about our AI, however, as I believe it could
potentially jeopardize our chances of winning the tournament. On a side note,
we did attempt to implement pruning, but we are leaving the majority of it as
a future goal to work on after the tournament.
