/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_matrice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 19:24:43 by mgreil            #+#    #+#             */
/*   Updated: 2018/01/09 16:05:08 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	calc_one_position(t_matrice m, t_point *p, t_point *center)
{
	t_point	tmp;

	tmp.x = ((p->x - center->x) * m.a1 + (p->y - center->y) *
			m.a2 + (p->z - center->z) * m.a3 + p->s * m.a4) + center->x;
	tmp.y = ((p->x - center->x) * m.b1 + (p->y - center->y) *
			m.b2 + (p->z - center->z) * m.b3 + p->s * m.b4) + center->y;
	tmp.z = ((p->x - center->x) * m.c1 + (p->y - center->y) *
			m.c2 + (p->z - center->z) * m.c3 + p->s * m.c4) + center->z;
	p->x = tmp.x;
	p->y = tmp.y;
	p->z = tmp.z;
}

void		calc_positions(t_matrice m, t_env *e)
{
	int	x;
	int	y;

	y = 0;
	while (y < e->map.size_y)
	{
		x = 0;
		while (x < e->map.size_x)
		{
			calc_one_position(m, &(e->map.map[y][x]), e->map.center);
			x++;
		}
		y++;
	}
}

void		calc_new_position(int key, t_env *e)
{
	if (key == KEY_TRANSLATION_UP)
		calc_positions(matrice_translation(TRANSLATION_UP, 0), e);
	else if (key == KEY_TRANSLATION_DOWN)
		calc_positions(matrice_translation(TRANSLATION_DOWN, 0), e);
	else if (key == KEY_TRANSLATION_RIGHT)
		calc_positions(matrice_translation(0, TRANSLATION_RIGHT), e);
	else if (key == KEY_TRANSLATION_LEFT)
		calc_positions(matrice_translation(0, TRANSLATION_LEFT), e);
	else if (key == KEY_ROTATION_X_UP)
		calc_positions(matrice_rotation(ROTATION_X_UP, 0, 0), e);
	else if (key == KEY_ROTATION_X_DOWN)
		calc_positions(matrice_rotation(ROTATION_X_DOWN, 0, 0), e);
	else if (key == KEY_ROTATION_Y_UP)
		calc_positions(matrice_rotation(0, ROTATION_Y_UP, 0), e);
	else if (key == KEY_ROTATION_Y_DOWN)
		calc_positions(matrice_rotation(0, ROTATION_Y_DOWN, 0), e);
	else if (key == KEY_ROTATION_Z_UP)
		calc_positions(matrice_rotation(0, 0, ROTATION_Z_UP), e);
	else if (key == KEY_ROTATION_Z_DOWN)
		calc_positions(matrice_rotation(0, 0, ROTATION_Z_DOWN), e);
	else if (key == KEY_ZOOM_IN)
		calc_positions(matrice_scale(ZOOM_IN, 0), e);
	else if (key == KEY_ZOOM_OUT)
		calc_positions(matrice_scale(ZOOM_OUT, 0), e);
}
