/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:29:41 by swilliam          #+#    #+#             */
/*   Updated: 2022/09/30 15:47:38 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include "ft_printf.h"
#include "libft.h"
#include "get_next_line.h"

typedef struct s_filler
{
	int		map_created;
	int		heatmap_created;
	int		**board;
	int		player;
	int		opponent;
	int		board_x;
	int		board_y;
	char	*test;
	int		testint1;
	int		testint2;

}	t_filler;

typedef struct s_piece
{
	int		**piece;
	int		created;
	int		x;
	int		y;
	int		best_distance;
	int		best_x;
	int		best_y;
}	t_piece;

/*
** DELETE BEFORE SUBMISSION
*/
void	print_to_log(t_filler *data, t_piece *piece);

/*
** Data
*/
t_filler	*initialise_data(t_filler *data);
t_piece		*initialise_piece(t_piece *piece);
void		free_array(t_filler *data, t_piece *piece);


/*
** Input reading
*/
void		update_players(t_filler *data, char *line_read);
void		allocate_map(t_filler *data, char *line_read);
void		create_map(t_filler *data);
void		allocate_piece(t_filler *data, t_piece *piece, char *line_read);
void		create_piece(t_filler *data, t_piece *piece);

/*
** Heatmap
*/
void		create_heatmap(t_filler *data);
int			fill_neighbours(t_filler *data, int y, int x, int len);
int			fill_space(t_filler *data, int y, int x, int len);
int			process_heatmap(t_filler *data, int current, int len);

/*
** Piece placement:
*/

void		calculate_placement(t_filler *data, t_piece *piece);
void		place_piece(t_piece *piece);
void	attempt_placement(t_filler *data, t_piece *piece, int x, int y);




#endif
