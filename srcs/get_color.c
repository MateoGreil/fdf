/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:56:23 by mgreil            #+#    #+#             */
/*   Updated: 2018/01/10 12:10:28 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_altitude_color(int z)
{
	int color;

	color = 0;
	if (z >= 0)
		color = BLUE;
	else if (z < 0 && z >= -9)
		color = GREEN_DARK;
	else if (z < -9 && z >= -49)
		color = GREEN;
	else if (z < -49 && z >= -99)
		color = GREEN_LIGHT;
	else if (z < -99 && z >= -159)
		color = BROWN_LIGHT;
	else if (z < -159 && z >= -279)
		color = BROWN;
	else if (z < -279 && z >= -529)
		color = BROWN_DARK;
	else if (z < -529)
		color = WHITE;
	return (color);
}

int	get_color_shift(int start, int end, int nb_color)
{
	char	dr;
	char	dg;
	char	db;
	int		shift;

	if (nb_color == 0)
		nb_color++;
	dr = (start / 256 / 256 % 256 - end / 256 / 256 % 256) / nb_color;
	dg = (start / 256 % 256 - end / 256 % 256) / nb_color;
	db = (start % 256 - end % 256) / nb_color;
	shift = dr * 256 * 256 + dg * 256 + db;
	return (shift);
}
