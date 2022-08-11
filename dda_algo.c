/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:43:29 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/11 17:41:41 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// draw cube func
void draw_box(t_cub3d_data *cub, t_vec v)
{
	for(int i = v.y * cub->yrate; i < (v.y + 1) * cub->yrate; i++)
	{
		for(int j = v.x * cub->xrate; j < (v.x + 1) * cub->xrate ; j++)
		{
			mlx_pixel_put(cub->mlx, cub->win, j, i, 0xFF000000);
		}
	}
}

// dda
void dda(t_cub3d_data *cub, t_vec ray)
{
	t_vec Xside;
	t_vec Yside;
	int Xsidedir;
	int Ysidedir;
	double c1;
	double c0;
	double Xlen;
	double Ylen;

	c1 = 0;
	if (ray.x != 0)
		c1 = ray.y / ray.x;
	c0 = ray.x * cub->cpos.y - ray.y * cub->cpos.x;


		Xside.x = (int)cub->cpos.x;
		Yside.y = (int)cub->cpos.y;
		if (ray.x == 0 && ray.y)
		{
			Xsidedir = 0;
			Xside.x = 0;
			Xside.y = 0;
			if (ray.y > 0)
				Ysidedir = 1;
			else
				Ysidedir = -1;
			Yside.y++;
		}
		else if (ray.x == 0 && ray.y)
		{
			Xsidedir = 1;
			Xside.x++;
		}
		else
			Xsidedir = -1;
		if (ray.x && ray.y)
			Xside.y = c1 * Xside.x + c0;
		else if (ray.x && ray.y == 0)
			Xside.y = cub->cpos.y;
		else
			Xside.y = 0;
	

		
		if (ray.y == 0)
		{
			Ysidedir = 0;
			Yside.y = 0;
		}
		else if (ray.y > 0)
		{
			Ysidedir = 1;
			Yside.y++;
		}
		else
			Ysidedir = -1;
		if (ray.y && ray.x)
			Yside.x = (Yside.y - c0) / c1;
		else if (ray.y && ray.x == 0)
			Yside.x = cub->cpos.x;
		else
			Yside.x = 0;


	Xlen = vec_scale(Xside);
	Ylen = vec_scale(Yside);
	printf("%f %f | %f %f | %f %f | %f %f | %d %d\n",cub->cpos.x, cub->cpos.y, ray.x, ray.y, Xside.x, Xside.y, Yside.x, Yside.y, Xsidedir, Ysidedir);
	while (1)
	{
		if (Xlen < Ylen)
		{
			if (cub->map[(int)Xside.y][(int)Xside.x] == '1')
			{
				draw_box(cub, Xside);
				break;
			}
			Xside.x += Xsidedir;
			Xside.y = c1 * Xside.x + c0;
			Xlen = vec_scale(Xside);

		}
		else
		{
			if (cub->map[(int)Yside.y][(int)Yside.x] == '1')
			{
				draw_box(cub, Yside);
				break;
			}
			Yside.y += Ysidedir;
			Yside.x = (Yside.y - c0) / c1;
			Ylen = vec_scale(Yside);
		}
	}
}