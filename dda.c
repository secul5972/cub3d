/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:43:29 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/17 15:55:35 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dda_data(t_cub3d_data *cub, t_dda_data *dda, \
double cposToWallDist)
{
	if (dda->side && dda->ray.x < 0)
		dda->img_num = 3;
	else if (dda->side && dda->ray.x >= 0)
		dda->img_num = 2;
	else if (!dda->side && dda->ray.y < 0)
		dda->img_num = 0;
	else
		dda->img_num = 1;
	dda->wall_len = cub->w_height / cposToWallDist;
	dda->wall_bot = cub->w_height / 2 + dda->wall_len / 2;
	dda->wd_bot = dda->wall_bot;
	if (dda->wall_bot >= cub->w_height)
		dda->wd_bot = cub->w_height;
	dda->wall_top = cub->w_height / 2 - dda->wall_len / 2;
	dda->wd_top = dda->wall_top;
	if (dda->wall_top < 0)
		dda->wd_top = 0;
}

void	print_wall(t_cub3d_data *cub, int screenX, double cposToWallDist, \
t_dda_data *dda)
{
	int		h;
	t_vecd	tex;

	set_dda_data(cub, dda, cposToWallDist);
	if (dda->side)
		tex.x = cub->cpos.y + cposToWallDist * dda->ray.y;
	else
		tex.x = cub->cpos.x + cposToWallDist * dda->ray.x;
	tex.x = (tex.x - floor(tex.x)) * cub->dir_img[dda->img_num].t_width;
	h = dda->wd_top;
	while (h <= dda->wd_bot)
	{
		tex.y = (double)(h - dda->wall_top) / (dda->wall_bot - dda->wall_top) \
		* cub->dir_img[dda->img_num].t_height ;
		cub->img.data_ptr[h * (int)cub->w_width + screenX] = \
		cub->dir_img[dda->img_num].data_ptr[(int)tex.y * \
		cub->dir_img[dda->img_num].t_width + (int)tex.x];
		h++;
	}
}

void	dda_init(t_cub3d_data *cub, t_dda_data *dda, t_vecd ray)
{
	dda->mappos.x = (int)cub->cpos.x;
	dda->mappos.y = (int)cub->cpos.y;
	dda->dlen.x = fabs(1 / ray.x);
	dda->dlen.y = fabs(1 / ray.y);
	if (ray.x > 0)
	{
		dda->dmappos.x = 1;
		dda->len.x = (dda->mappos.x + 1 - cub->cpos.x) * dda->dlen.x;
	}
	else
	{
		dda->dmappos.x = -1;
		dda->len.x = (cub->cpos.x - dda->mappos.x) * dda->dlen.x;
	}
	if (ray.y > 0)
	{
		dda->dmappos.y = 1;
		dda->len.y = (dda->mappos.y + 1 - cub->cpos.y) * dda->dlen.y;
	}
	else
	{
		dda->dmappos.y = -1;
		dda->len.y = (cub->cpos.y - dda->mappos.y) * dda->dlen.y;
	}
	make_vec(&dda->ray, ray.x, ray.y);
}

double	dist(t_cub3d_data *cub, t_dda_data dda)
{
	if (dda.side == 1)
		return ((dda.mappos.x - cub->cpos.x + \
		(1 - dda.dmappos.x) / 2) / dda.ray.x);
	else
		return ((dda.mappos.y - cub->cpos.y + \
		(1 - dda.dmappos.y) / 2) / dda.ray.y);
}

void	dda(t_cub3d_data *cub, t_vecd ray, int screenX, double wdist)
{
	t_dda_data	dda;

	dda_init(cub, &dda, ray);
	while (1)
	{
		if (dda.len.x < dda.len.y)
		{
			dda.mappos.x += dda.dmappos.x;
			dda.len.x += dda.dlen.x;
			dda.side = 1;
		}
		else
		{
			dda.mappos.y += dda.dmappos.y;
			dda.len.y += dda.dlen.y;
			dda.side = 0;
		}
		if (cub->map[dda.mappos.y][dda.mappos.x] == '1')
		{
			wdist = dist(cub, dda);
			print_wall(cub, screenX, wdist, &dda);
			break ;
		}
	}
}
