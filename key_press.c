/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:00:04 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/16 11:52:53 by secul5972        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_esc(t_cub3d_data *cub)
{
	free_all(cub);
	exit(0);
	return (0);
}

void	reset_background(t_cub3d_data *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)cub->w_height / 2)
	{
		j = 0;
		while (j < (int)cub->w_width)
		{
			cub->img.data_ptr[i * (int)cub->w_width + j] = cub->ceiling_color;
			j++;
		}
		i++;
	}
	while (i < (int)cub->w_height)
	{
		j = 0;
		while (j < (int)cub->w_width)
		{
			cub->img.data_ptr[i * (int)cub->w_width + j] = cub->floor_color;
			j++;
		}
		i++;
	}
}

void	rotate(t_cub3d_data *cub, double direction)
{
	double	tmp;
	double	angle;

	tmp = cub->cdir.x;
	angle = cub->rotate_angle * cub->frameTime;
	if (direction < 0)
		angle = -angle;
	reset_background(cub);
	cub->cdir.x = cub->cdir.x * cos(angle) - cub->cdir.y * sin(angle);
	cub->cdir.y = tmp * sin(angle) + cub->cdir.y * cos(angle);
	tmp = cub->plane.x;
	//아래와 동일한데 계산이 빠름
	make_vec(&cub->plane, cub->cdir.y, -cub->cdir.x);
	// cub->plane.x = cub->plane.x * cos(angle) - cub->plane.y * sin(angle);
	// cub->plane.y = tmp * sin(angle) + cub->plane.y * cos(angle);
	ray_casting(cub);
}

void	move_ud(t_cub3d_data *cub, double direction)
{
	reset_background(cub);
	if (cub->map[(int)(cub->cpos.y + direction * cub->cdir.y * cub->frameTime)][(int)cub->cpos.x] == '0')
		cub->cpos.y += direction * cub->cdir.y * cub->frameTime;
	if (cub->map[(int)cub->cpos.y][(int)(cub->cpos.x + direction * cub->cdir.x * cub->frameTime)] == '0')
		cub->cpos.x += direction * cub->cdir.x * cub->frameTime;
	ray_casting(cub);
}

void	move_lr(t_cub3d_data *cub, double direction)
{
	reset_background(cub);
	if (cub->map[(int)(cub->cpos.y + direction * cub->plane.y * cub->frameTime)][(int)cub->cpos.x] == '0')
		cub->cpos.y += direction * cub->plane.y * cub->frameTime;
	if (cub->map[(int)cub->cpos.y][(int)(cub->cpos.x + direction * cub->plane.x * cub->frameTime)] == '0')
		cub->cpos.x += direction * cub->plane.x * cub->frameTime;
	ray_casting(cub);
}

int press_key(int keycode, t_cub3d_data *cub)
{
	if (keycode == KEY_W)
		move_ud(cub, 1);
	else if (keycode == KEY_S)
		move_ud(cub, -1);
	else if (keycode == KEY_A)
		move_lr(cub, -1);
	else if (keycode == KEY_D)
		move_lr(cub, 1);
	else if (keycode == KEY_LEFT)
		rotate(cub, 1);
	else if (keycode == KEY_RIGHT)
		rotate(cub, -1);
	else if (keycode == KEY_ESC)
		press_esc(cub);
	return (0);
}
/*
[cos (a) -sin (a)]
[sin (a) cos (a)]
*/