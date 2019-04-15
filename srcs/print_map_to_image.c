/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_to_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 19:50:27 by mgreil            #+#    #+#             */
/*   Updated: 2018/01/10 12:09:10 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	convert(t_env e, int x, int y)
{
	t_point p;

	p.x = (DIST * (e.map.map[y][x].x - WIN_SIZE_X / 2))
		/ (DIST + e.map.map[y][x].z) + WIN_SIZE_X / 2;
	p.y = (DIST * (e.map.map[y][x].y - WIN_SIZE_Y / 2))
		/ (DIST + e.map.map[y][x].z) + WIN_SIZE_Y / 2;
	p.z = e.map.map[y][x].z;
	p.color = e.map.map[y][x].color;
	return (p);
}

static t_point	**convert_map_coord_to_screen(t_env e)
{
	t_point	**screen;
	int		x;
	int		y;

	screen = (t_point**)malloc(sizeof(t_point*) * e.map.size_y);
	y = 0;
	while (y < e.map.size_y)
	{
		screen[y] = (t_point*)malloc(sizeof(t_point) * e.map.size_x);
		y++;
	}
	y = 0;
	while (y < e.map.size_y)
	{
		x = 0;
		while (x < e.map.size_x)
		{
			screen[y][x] = convert(e, x, y);
			x++;
		}
		y++;
	}
	return (screen);
}

static void		free_screen(t_env e, t_point **screen)
{
	int	y;

	y = 0;
	while (y < e.map.size_y)
	{
		free(screen[y]);
		y++;
	}
	free(screen);
}

void			print_map_to_image(t_env e)
{
	t_point	**screen;
	int		x;
	int		y;

	screen = NULL;
	screen = convert_map_coord_to_screen(e);
	y = 0;
	while (y < e.map.size_y)
	{
		x = 0;
		while (x < e.map.size_x)
		{
			if (x + 1 < e.map.size_x)
				draw_line_to_image(&e.img, screen[y][x], screen[y][x + 1]);
			if (y + 1 < e.map.size_y)
			{
				draw_line_to_image(&e.img, screen[y][x], screen[y + 1][x]);
			}
			x++;
		}
		y++;
	}
	free_screen(e, screen);
}
