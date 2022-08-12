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

// dda
void dda(t_cub3d_data *cub, t_vec ray)
{
	t_vec mapPos;
	t_vec dmapPos;
	t_vec len;
	t_vec dlen;
	int side;
    double scale = vec_scale(ray);

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
            double a;
            if (side)
            {
                a = sqrt(len.x * len.x / (scale * scale));
                bresenham(cub, cub->cpos.x * cub->xrate, cub->cpos.y * cub->xrate,  (cub->cpos.x + a * ray.x)*cub->xrate,(cub->cpos.y + a * ray.y)*cub->xrate ,0x00FFFF00);
            }
            else
            {
                a = sqrt(len.y * len.y / (scale * scale));
                bresenham(cub, cub->cpos.x * cub->xrate, cub->cpos.y * cub->xrate,  (cub->cpos.x + a * ray.x)*cub->xrate,(cub->cpos.y + a * ray.y)*cub->xrate ,0x00FFFF00);
            }
            //printf("%f %d %d\n", a, (int)mapPos.y, (int)mapPos.x);
			break;
		}
	}
}