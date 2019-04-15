/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:57:51 by mgreil            #+#    #+#             */
/*   Updated: 2017/12/16 17:11:43 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_matrice(t_matrice *m)
{
	m->a1 = 1;
	m->a2 = 0;
	m->a3 = 0;
	m->a4 = 0;
	m->b1 = 0;
	m->b2 = 1;
	m->b3 = 0;
	m->b4 = 0;
	m->c1 = 0;
	m->c2 = 0;
	m->c3 = 1;
	m->c4 = 0;
	m->d1 = 0;
	m->d2 = 0;
	m->d3 = 0;
	m->d4 = 1;
}

t_matrice	matrice_translation(double x, double y)
{
	t_matrice matrice;

	init_matrice(&matrice);
	matrice.a4 = x;
	matrice.b4 = y;
	return (matrice);
}

t_matrice	matrice_rotation(double x, double y, double z)
{
	t_matrice	matrice;

	init_matrice(&matrice);
	if (x)
	{
		matrice.b2 = cos(x);
		matrice.b3 = -sin(x);
		matrice.c2 = sin(x);
		matrice.c3 = cos(x);
	}
	else if (y)
	{
		matrice.a1 = cos(y);
		matrice.a3 = sin(y);
		matrice.c1 = -sin(y);
		matrice.c3 = cos(y);
	}
	else
	{
		matrice.a1 = cos(z);
		matrice.a2 = -sin(z);
		matrice.b1 = sin(z);
		matrice.b2 = cos(z);
	}
	return (matrice);
}

t_matrice	matrice_scale(double zoom, double zoom_z)
{
	t_matrice	matrice;

	init_matrice(&matrice);
	if (!zoom_z)
	{
		matrice.a1 = zoom;
		matrice.b2 = zoom;
		matrice.c3 = zoom;
	}
	else
	{
		matrice.c3 = zoom_z;
	}
	return (matrice);
}
