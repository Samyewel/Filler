/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:33:28 by swilliam          #+#    #+#             */
/*   Updated: 2021/12/12 17:17:05 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isascii:
** - Checks if the input integer is an ascii character.
*/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
