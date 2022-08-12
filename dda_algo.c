	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:43:29 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/12 12:38:14 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// draw cube func
void draw_box(t_cub3d_data *cub, t_vec v, int side)
{
	printf("%f %f\n", v.x * cub->xrate , v.y*cub->xrate);
	if (side)
	{
		bresenham(cub, v.x * cub->xrate, v.y* cub->xrate, (v.x + 1)* cub->xrate, v.y* cub->xrate, 0xFF00FF00);
	}
	else
	{
		bresenham(cub, v.x* cub->xrate, v.y* cub->xrate, v.x* cub->xrate, (v.y + 1)* cub->xrate, 0xFF00FF00);
	}
}

// dda
void dda(t_cub3d_data *cub, t_vec ray)
{
	t_vec mapPos;
	t_vec dmapPos;
	t_vec len;
	t_vec dlen;
	int side;

	mapPos.x = (int)cub->cpos.x;
	mapPos.y = (int)cub->cpos.y;

	dlen.x = fabs(vec_scale(ray) / ray.x);
	dlen.y = fabs(vec_scale(ray) / ray.y);

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
			side = 1;
		}
		else
		{
			mapPos.y += dmapPos.y;
			len.y += dlen.y;
			side = 0;
		}
		if (cub->map[(int)mapPos.y][(int)mapPos.y] == '1')
		{

			draw_box(cub, mapPos, side);
			break;
		}
	}
}