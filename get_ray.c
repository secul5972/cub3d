/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:40:25 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/12 13:00:26 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bresenham(t_cub3d_data *cub, int startX, int startY, int finishX, int finishY, int color)
{

	int x = startX;
	int y = startY;
	int Xfactor = finishX < startX ? -1 : 1;
	int Yfactor = finishY < startY ? -1 : 1;

	int w = abs(finishX - startX); // -300
	int h = abs(finishY - startY); // -200

	int f;

	if (w > h)
	{
		f = (2 * h) - w;
		for (x = startX; x != finishX; x += Xfactor)
		{
			if (f < 0)
			{
				f += 2 * h;
			}
			else
			{
				y += Yfactor;
				f += 2 * (h - w);
			}
			mlx_pixel_put(cub->mlx, cub->win, x, y, color);//0x00FFFF00
		}
	}
	else
	{
		f = (2 * w) - h;
		for (y = startY; y != finishY; y += Yfactor)
		{
			if (f < 0)
			{
				f += 2 * w;
			}
			else
			{
				x += Xfactor;
				f += 2 * (w - h);
			}
			mlx_pixel_put(cub->mlx, cub->win, x, y, color);
		}
	}
}

void	get_ray(t_cub3d_data *cub, int color)
{
	int		x;
	double	multiple;

	//plane vector
	//make_vec(&cub->plane, cub->cdir.y, -cub->cdir.x);
	x = 0;
	while (x < cub->w_width)
	{
		// ray vector
		multiple = 2 * x / (double)cub->w_width - 1; // -1 <= 2 * x / w < 1

		cub->ray.x = cub->cdir.x + cub->plane.x * multiple;
		cub->ray.y = cub->cdir.y + cub->plane.y * multiple;
		bresenham(cub, cub->cpos.x * cub->xrate, cub->cpos.y * cub->xrate,  (cub->cpos.x + cub->ray.x) * cub->xrate, (cub->cpos.y + cub->ray.y) * cub->xrate, color);
		//Before DDA

		//DDA
        dda(cub, cub->ray);
		x++;
	}
}
