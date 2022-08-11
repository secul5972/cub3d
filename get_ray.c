/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:40:25 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/11 14:59:07 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_ray(t_cub3d_data *cub)
{
	t_vec	ray;
	int		x;
	double	plane;
	double	multiple;

	//plane vector
	plane = 0.66;
	if (cub->cdir.x < 0)
		make_vec(&cub->plane, 0, plane);
	else if (cub->cdir.x > 0)
		make_vec(&cub->plane, 0, -plane);
	else if (cub->cdir.y < 0)
		make_vec(&cub->plane, plane, 0);
	else if (cub->cdir.y > 0)
		make_vec(&cub->plane, -plane, 0);
	x = 0;
	while (x < cub->w_width)
	{
		// ray vector
		multiple = 2 * x / (double)cub->w_width - 1; // -1 <= 2 * x / w < 1
		ray.x = cub->cdir.x + cub->plane.x * multiple;
		ray.y = cub->cdir.y + cub->plane.y * multiple;
		printf("rayX: %f, rayY: %f\n", ray.x, ray.y);

		//Before DDA

		//DDA
		x++;
	}
}
