/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:46:08 by swilliam          #+#    #+#             */
/*   Updated: 2022/09/30 16:21:12 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filler.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

t_filler	*initialise_data(t_filler *data)
{
	data->board = NULL;
	data->player = 0;
	data->opponent = 0;
	data->board_x = 0;
	data->board_y = 0;
	data->test = NULL;
	data->testint1 = 0;
	data->testint2 = 0;
	return (data);
}

t_piece	*initialise_piece(t_piece *piece)
{
	piece->piece = NULL;
	piece->created = 0;
	piece->x = 0;
	piece->y = 0;
	piece->best_distance = 9999;
	piece->best_x = 9999;
	piece->best_y =	9999;
	return (piece);
}

void	free_array(t_filler *data, t_piece *piece)
{
	int	i;

	i = 0;
	while (i < data->board_y)
	{
		free(data->board[i]);
		i++;
	}
	free(data->board);
	i = 0;
	while (i < piece->y)
	{
		free(piece->piece[i]);
		i++;
	}
	free(piece->piece);
}

void	print_to_log(t_filler *data, t_piece *piece)
{
	FILE		*log;

	log = fopen("log", "a+");
	if (log == NULL)
	{
		printf("Error.");
		exit(1);
	}
	fprintf(log, "Player = %d || Opponent = %d\n", data->player, data->opponent);
	fprintf(log, "Plateau: %d %d\n", data->board_x, data->board_y);
	int	x = 0;
	int	y = 0;
	while (y < data->board_y)
	{
		x = 0;
		fprintf(log, "%03d: ", y);
		while (x < data->board_x)
			fprintf(log, "%2d ", data->board[y][x++]);
		fprintf(log, "\n");
		y++;
	}
	int	x2 = 0;
	int	y2 = 0;
	fprintf(log, "Piece %d %d:\n", piece->x, piece->y);
	while (y2 < piece->y)
	{
		x2 = 0;
		while (x2 < piece->x)
			fprintf(log, "%2d ", piece->piece[y2][x2++]);
		fprintf(log, "\n");
		y2++;
	}
	fprintf(log, "best_distance = %d\n", piece->best_distance);
	fprintf(log, "best_x = %d\nbest_y = %d\n", piece->best_x, piece->best_y);
	// fprintf(log, "test_x = %d\ntest_y = %d\n", data->testint1, data->testint2);
	// if (data->test)
	// {
	// 	fprintf(log, "test = %s\n", data->test);
	// 	ft_strdel(&data->test);
	// }
	fclose(log);
}

int	main(void)
{
	char 		*line_read;
	t_filler 	*data;
	t_piece		*piece;

	data = (t_filler *)malloc(sizeof(t_filler));
	piece = (t_piece *)malloc(sizeof(t_piece));
	if (!data && !piece)
		return (-1);
	initialise_data(data);
	initialise_piece(piece);
	line_read = NULL;
	while (get_next_line(0, &line_read) > 0)
	{
		update_players(data, line_read);
		allocate_map(data, line_read);
		create_heatmap(data);
		allocate_piece(data, piece, line_read);
		calculate_placement(data, piece);
		//place_piece(piece);
		ft_strdel(&line_read);
		if (piece->created)
			break ;
	}
	print_to_log(data, piece);
	free_array(data, piece);
	return (0);
}

/*
process:
	- set player numbers
	- get map size
	- create map
	- create heatmap (increment board values by 1 for every square away from opponents pieces)
	- store piece
	- calculate best placement of piece by finding the shortest length
	- place final piece coordinates (put x and y)

input received is:
	$$$ exec p1 : [../swilliam.filler]
	Plateau 15 17:
		01234567890123456
	000 .................
	001 .................
	002 .................
	003 .................
	004 .................
	005 .................
	006 .................
	007 .................
	008 ..O..............
	009 .................
	010 .................
	011 .................
	012 ..............X..
	013 .................
	014 .................
	Piece 2 2:
	.*
	**
*/
