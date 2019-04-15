/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 20:12:12 by mgreil            #+#    #+#             */
/*   Updated: 2017/12/15 16:18:22 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(int num_error)
{
	if (num_error == USAGE)
		ft_putendl("Usage : ./fdf-demo <filename> [ case_size z_size ]");
	else if (num_error == MAP)
		ft_putendl("Found wrong line length. Exiting.");
	else if (num_error == DATA)
		ft_putendl("No data found.");
	exit(-1);
}
