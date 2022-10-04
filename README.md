# Filler
An algorithmic solution to a multiplayer strategy game, created during my studies at Hive.

 Filler:
 - A 1v1 strategy game, with the goal to own a majority of the game board
   with the pieces randomly provided to you.
 - Each player uses their own algorithm.
 - If a piece cannot be placed, the game ends.

 Round process:
 1)  Allocates space for the board using the coordinates given.
 2)  Fills the board with -1 and -2 depending on who is player 1 and player
     2.
 3)  Turns the board into a heatmap, used to calculate the shortest distance
     to the opponents pieces.
 4)  Allocates space for the random given piece.
 5)  Fills the piece with the given structure as zeroes and -1 / -2.
 6)  Frees the line being read, as it is no longer needed until the next round.
 7)  Calculates the shortest possible distance to the opponents pieces via
     the piece structure and heatmap.
 8)  Places the piece. If piece is valid, game continues. If piece is not
     valid, the game will end.
 9)  The round has ended, so the board is emptied and filled with zeroes
     for the next round. The piece is emptied completely.
 10) If the game is due to end now, all relevant information is freed and
     deleted.