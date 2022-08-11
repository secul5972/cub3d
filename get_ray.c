/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:40:25 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/11 15:39:45 by seungcoh         ###   ########.fr       */
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
	make_vec(&cub->plane, cub->cdir.y, -cub->cdir.x);
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
