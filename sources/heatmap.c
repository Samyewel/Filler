/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:35:51 by sam               #+#    #+#             */
/*   Updated: 2022/09/30 13:59:58 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filler.h"

int		fill_space(t_filler *data, int y, int x, int len)
{
	if (data->board[y][x] == 0)
	{
		data->board[y][x] = len;
		return (1);
	}
	else
		return (0);
}

int	fill_neighbours(t_filler *data, int y, int x, int len)
{
	int	filled;

	filled = 0;
	if (x >= 0 && x < data->board_x)
		filled += fill_space(data, y, x + 1, len);
	if (x > 0 && x <= data->board_x)
	 	filled += fill_space(data, y, x - 1, len);
	if (y >= 0 && y < data->board_y - 1)
	 	filled += fill_space(data, y + 1, x, len);
	if (y > 0 && y <= data->board_y - 1)
	 	filled += fill_space(data, y - 1, x, len);
	if ((y > 0 && y <= data->board_y - 1) && (x > 0 && x <= data->board_x))
	 	filled += fill_space(data, y - 1, x - 1, len);
	if ((y > 0 && y <= data->board_y - 1) && (x >= 0 && x < data->board_x))
		filled += fill_space (data, y - 1, x + 1, len);
	if ((y >= 0 && y < data->board_y - 1) && (x > 0 && x <= data->board_x))
		filled += fill_space (data, y + 1, x - 1, len);
	if ((y >= 0 && y < data->board_y - 1) && (x >= 0 && x < data->board_x))
		filled += fill_space (data, y + 1, x + 1, len);
	return (filled);
}


int		process_heatmap(t_filler *data, int current, int len)
{
	int filled;
	int	x;
	int	y;

	filled = 0;
	y = 0;
	while (y < data->board_y)
	{
		x = 0;
		while (x < data->board_x)
		{
			if (data->board[y][x] == current)
				filled += fill_neighbours(data, y, x, len);
			x++;
		}
		y++;
	}
	return (filled);
}

void	create_heatmap(t_filler *data)
{
	int	current;
	int	len;

	current = data->opponent;
	len = 1;
	while (process_heatmap(data, current, len))
	{
		current = len;
		len++;
	}
}