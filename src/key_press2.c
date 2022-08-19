/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:37:08 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/19 12:57:40 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_x_button(t_cub3d_data *cub)
{
	free_all(cub);
	system("leaks cub3D");
	exit(0);
	return (0);
}

int	press_esc(t_cub3d_data *cub)
{
	free_all(cub);
	system("leaks cub3D");
	exit(0);
	return (0);
}

void	reset_background(t_cub3d_data *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)cub->w_height / 2)
	{
		j = 0;
		while (j < (int)cub->w_width)
		{
			cub->img.data_ptr[i * (int)cub->w_width + j] = cub->ceiling_color;
			j++;
		}
		i++;
	}
	while (i < (int)cub->w_height)
	{
		j = 0;
		while (j < (int)cub->w_width)
		{
			cub->img.data_ptr[i * (int)cub->w_width + j] = cub->floor_color;
			j++;
		}
		i++;
	}
}
