/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:40:25 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/17 18:47:15 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting(t_cub3d_data *cub)
{
	int		x;
	double	multiple;

	x = 0;
	while (x < cub->w_width)
	{
		multiple = 2 * x / (double)cub->w_width - 1;
		cub->ray.x = cub->cdir.x + cub->plane.x * multiple;
		cub->ray.y = cub->cdir.y + cub->plane.y * multiple;
		dda(cub, cub->ray, x, 0);
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img_ptr, 0, 0);
}
