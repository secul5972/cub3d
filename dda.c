/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:43:29 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/17 14:59:03 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_wall(t_cub3d_data *cub, int screenX, double cposToWallDist\
, t_vecd ray, int side)
{
	double	wall_len;
	int		wall_top;
	int		wall_bottom;
	int		h;
    int     dir_num;

    if (side && ray.x < 0)
        dir_num = 3;
    else if (side && ray.x >= 0)
        dir_num = 2;
    else if (!side && ray.y < 0)
        dir_num = 0;
    else
        dir_num = 1;

	wall_len = cub->w_height / cposToWallDist;
	wall_bottom = cub->w_height / 2 + wall_len / 2;
	if (wall_bottom >= cub->w_height)
		wall_bottom = cub->w_height;
	wall_top = cub->w_height / 2 - wall_len / 2;
	if (wall_top < 0)
		wall_top = 0;

	double texX;
	double texY;
	if (side == 0) texX = cub->cpos.x + cposToWallDist * ray.x;
    else           texX = cub->cpos.y + cposToWallDist * ray.y;
	texX = (texX - floor(texX)) * cub->dir_img[dir_num].t_width;
	h = wall_top;
	while (h <= wall_bottom)
	{
		texY = (double)(h - cub->w_height / 2 + wall_len / 2) / (cub->w_height / 2 + wall_len / 2 - cub->w_height / 2 + wall_len / 2) * cub->dir_img[dir_num].t_height ;
		cub->img.data_ptr[h * (int)cub->w_width + screenX] = cub->dir_img[dir_num].data_ptr[(int)texY * cub->dir_img[dir_num].t_width + (int)texX];
		h++;
	}
}

void	dda_init(t_cub3d_data *cub, t_dda_data *vec, t_vecd ray)
{
	vec->mappos.x = (int)cub->cpos.x;
	vec->mappos.y = (int)cub->cpos.y;
	vec->dlen.x = fabs(1 / ray.x);
	vec->dlen.y = fabs(1 / ray.y);
	if (ray.x > 0)
	{
		vec->dmappos.x = 1;
		vec->len.x = (vec->mappos.x + 1 - cub->cpos.x) * vec->dlen.x;
	}
	else
	{
		vec->dmappos.x = -1;
		vec->len.x = (cub->cpos.x - vec->mappos.x) * vec->dlen.x;
	}
	if (ray.y > 0)
	{
		vec->dmappos.y = 1;
		vec->len.y = (vec->mappos.y + 1 - cub->cpos.y) * vec->dlen.y;
	}
	else
	{
		vec->dmappos.y = -1;
		vec->len.y = (cub->cpos.y - vec->mappos.y) * vec->dlen.y;
	}
}

double	dist(t_cub3d_data *cub, t_vecd ray, t_dda_data vec)
{
	if (vec.side == 1)
		return ((vec.mappos.x - cub->cpos.x + (1 - vec.dmappos.x) / 2) / ray.x);
	else
		return ((vec.mappos.y - cub->cpos.y + (1 - vec.dmappos.y) / 2) / ray.y);
}

void	dda(t_cub3d_data *cub, t_vecd ray, int screenX, double wdist)
{
	t_dda_data	vec;

	dda_init(cub, &vec, ray);
	while (1)
	{
		if (vec.len.x < vec.len.y)
		{
			vec.mappos.x += vec.dmappos.x;
			vec.len.x += vec.dlen.x;
			vec.side = 1;
		}
		else
		{
			vec.mappos.y += vec.dmappos.y;
			vec.len.y += vec.dlen.y;
			vec.side = 0;
		}
		if (cub->map[vec.mappos.y][vec.mappos.x] == '1')
		{
			wdist = dist(cub, ray, vec);
			print_wall(cub, screenX, wdist, ray, vec.side);
			break ;
		}
	}
}
