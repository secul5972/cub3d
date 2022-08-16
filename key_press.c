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

void	rotate(t_cub3d_data *cub, double direction)
{
	double	tmp;
	double	angle;

	tmp = cub->cdir.x;
	angle = cub->rotate_angle * cub->frame_time;
	if (direction < 0)
		angle = -angle;
	reset_background(cub);
	cub->cdir.x = cub->cdir.x * cos(angle) - cub->cdir.y * sin(angle);
	cub->cdir.y = tmp * sin(angle) + cub->cdir.y * cos(angle);
	tmp = cub->plane.x;
	make_vec(&cub->plane, cub->cdir.y, -cub->cdir.x);
	ray_casting(cub);
}

void	move_y(t_cub3d_data *cub, double move_to)
{
	int	y;

	if (move_to < 0)
	{
		y = cub->cpos.y + move_to;
		if (y + EPS > cub->cpos.y + move_to)
			cub->cpos.y = y + EPS;
		else
			cub->cpos.y = cub->cpos.y + move_to;
	}
	else
	{
		y = cub->cpos.y + move_to + 1;
		if (y - EPS < cub->cpos.y + move_to)
			cub->cpos.y = y - EPS;
		else
			cub->cpos.y = cub->cpos.y + move_to;
	}
}

void	move_x(t_cub3d_data *cub, double move_to)
{
	int	x;

	if (move_to < 0)
	{
		x = cub->cpos.x + move_to;
		if (x + EPS > cub->cpos.x + move_to)
			cub->cpos.x = x + EPS;
		else
			cub->cpos.x = cub->cpos.x + move_to;
	}
	else
	{	
		x = cub->cpos.x + move_to + 1;
		if (x - EPS < cub->cpos.x + move_to)
			cub->cpos.x = x - EPS;
		else
			cub->cpos.x = cub->cpos.x + move_to;
	}
}

void	move(t_cub3d_data *cub, double move_to_y, double move_to_x)
{
	reset_background(cub);
	if (cub->map[(int)(cub->cpos.y + move_to_y)][(int)cub->cpos.x] == '0')
		move_y(cub, move_to_y);
	if (cub->map[(int)cub->cpos.y][(int)(cub->cpos.x + move_to_x)] == '0')
		move_x(cub, move_to_x);
	ray_casting(cub);
}

int	press_key(int keycode, t_cub3d_data *cub)
{
	if (keycode == KEY_W)
		move(cub, 1 * cub->cdir.y * cub->frame_time, \
		1 * cub->cdir.x * cub->frame_time);
	else if (keycode == KEY_S)
		move(cub, -1 * cub->cdir.y * cub->frame_time, \
		-1 * cub->cdir.x * cub->frame_time);
	else if (keycode == KEY_A)
		move(cub, -1 * cub->plane.y * cub->frame_time, \
		-1 * cub->plane.x * cub->frame_time);
	else if (keycode == KEY_D)
		move(cub, 1 * cub->plane.y * cub->frame_time, \
		1 * cub->plane.x * cub->frame_time);
	else if (keycode == KEY_LEFT)
		rotate(cub, 1);
	else if (keycode == KEY_RIGHT)
		rotate(cub, -1);
	else if (keycode == KEY_ESC)
		press_esc(cub);
	return (0);
}
