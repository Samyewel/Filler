/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:31:14 by sam               #+#    #+#             */
/*   Updated: 2022/10/04 14:10:52 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filler.h"

/*
** initialise_board:
** - initialises all information relating to the game board and its contents.
*/

t_board	*initialise_board(t_board *board)
{
	board->player = 0;
	board->opponent = 0;
	board->board = NULL;
	board->x = 0;
	board->y = 0;
	board->created = 0;
	return (board);
}

/*
** initialise_piece:
** - initialises all information relating to the given piece.
*/

t_piece	*initialise_piece(t_piece *piece)
{
	piece->piece = NULL;
	piece->x = 0;
	piece->y = 0;
	piece->best_x = 9999;
	piece->best_y = 9999;
	piece->best_distance = 9999;
	piece->created = 0;
	piece->placed = 0;
	return (piece);
}

/*
** initialise_attempt:
** - initialises information used for when attempting to place the piece
**   on the board.
*/

t_attempt	*initialise_attempt(t_attempt *attempt)
{
	attempt->distance = 0;
	attempt->overlap = 0;
	attempt->x = 0;
	attempt->y = 0;
	return (attempt);
}
