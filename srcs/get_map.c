/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 20:18:43 by mgreil            #+#    #+#             */
/*   Updated: 2018/01/15 14:35:25 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_map(t_map *map)
{
	map->map = NULL;
	map->size_x = 0;
	map->size_y = 0;
	map->size_z = 0;
	map->z_max = INTMIN;
	map->z_min = INTMAX;
}

static void	free_line(void *line, size_t useless)
{
	useless = 0;
	free((char*)line);
}

t_map		get_map(char *path_file, t_env e)
{
	t_list	*b_list;
	t_map	map;
	int		ret;

	b_list = NULL;
	init_map(&map);
	if ((ret = read_to_lst(path_file, &b_list)) == -1 || ret == 0)
	{
		if (b_list)
			ft_lstdel(&b_list, &free_line);
		error(DATA);
		exit(-1);
	}
	map.size_y = ret;
	if (lst_to_map(&b_list, &map, e.color_type) == -1)
	{
		if (b_list)
			ft_lstdel(&b_list, &free_line);
		error(MAP);
		exit(-1);
	}
	ft_lstdel(&b_list, &free_line);
	map.size_z = map.z_max - map.z_min;
	map.center = &(map.map[map.size_y / 2][map.size_x / 2]);
	return (map);
}
