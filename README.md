# AI-Hex-Game
Allows the user to play the board game Hex ( https://en.wikipedia.org/wiki/Hex_(board_game) ) against an artificial intelligence opponent.

Written in C++

AI opponent uses monte carlo simulation to calculate win/trials ratio for every possible move on the board and chooses the move with highest likelihood to win.

To play against a relatively "smart" AI opponent, choose a board size of 5. 

Other normal board sizes usually used in traditional Hex are 7 and 11.

Possible future additions:
To make the AI "smarter" at higher board sizes such as 7 or 11, add a higher amount of Monte Carlo trials than 1000. To
make these computations in a reasonable amount of time, consider options such as multi-threading to achieve faster performance.


