/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:33:07 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/18 18:33:07 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
