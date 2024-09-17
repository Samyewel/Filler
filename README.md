# Filler

- [Overview](#overview)
- [Game Rules](#Game_Rules)
- [Round Process](#Round_Process)
- [Usage](#usage)
- [Credits](#credits)

## Overview

Filler is a multiplayer strategy game developed as part of the curriculum at Hive. It involves two players competing to dominate a game board using randomly provided pieces. Each player implements their own algorithm to place pieces strategically.

## Game Rules

- **Objective**: Own the majority of the game board using the pieces provided.
- **Gameplay**: Players take turns placing pieces on the board. If a player cannot place a piece, the game ends.
- **Piece Placement**: Pieces are placed based on the shortest distance calculation to the opponent's pieces using a heatmap.

## Round Process

1. **Board Initialization**:
   - Allocates space for the board using the given coordinates.
   - Initializes the board with -1 and -2 based on player 1 and player 2.

2. **Heatmap Calculation**:
   - Converts the board into a heatmap to calculate distances to opponent pieces efficiently.

3. **Piece Handling**:
   - Allocates space for the randomly provided piece.
   - Initializes the piece structure with zeroes and player markers (-1 / -2).

4. **Placement Logic**:
   - Calculates the shortest distance to opponent pieces using the piece structure and heatmap.
   - Places the piece if valid. If not, ends the game.

5. **End of Round**:
   - Clears the board for the next round, filling it with zeroes.
   - Empties the piece structure.

6. **Game End**:
   - Frees all allocated memory and resources if the game is over.

## Usage

To run the Filler program:

`./filler_vm -f map_file -p1 player1 -p2 player2`
   - map_file: Path to the game board file.
   - player1, player2: Executable files or commands for each player's algorithm.
   - Optional:
     -q : quiet mode

The eval_tests folder contains a Makefile containing a python script you can use to test any of the players and maps, as well as a visualiser I am borrowing from the amazing azajay08 for demonstration purposes.

## Credits

- 42 School for designing a really fun project aiming to enhance understanding of algorithmic processes and implementations.
- azajay08 for their cute little visualiser that I am borrowing for presentation purposes!
