/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_placement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:30:39 by sam               #+#    #+#             */
/*   Updated: 2022/10/04 14:30:18 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filler.h"

/*
** place_piece:
** - Sends the coordinates of where the place is to be placed. If the piece
**   cannot be placed, the default coordinate values of 9999 will be used,
**   therefore ending the game.
*/

void	place_piece(t_piece *piece)
{
	if (piece->created)
	{
		ft_printf("%d %d\n", piece->best_y, piece->best_x);
		piece->placed = 1;
	}
}

/*
** update_piece_distance:
** - Updates the information of the current best possible distance and
**   coordinates for the piece to be placed.
*/

static void	update_placement(t_piece *piece, t_attempt *attempt, int x, int y)
{
	piece->best_distance = attempt->distance;
	piece->best_x = x;
	piece->best_y = y;
}

/*
** check_coordinates:
** - Checks that the current section of the piece does not overlap another
**   of your pieces more than once.
** - If the current section of the piece overlaps with an opponents piece,
**   it is not a valid placement.
** - Adds the current heatmap value to the distance with the aim of finding
**   the lowest possible distance later in calculate_placement.
*/

static int	check_coordinates(t_board *board, t_attempt *attempt, int x, int y)
{
	if (x < board->x && y < board->y)
	{
		attempt->overlap += (board->board[y][x] == board->player);
		if (attempt->overlap > 1)
			return (0);
		if (board->board[y][x] == board->opponent)
			return (0);
		if (board->board[y][x] >= 0)
			attempt->distance += board->board[y][x];
		return (1);
	}
	return (0);
}

/*
** calculate_placement:
** - Loops through the piece given, checking each coordinate to see if
**   placement is possible.
** - Updates the placement coordinates and distance when a lower distance
**   is calculated.
*/

static void	calculate_placement(t_board *board, t_piece *piece, int x, int y)
{
	t_attempt	*attempt;
	int			x2;
	int			y2;

	attempt = (t_attempt *)malloc(sizeof(t_attempt));
	if (!attempt)
		end_game(board, piece);
	y2 = 0;
	initialise_attempt(attempt);
	while (y2 < piece->y)
	{
		x2 = 0;
		while (x2 < piece->x)
		{
			if (piece->piece[y2][x2] < 0)
				if (!check_coordinates(board, attempt, x2 + x, y2 + y))
					return ;
			x2++;
		}
		y2++;
	}
	if (attempt->overlap == 1 && attempt->distance < piece->best_distance)
		update_placement(piece, attempt, x, y);
	free(attempt);
}

/*
** attempt_placement:
** - Loops through the board, checking each coordinate to see if piece
**   placement is possible.
** - Calls place_piece once all possible coordinates are attempted.
*/

void	attempt_placement(t_board *board, t_piece *piece)
{
	int	x;
	int	y;

	y = 0;
	if (piece->created)
	{
		while (y < board->y)
		{
			x = 0;
			while (x < board->x)
			{
				calculate_placement(board, piece, x, y);
				x++;
			}
			y++;
		}
		place_piece(piece);
	}
}
