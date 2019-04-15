/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:21:54 by mgreil            #+#    #+#             */
/*   Updated: 2018/01/15 15:35:13 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	**init_map(int size_x, int size_y)
{
	t_point	**map;
	int	i;

	map = (t_point**)malloc(sizeof(t_point*) * size_y);
	i = 0;
	while (i < size_y)
	{
		map[i] = (t_point*)malloc(sizeof(t_point) * size_x);
		i++;
	}
	return (map);
}

static int	calc_size_x(char *line)
{
	int	i;
	int	size_x;

	size_x = 0;
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i])
			size_x++;
		while (line[i] && !ft_isspace(line[i]))
			i++;
	}
	return (size_x);
}

static int	get_color(char *str, int z, char color_type)
{
	int color;
	int	i;

	if (color_type == MAP_COLOR)
	{
		i = 0;
		while (str[i] && str[i] != ',' && str[i] != ' ')
			i++;
		if (!str[i] || str[i] == ' ')
			return (WHITE);
		i += 3;
		color = ft_atoi_base(str + i, 16);
	}
	else
	{
		color = get_altitude_color(z);
	}
	return (color);
}

static int	one_elem_to_map(t_list *alst, t_map *map, int y, char color_type)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (ft_isspace(((char*)alst->content)[i]))
		i++;
	while (((char*)alst->content)[i])
	{
		map->map[y][x].x = x;
		map->map[y][x].y = y;
		map->map[y][x].z = -ft_atoi(alst->content + i);
		map->map[y][x].s = 1;
		map->map[y][x].color = get_color(alst->content + i, map->map[y][x].z, color_type);
		if (map->map[y][x].z > map->z_max)
			map->z_max = map->map[y][x].z;
		if (map->map[y][x].z < map->z_min)
			map->z_min = map->map[y][x].z;
		while (((char*)alst->content)[i] && !ft_isspace(((char*)alst->content)[i]))
			i++;
		while (ft_isspace(((char*)alst->content)[i]))
			i++;
		x++;
	}
	//free(alst->content);
	return (x);
}

int	lst_to_map(t_list **b_list, t_map *map, char color_type)
{
	t_list	*elem;
	int	y;

	elem = *b_list;
	map->size_x = calc_size_x((*b_list)->content);
	map->map = init_map(map->size_x, map->size_y);
	y = 0;
	while (elem)
	{
		if (one_elem_to_map(elem, map, y, color_type) != map->size_x)
			return (-1);
		elem = elem->next;
		y++;
	}
	return (0);
}
