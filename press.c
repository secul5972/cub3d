/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:00:04 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/11 17:38:38 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int press_esc(t_cub3d_data *cub)
{
	//free_all(cub);
	exit(0);
	return (0);
}

int press_key(int keycode, t_cub3d_data *cub)
{
	if (keycode == KEY_W)
	{
		if (cub->map[(int)cub->cpos.y - 1][(int)cub->cpos.x] == '0')
		{
			get_ray(cub, 0x00000000);
			cub->cpos.y--;
			get_ray(cub, 0x00FFFF00);
		}
	}
	else if (keycode == KEY_A)
	{
		if (cub->map[(int)cub->cpos.y][(int)cub->cpos.x - 1] == '0')
		{
			get_ray(cub, 0x00000000);
			cub->cpos.x-= 0.1;
			get_ray(cub, 0x00FFFF00);
		}
	}
	else if (keycode == KEY_S)
	{
		if (cub->map[(int)cub->cpos.y + 1][(int)cub->cpos.x] == '0')
		{
			get_ray(cub, 0x00000000);
			cub->cpos.y++;
			get_ray(cub, 0x00FFFF00);
		}
	}
	else if (keycode == KEY_D)
	{
		if (cub->map[(int)cub->cpos.y][(int)cub->cpos.x + 1] == '0')
		{
			get_ray(cub, 0x00000000);
			cub->cpos.x++;
			get_ray(cub, 0x00FFFF00);
		}
	}
	else if (keycode == KEY_LEFT)
	{
		get_ray(cub, 0x00000000);
		double tmp = cub->cdir.x;
		cub->cdir.x = cub->cdir.x * cos(cub->rotate) - cub->cdir.y * sin(cub->rotate);
		cub->cdir.y = tmp * sin(cub->rotate) + cub->cdir.y * cos(cub->rotate);
		tmp = cub->plane.x;
		cub->plane.x = cub->plane.x * cos(cub->rotate) - cub->plane.y * sin(cub->rotate);
		cub->plane.y = tmp * sin(cub->rotate) + cub->plane.y * cos(cub->rotate);
		get_ray(cub, 0x00FFFF00);
	}
	else if (keycode == KEY_RIGHT)
	{
		get_ray(cub, 0x00000000);
		double tmp = cub->cdir.x;
		cub->cdir.x = cub->cdir.x * cos(-cub->rotate) - cub->cdir.y * sin(-cub->rotate);
		cub->cdir.y = tmp * sin(-cub->rotate) + cub->cdir.y * cos(-cub->rotate);
		tmp = cub->plane.x;
		cub->plane.x = cub->plane.x * cos(-cub->rotate) - cub->plane.y * sin(-cub->rotate);
		cub->plane.y = tmp * sin(-cub->rotate) + cub->plane.y * cos(-cub->rotate);
		get_ray(cub, 0x00FFFF00);
	}
	else if (keycode == KEY_ESC)
		press_esc(cub);
	return (0);
}
/*
[cos (a) -sin (a)]
[sin (a) cos (a)]
*/