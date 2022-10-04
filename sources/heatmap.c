/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:35:51 by sam               #+#    #+#             */
/*   Updated: 2022/10/04 14:42:56 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filler.h"

/*
** fill_space:
** - Sets the given space to the number correlating to its distance from an
**   opponents piece.
*/

static int	fill_space(t_board *board, int y, int x, int len)
{
	if (board->board[y][x] == 0)
	{
		board->board[y][x] = len;
		return (1);
	}
	else
		return (0);
}

/*
** fill_neighbours:
** - Checks every neighbouring space from the current coordinates, filling it
**   with the increasing number correlating to its distance from an opponents
**   piece if possible.
*/

static int	fill_neighbours(t_board *board, int y, int x, int len)
{
	int	filled;
	int	y_bounds;
	int	x_bounds;

	y_bounds = board->y - 1;
	x_bounds = board->x - 1;
	filled = 0;
	if (x >= 0 && x < x_bounds)
		filled += fill_space(board, y, x + 1, len);
	if (x > 0 && x <= x_bounds)
		filled += fill_space(board, y, x - 1, len);
	if (y >= 0 && y < y_bounds)
		filled += fill_space(board, y + 1, x, len);
	if (y > 0 && y <= y_bounds)
		filled += fill_space(board, y - 1, x, len);
	if ((y > 0 && y <= y_bounds) && (x > 0 && x <= x_bounds))
		filled += fill_space(board, y - 1, x - 1, len);
	if ((y > 0 && y <= y_bounds) && (x >= 0 && x < x_bounds))
		filled += fill_space (board, y - 1, x + 1, len);
	if ((y >= 0 && y < y_bounds) && (x > 0 && x <= x_bounds))
		filled += fill_space (board, y + 1, x - 1, len);
	if ((y >= 0 && y < y_bounds) && (x >= 0 && x < x_bounds))
		filled += fill_space (board, y + 1, x + 1, len);
	return (filled);
}

/*
** process_heatmap:
** - Loops through the board filling each space with a number correlating to
**   it's distance from an opponents piece.
** - Initially starts by locating the opponents piece, filling all neighbour
**   spaces as 1.
** - Once all of the opponents pieces are located, the neighbour spaces are
**   then filled as two, and so on.
**
**   Example:
**   3 -1  3  3  3
**   3  2  2  2  2
**   3  2  1  1  1
**   3  2  1 -2  1
*/

static int	process_heatmap(t_board *board, int current, int len)
{
	int	filled;
	int	x;
	int	y;

	filled = 0;
	y = 0;
	while (y < board->y)
	{
		x = 0;
		while (x < board->x)
		{
			if (board->board[y][x] == current)
				filled += fill_neighbours(board, y, x, len);
			x++;
		}
		y++;
	}
	return (filled);
}

/*
** create_heatmap:
** - Loops through process_heatmap until it is no longer possible to fill
**   any more of the board.
** - To calculate the distance from an opponents piece, fill the map with
**   numbers, increasing by one for every coordinate away from a piece we
**   are.
*/

void	create_heatmap(t_board *board)
{
	int	current;
	int	len;

	current = board->opponent;
	len = 1;
	while (process_heatmap(board, current, len))
	{
		current = len;
		len++;
	}
}
