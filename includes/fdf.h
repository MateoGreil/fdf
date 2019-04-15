/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 17:01:27 by mgreil            #+#    #+#             */
/*   Updated: 2018/01/09 18:15:38 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define INTMAX 2147483647
# define INTMIN -2147483648

# define WIN_SIZE_X 1920
# define WIN_SIZE_Y 1080
# define DIST 10000

# define USAGE 0
# define DATA 1
# define MAP 2

# define KEY_PRESS 2
# define KEY_PRESS_MASK (1L<<6)

# define KEY_ECHAP 53
# define KEY_TRANSLATION_UP 123
# define KEY_TRANSLATION_DOWN 124
# define KEY_TRANSLATION_RIGHT 125
# define KEY_TRANSLATION_LEFT 126
# define KEY_ROTATION_X_UP 91
# define KEY_ROTATION_X_DOWN 84
# define KEY_ROTATION_Y_UP 88
# define KEY_ROTATION_Y_DOWN 86
# define KEY_ROTATION_Z_UP 89
# define KEY_ROTATION_Z_DOWN 92
# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78
# define KEY_COLOR 8
# define KEY_CENTER 87
# define KEY_ZOOM_Z_IN 46
# define KEY_ZOOM_Z_OUT 45

# define TRANSLATION_UP -10
# define TRANSLATION_DOWN 10
# define TRANSLATION_RIGHT 10
# define TRANSLATION_LEFT -10
# define ROTATION_X_UP -M_PI / 64
# define ROTATION_X_DOWN M_PI / 64
# define ROTATION_Y_UP -M_PI / 64
# define ROTATION_Y_DOWN M_PI / 64
# define ROTATION_Z_UP -M_PI / 64
# define ROTATION_Z_DOWN M_PI / 64
# define ZOOM_IN 1.1
# define ZOOM_OUT 0.9

# define BLUE  				0x000092FF
# define GREEN_DARK		0x00114912
# define GREEN				0x001D8D1F
# define GREEN_LIGHT	0x002EDF31
# define BROWN_LIGHT	0x00DF902E
# define BROWN				0x0098621E
# define BROWN_DARK		0x00563712
# define WHITE				0x00FFFFFF

# define ALTITUDE_COLOR -1
# define MAP_COLOR 1

typedef struct	s_matrice
{
	double	a1;
	double	a2;
	double	a3;
	double	a4;
	double	b1;
	double	b2;
	double	b3;
	double	b4;
	double	c1;
	double	c2;
	double	c3;
	double	c4;
	double	d1;
	double	d2;
	double	d3;
	double	d4;
}				t_matrice;

typedef struct	s_point
{
	double	x;
	double	y;
	double	z;
	double	s;
	int		color;
}				t_point;

typedef struct	s_map
{
	t_point	**map;
	int		size_x;
	int		size_y;
	int		size_z;
	int		z_max;
	int		z_min;
	t_point	*center;
}				t_map;

typedef struct	s_img
{
	void	*img;
	char	*data;
	int		size_x;
	int		size_y;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;

typedef struct	s_env
{
	char	*map_name;
	void	*mlx;
	void	*win;
	t_map	map;
	t_point	**screen;
	t_img	img;
	char	color_type;
}				t_env;

t_map			get_map(char *path_file, t_env env);
int				lst_to_map(t_list **b_list, t_map *map, char color_type);

t_matrice		matrice_translation(double x, double y);
t_matrice		matrice_rotation(double x, double y, double z);
t_matrice		matrice_scale(double zoom, double zoom_y);

void			calc_new_position(int key, t_env *e);
void			calc_positions(t_matrice m, t_env *e);

t_img			new_image(void *mlx, int img_size_x, int img_size_y);
void			draw_line_to_image(t_img *img, t_point p1, t_point p2);
void			print_map_to_image(t_env env);

int				get_color_shift(int start, int end, int nb_color);
int				get_altitude_color(int z);

int				key_hook(int keycode, t_env *env);

void			error(int num_error);

void			del_image(void *mlx, t_img *img);
void			free_map(t_map *map);

void			center(t_env *e);

#endif
