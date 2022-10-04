/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:29:41 by swilliam          #+#    #+#             */
/*   Updated: 2022/10/04 12:54:28 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"

typedef struct s_board
{
	int		player;
	int		opponent;
	int		**board;
	int		x;
	int		y;
	int		created;
}	t_board;

typedef struct s_piece
{
	int		**piece;
	int		x;
	int		y;
	int		best_x;
	int		best_y;
	int		best_distance;
	int		created;
	int		placed;
}	t_piece;

typedef struct s_attempt
{
	int		distance;
	int		overlap;
	int		x;
	int		y;
}	t_attempt;

/*
** Data
*/
t_board		*initialise_board(t_board *board);
t_piece		*initialise_piece(t_piece *piece);
t_attempt	*initialise_attempt(t_attempt *attempt);
void		reset_round(t_board *board, t_piece *piece);
void		end_game(t_board *board, t_piece *piece);

/*
** Input reading
*/
void		update_players(t_board *board, char *line_read);
void		allocate_map(t_board *board, char *line_read);
void		fill_map(t_board *board, char *line_read);
void		allocate_fill_piece(t_board *board, t_piece *piece,
				char *line_read);
void		fill_piece(t_board *board, t_piece *piece);

/*
** Heatmap
*/
void		create_heatmap(t_board *board);

/*
** Piece placement:
*/

void		attempt_placement(t_board *board, t_piece *piece);
void		place_piece(t_piece *piece);

#endif