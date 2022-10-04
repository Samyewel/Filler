/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:36:58 by sam               #+#    #+#             */
/*   Updated: 2022/10/04 14:41:01 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filler.h"

/*
** update_players:
** - Reads the input information from standard output, assinging the player
**   as either -1 or -2 depending on which player they are given.
** - Once the map is created, -1 and -2 are used to mark player positions
**   to prevent collision and provide more precise algorithm execution.
*/

void	update_players(t_board *board, char *line_read)
{
	if (ft_strstr(line_read, "$$$") && board->player == 0)
	{
		board->player = ft_atoi(&line_read[10]) * -1;
		if (board->player == -1)
			board->opponent = -2;
		else if (board->player == -2)
			board->opponent = -1;
		ft_strdel(&line_read);
	}
}

/*
** allocate_map:
** - Reads the line "Plateau Y X:" from standard output, creating a zero-filled
**   map using the read coordinates.
*/

void	allocate_map(t_board *board, char *line_read)
{
	char	**map_size_split;
	int		i;

	map_size_split = NULL;
	i = 0;
	if (ft_strstr(line_read, "Plateau") && board->board == NULL)
	{
		map_size_split = ft_strsplit(line_read, ' ');
		if (!map_size_split)
			return ;
		board->y = ft_atoi(map_size_split[1]);
		board->x = ft_atoi(map_size_split[2]);
		ft_arrdel(map_size_split);
		board->board = (int **)malloc(sizeof(int *) * board->y);
		while (i < board->y)
		{
			board->board[i] = (int *)ft_memalloc(sizeof(int) * board->x);
			i++;
		}
	}
}

/*
** Fill_map:
** - Adds -1 and -2 to the coordinate in which location a player or opponents
**   piece is located.
*/

void	fill_map(t_board *board, char *line_read)
{
	char	*map_reading;
	int		x;
	int		y;

	map_reading = NULL;
	y = 0;
	if (ft_strstr(line_read, "    "))
	{
		while (get_next_line(0, &map_reading) > 0)
		{
			x = 0;
			while (x < board->x)
			{
				if (map_reading[x + 4] == 'o' || map_reading[x + 4] == 'O')
					board->board[y][x] = -1;
				if (map_reading[x + 4] == 'x' || map_reading[x + 4] == 'X')
					board->board[y][x] = -2;
				x++;
			}
			ft_strdel(&map_reading);
			if (++y == board->y)
				break ;
		}
		create_heatmap(board);
	}
}

/*
** allocate_piece:
** - Reads the input line "Piece Y X:", gathering the Y and X coordinates and
**   creates a zero-filled piece using them.
** - Calls fill_piece to fill the blank piece.
*/

void	allocate_fill_piece(t_board *board, t_piece *piece, char *line_read)
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
		fill_piece(board, piece);
	}
}

/*
** fill_piece:
** - Reads the input information, filling the blank piece with the players
**   corresponding ID if an asterisk '*' is found.
** - The periods '.' are left as zeroes.
** - Sets piece->created as a trigger for when piece placement should be
**   attempted.
*/

void	fill_piece(t_board *board, t_piece *piece)
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
				piece->piece[y][x] = board->player;
			x++;
		}
		ft_strdel(&piece_reading);
		if (++y == piece->y)
			break ;
	}
	piece->created = 1;
}
