/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:18:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/01/13 11:44:08 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	lim_zoom(t_env e)
{
	if (e.map.map[0][0].x > 0
	 && e.map.map[0][0].y > 0
	 && e.map.map[0][0].x < WIN_SIZE_X
	 && e.map.map[0][0].y < WIN_SIZE_Y
	 && e.map.map[e.map.size_y - 1][0].x > 0
	 && e.map.map[e.map.size_y - 1][0].y > 0
	 && e.map.map[e.map.size_y - 1][0].x < WIN_SIZE_X
	 && e.map.map[e.map.size_y - 1][0].y < WIN_SIZE_Y
	 && e.map.map[e.map.size_y - 1][e.map.size_x - 1].x > 0
	 && e.map.map[e.map.size_y - 1][e.map.size_x - 1].y > 0
	 && e.map.map[e.map.size_y - 1][e.map.size_x - 1].x < WIN_SIZE_X
	 && e.map.map[e.map.size_y - 1][e.map.size_x - 1].y < WIN_SIZE_Y
	 && e.map.map[0][e.map.size_x - 1].x > 0
	 && e.map.map[0][e.map.size_x - 1].y > 0
	 && e.map.map[0][e.map.size_x - 1].x < WIN_SIZE_X
	 && e.map.map[0][e.map.size_x - 1].y < WIN_SIZE_Y)
	{
		return (1);
	}
	return (0);
}

static void	key_func(int keycode, t_env *e)
{
	calc_new_position(keycode, e);
	e->img = new_image(e->mlx, WIN_SIZE_X, WIN_SIZE_Y);
	print_map_to_image(*e);
	mlx_put_image_to_window(e->win, e->win, e->img.img, 0, 0);
	del_image(e->mlx, &(e->img));
}

/*static void	scale_z(int keycode, t_env *e)
{
	if (keycode == KEY_ZOOM_Z_IN)
		calc_positions(matrice_scale(0, ZOOM_IN), e);
	else
		calc_positions(matrice_scale(0, ZOOM_OUT), e);
	mlx_destroy_image(e->mlx, e->img.img);
	e->img = new_image(e->mlx, WIN_SIZE_X, WIN_SIZE_Y);
	print_map_to_image(*e);
	mlx_put_image_to_window(e->win, e->win, e->img.img, 0, 0);
}*/

static void	change_color(t_env *e)
{
	e->color_type *= -1;
	free_map(&e->map);
	e->map = get_map(e->map_name, *e);
	e->img = new_image(e->mlx, WIN_SIZE_X, WIN_SIZE_Y);
	center(e);
	print_map_to_image(*e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img, 0, 0);
	del_image(e->mlx, &(e->img));
}

int			key_hook(int keycode, t_env *e)
{
	if (keycode == KEY_ECHAP)
	{
		free_map(&e->map);
		exit(0);
	}
	else if (keycode == KEY_COLOR)
		change_color(e);
	else if (keycode == KEY_CENTER)
	{
		center(e);
		e->img = new_image(e->mlx, WIN_SIZE_X, WIN_SIZE_Y);
		print_map_to_image(*e);
		mlx_put_image_to_window(e->win, e->win, e->img.img, 0, 0);
	}
	//else if (keycode == KEY_ZOOM_Z_IN || keycode == KEY_ZOOM_Z_OUT)
	//{
	//	scale_z(keycode, e);
	//}
	else if (keycode != KEY_ZOOM_IN || (keycode == KEY_ZOOM_IN && lim_zoom(*e)))
		key_func(keycode, e);
		
	return (0);
}
