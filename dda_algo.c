/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:43:29 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/11 20:36:20 by secul5972        ###   ########.fr       */
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
	t_vec mapPos;
	t_vec dmapPos;
	t_vec len;
	t_vec dlen;

	mapPos.x = (int)cub->cpos.x;
	mapPos.y = (int)cub->cpos.y;

	dlen.x = abs(vec_scale(ray)/ray.x);
	dlen.y = abs(vec_scale(ray)/ray.y);

	if (ray.x > 0)
	{
		dmapPos.x = 1;
		len.x = (mapPos.x + 1 - cub->cpos.x) * dlen.x;
	}
	else
	{
		dmapPos.x = -1;
		len.x = (cub->cpos.x - mapPos.x) * dlen.x;
	}
	
	if (ray.y > 0)
	{
		dmapPos.y = 1;
		len.y = (mapPos.y + 1 - cub->cpos.y) * dlen.y;
	}
	else
	{
		dmapPos.y = -1;
		len.y = (cub->cpos.y - mapPos.y) * dlen.y;
	}

	while (1)
	{
		if (len.x < len.y)
		{
			mapPos.x += dmapPos.x;
			len.x += dlen.x;
		}
		else
		{
			mapPos.y += dmapPos.y;
			len.y += dlen.y;
		}
		if (cub->map[(int)mapPos.y][(int)mapPos.y] == '1')
		{
			draw_box(cub, mapPos);
			break;
		}
	}
}