/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:31:48 by sam               #+#    #+#             */
/*   Updated: 2022/09/22 14:36:51 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 42
# define FD_SIZE 4096
/*
** Inclusions
*/
# include "libft.h"
# include <unistd.h>
/*
** Prototypes
*/
int	get_next_line(const int fd, char **line);

#endif