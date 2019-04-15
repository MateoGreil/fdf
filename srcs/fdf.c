/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 20:24:48 by mgreil            #+#    #+#             */
/*   Updated: 2018/01/15 14:16:04 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center(t_env *e)
{
	while (e->map.center->y < WIN_SIZE_Y / 2)
		calc_new_position(KEY_TRANSLATION_RIGHT, e);
	while (e->map.center->y > WIN_SIZE_Y / 2)
		calc_new_position(KEY_TRANSLATION_LEFT, e);
	while (e->map.center->x < WIN_SIZE_X / 2)
		calc_new_position(KEY_TRANSLATION_DOWN, e);
	while (e->map.center->x > WIN_SIZE_X / 2)
		calc_new_position(KEY_TRANSLATION_UP, e);
}

static void	put_key(void)
{
	ft_putendl(" _________________________");
	ft_putendl("| CONTROLS:               |");
	ft_putendl("| Translation:            |");
	ft_putendl("|    Y:   Key UP, DOWN    |");
	ft_putendl("|    X:   Key LEFT, RIGHT |");
	ft_putendl("|                         |");
	ft_putendl("| Rotation:               |");
	ft_putendl("|    X:   a, d            |");
	ft_putendl("|    Y:   w, s            |");
	ft_putendl("|    Z:   q, e            |");
	ft_putendl("|                         |");
	ft_putendl("| Zoom:                   |");
	ft_putendl("|    IN:  i               |");
	ft_putendl("|    OUT: o               |");
	ft_putendl("|                         |");
	ft_putendl("| Color:  c               |");
	ft_putendl("| Center: space           |");
	ft_putendl("|_________________________|");
}

static void	init_env(t_env *e, char **av)
{
	e->map_name = *av;
	e->mlx = NULL;
	e->win = NULL;
	e->screen = NULL;
	e->color_type = ALTITUDE_COLOR;
}

int			main(int ac, char **av)
{
	t_env	env;

	if (ac == 2)
	{
		put_key();
		init_env(&env, &(av[1]));
		env.map = get_map(env.map_name, env);
		env.mlx = mlx_init();
		env.win = mlx_new_window(env.mlx, WIN_SIZE_X, WIN_SIZE_Y, "fdf");
		env.img = new_image(env.mlx, WIN_SIZE_X, WIN_SIZE_Y);
		env.color_type = ALTITUDE_COLOR;
		center(&env);
		print_map_to_image(env);
		mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
		del_image(env.mlx, &(env.img));
		mlx_hook(env.win, KEY_PRESS, KEY_PRESS_MASK, &key_hook, &env);
		mlx_loop(env.mlx);
		free_map(&(env.map));
	}
	else
		error(USAGE);
}
