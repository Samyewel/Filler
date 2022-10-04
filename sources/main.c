/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:46:08 by swilliam          #+#    #+#             */
/*   Updated: 2022/10/04 14:20:38 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filler.h"

/*
** reset_round:
** - Once a round is complete, we keep the board size but simply revert all
**   spaces to zero so they can be filled in the next round.
** - We remove all piece information to allow the next random piece to be
**   stored.
*/

void	reset_round(t_board *board, t_piece *piece)
{
	int	x;
	int	y;

	y = 0;
	if (!piece->placed)
		return ;
	while (y < board->y)
	{
		x = 0;
		while (x < board->x)
		{
			if (board->board[y][x] != 0)
				board->board[y][x] = 0;
			x++;
		}
		y++;
	}
	y = 0;
	while (y < piece->y)
	{
		free(piece->piece[y]);
		y++;
	}
	free(piece->piece);
	initialise_piece(piece);
}

/*
** end_game:
** - Once no more pieces can be placed, both the board and piece information
**   are completely wiped.
*/

void	end_game(t_board *board, t_piece *piece)
{
	int	i;

	i = 0;
	if (board->board != NULL)
	{
		while (i < board->y)
		{
			free(board->board[i]);
			i++;
		}
		free(board->board);
	}
	free(board);
	free(piece);
	exit(1);
}

/*
** Filler:
** - A 1v1 strategy game, with the goal to own a majority of the game board
**   with the pieces randomly provided to you.
** - Each player uses their own algorithm.
** - If a piece cannot be placed, the game ends.
**
** main:
** - Initialises board and piece data.
** - Skips one line, then reads which player number each player is given.
** - Reads line by line in a cycle until there is nothing left to read.
**
** Round process:
** 1)  Allocates space for the board using the coordinates given.
** 2)  Fills the board with -1 and -2 depending on who is player 1 and player
**     2.
** 3)  Turns the board into a heatmap, used to calculate the shortest distance
**     to the opponents pieces.
** 4)  Allocates space for the random given piece.
** 5)  Fills the piece with the given structure as zeroes and -1 / -2.
** 6)  Frees the line being read, as it is no longer needed until the next round.
** 7)  Calculates the shortest possible distance to the opponents pieces via
**     the piece structure and heatmap.
** 8)  Places the piece. If piece is valid, game continues. If piece is not
**     valid, the game will end.
** 9)  The round has ended, so the board is emptied and filled with zeroes
**     for the next round. The piece is emptied completely.
** 10) If the game is due to end now, all relevant information is freed and
**     deleted.
*/

int	main(void)
{
	char		*line_read;
	t_board		*board;
	t_piece		*piece;

	line_read = NULL;
	board = (t_board *)malloc(sizeof(t_board));
	piece = (t_piece *)malloc(sizeof(t_piece));
	if (!board || !piece)
		return (-1);
	initialise_board(board);
	initialise_piece(piece);
	get_next_line(0, &line_read);
	update_players(board, line_read);
	while (get_next_line(0, &line_read) > 0)
	{
		allocate_map(board, line_read);
		fill_map(board, line_read);
		allocate_fill_piece(board, piece, line_read);
		ft_strdel(&line_read);
		attempt_placement(board, piece);
		reset_round(board, piece);
	}
	end_game(board, piece);
	return (0);
}
