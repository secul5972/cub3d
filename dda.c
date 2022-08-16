/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:43:29 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/16 11:49:19 by secul5972        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_wall(t_cub3d_data *cub, int screenX, double cposToWallDist)
{
	double	wallLen;
	int		wallTop;
	int		wallBottom;

	wallLen = cub->w_height / cposToWallDist;
	wallBottom = cub->w_height / 2 + wallLen / 2;
	if (wallBottom >= cub->w_height)
		wallBottom = cub->w_height;
	wallTop = cub->w_height / 2 - wallLen / 2;
	if (wallTop < 0)
		wallTop = 0;
	while (wallTop <= wallBottom)
	{
		cub->img.data_ptr[wallTop * (int)cub->w_width + screenX] = 0xDC143C;
		wallTop++;
	}
}

void	dda_init(t_cub3d_data *cub, t_dda_data *vec, t_vecd ray)
{
	vec->mapPos.x = (int)cub->cpos.x;
	vec->mapPos.y = (int)cub->cpos.y;
	vec->dlen.x = fabs(1 / ray.x);
	vec->dlen.y = fabs(1 / ray.y);
	if (ray.x > 0)
	{
		vec->dmapPos.x = 1;
		vec->len.x = (vec->mapPos.x + 1 - cub->cpos.x) * vec->dlen.x;
	}
	else
	{
		vec->dmapPos.x = -1;
		vec->len.x = (cub->cpos.x - vec->mapPos.x) * vec->dlen.x;
	}
	if (ray.y > 0)
	{
		vec->dmapPos.y = 1;
		vec->len.y = (vec->mapPos.y + 1 - cub->cpos.y) * vec->dlen.y;
	}
	else
	{
		vec->dmapPos.y = -1;
		vec->len.y = (cub->cpos.y - vec->mapPos.y) * vec->dlen.y;
	}
}

double	dist(t_cub3d_data *cub, t_vecd ray, t_dda_data vec)
{
	if (vec.side == 1)
		return ((vec.mapPos.x - cub->cpos.x + (1 - vec.dmapPos.x) / 2) / ray.x);
	else
		return ((vec.mapPos.y - cub->cpos.y + (1 - vec.dmapPos.y) / 2) / ray.y);
}

void	dda(t_cub3d_data *cub, t_vecd ray, int screenX, double wdist)
{
	t_dda_data	vec;

	dda_init(cub, &vec, ray);
	while (1)
	{
		if (vec.len.x < vec.len.y)
		{
			vec.mapPos.x += vec.dmapPos.x;
			vec.len.x += vec.dlen.x;
			vec.side = 1;
		}
		else
		{
			vec.mapPos.y += vec.dmapPos.y;
			vec.len.y += vec.dlen.y;
			vec.side = 0;
		}
		if (cub->map[vec.mapPos.y][vec.mapPos.x] == '1')
		{
			wdist = dist(cub, ray, vec);
			print_wall(cub, screenX, wdist);
			break ;
		}
	}
}