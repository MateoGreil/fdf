/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 00:25:59 by mgreil            #+#    #+#             */
/*   Updated: 2018/01/09 16:07:18 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img	new_image(void *mlx, int img_size_x, int img_size_y)
{
	t_img	img;

	img.img = NULL;
	img.img = mlx_new_image(mlx, img_size_x, img_size_y);
	img.data = NULL;
	img.data =
		mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);
	img.size_x = img_size_x;
	img.size_y = img_size_y;
	return (img);
}

void	del_image(void *mlx, t_img *img)
{
	mlx_destroy_image(mlx, img->img);
	img->img = NULL;
	img->data = NULL;
}

void	free_map(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->size_y)
	{
		free(map->map[y]);
		y++;
	}
	free(map->map);
	map->map = NULL;
	map->center = NULL;
}
