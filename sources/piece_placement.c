/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_placement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:30:39 by sam               #+#    #+#             */
/*   Updated: 2022/09/30 16:22:41 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filler.h"

void	place_piece(t_piece *piece)
{
	if (piece->created)
	{
		//ft_printf("%d %d\n", piece->best_y, piece->best_x);
		ft_putnbr(piece->best_y);
		ft_putchar(' ');
		ft_putnbr(piece->best_x);
		ft_putchar('\n');
	}
}

void	attempt_placement(t_filler *data, t_piece *piece, int x, int y)
{
	int	validate_x;
	int	validate_y;
	int	distance;
	int	overlap;

	validate_y = 0;
	distance = 0;
	overlap = 0;
	while (validate_y < piece->y)
	{
		validate_x = 0;
		while (validate_x < piece->x)
		{
			if (x + validate_x < data->board_x && y + validate_y < data->board_y)
			{
				if (piece->piece[validate_y][validate_x] < 0)
				{
					overlap += (data->board[y + validate_y][x + validate_x] == data->player);
					if (overlap > 1)
						return ;
					if (data->board[y + validate_y][x + validate_x] == data->opponent)
						return ;
					if (data->board[y + validate_y][x + validate_x] >= 0)
						distance += data->board[y + validate_y][x + validate_x];
				}
				validate_x++;
			}
			else
				return ;
		}
		validate_y++;
	}
	if (overlap == 1 && distance < piece->best_distance)
	{
		piece->best_distance = distance;
		piece->best_x = x;
		piece->best_y = y;
	}
}

void	calculate_placement(t_filler *data, t_piece *piece)
{
	int	x;
	int	y;

	if (piece->created)
	{
		y = 0;
		while (y < data->board_y)
		{
			x = 0;
			while (x < data->board_x)
			{
				attempt_placement(data, piece, x, y);
				x++;
			}
			y++;
		}
	}
}
