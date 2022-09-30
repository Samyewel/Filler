/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:36:58 by sam               #+#    #+#             */
/*   Updated: 2022/09/30 14:29:11 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filler.h"

void	update_players(t_filler *data, char *line_read)
{
	if (ft_strstr(line_read, "$$$"))
	{
		data->player = ft_atoi(&line_read[10]) * -1;
		if (data->player == -1)
			data->opponent = -2;
		else if (data->player == -2)
			data->opponent = -1;
	}
}

void	allocate_map(t_filler *data, char *line_read)
{
	char **map_size_split;
	int	i;

	map_size_split = NULL;
	i = 0;
	if (ft_strstr(line_read, "Plateau"))
	{
		map_size_split = ft_strsplit(line_read, ' ');
		if (!map_size_split)
			return ;
		data->board_y = ft_atoi(map_size_split[1]);
		data->board_x = ft_atoi(map_size_split[2]);
		ft_arrdel(map_size_split);
		data->board = (int **)malloc(sizeof(int *) * data->board_y);
		while(i < data->board_y)
		{
			data->board[i] = (int *)ft_memalloc(sizeof(int) * data->board_x);
			i++;
		}
		create_map(data);
	}
}

void	create_map(t_filler *data)
{
	char	*map_reading;
	int		x;
	int		y;

	map_reading = NULL;
	y = -1;
	while (get_next_line(0, &map_reading) > 0)
	{
		if (y >= 0)
		{
			x = 0;
			while (x < data->board_x)
			{
				if (map_reading[x + 4] == 'o'
						|| map_reading[x + 4] == 'O')
					data->board[y][x] = -1;
				if (map_reading[x + 4] == 'x'
						|| map_reading[x + 4] == 'X')
					data->board[y][x] = -2;
				x++;
			}
		}
		ft_strdel(&map_reading);
		if (y++ == data->board_y - 1)
			break ;
	}
}

void	allocate_piece(t_filler *data, t_piece *piece, char *line_read)
{
	char	**piece_split;
	int		i;

	piece_split = NULL;
	i = 0;
	if (ft_strstr(line_read, "Piece"))
	{
		piece_split = ft_strsplit(line_read, ' ');
		if (!piece_split)
			return ;
		piece->y = ft_atoi(piece_split[1]);
		piece->x = ft_atoi(piece_split[2]);
		ft_arrdel(piece_split);
		piece->piece = (int **)malloc(sizeof(int *) * piece->y);
		while (i < piece->y)
		{
			piece->piece[i] = (int *)ft_memalloc(sizeof(int) * piece->x);
			i++;
		}
		create_piece(data, piece);
	}
}

void	create_piece(t_filler *data, t_piece *piece)
{
	char	*piece_reading;
	int		x;
	int		y;

	piece_reading = NULL;
	y = 0;
	while (get_next_line(0, &piece_reading) > 0)
	{
		x = 0;
		while (x < piece->x)
		{
			if (piece_reading[x] == '*')
				piece->piece[y][x] = data->player;
			x++;
		}
		ft_strdel(&piece_reading);
		if (y++ == piece->y)
			break ;
	}
	piece->created = 1;
}
