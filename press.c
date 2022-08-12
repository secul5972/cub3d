/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:00:04 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/12 14:55:46 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int press_esc(t_cub3d_data *cub)
{
	//free_all(cub);
	exit(0);
	return (0);
}

void	reset_black(t_cub3d_data *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)cub->w_height)
	{
		j = 0;
		while (j < (int)cub->w_width)
		{
			cub->img.data_ptr[i * (int)cub->w_width + j] = 0;
			//mlx_pixel_put(cub->mlx, cub->win, j, i, 0x00000000);
			j++;
		}
		i++;
	}
    mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img_ptr, 0, 0);

    for(int i=0;i<cub->m_height;i++)
    {
        for(int j=0;j<cub->m_width;j++)
        {
            if (cub->map[i][j] == '1')
            {
                //printf("%d %d\n", i, j);
                for(int a = i * cub->xrate; a < (i+1)*cub->xrate;a++)
                {
                    for(int b = j * cub->xrate; b < (j+1)*cub->xrate;b++)
                    {
                        mlx_pixel_put(cub->mlx, cub->win, b, a, 0xFF0000);
                    }
                }
            }
        }
    }
}

void rotate(t_cub3d_data *cub, double direction)
{
	double tmp;
	double angle;

	tmp = cub->cdir.x;
	angle = cub->rotate_angle * cub->frameTime;
	if (direction < 0)
		angle = -angle;
	reset_black(cub);
	cub->cdir.x = cub->cdir.x * cos(angle) - cub->cdir.y * sin(angle);
	cub->cdir.y = tmp * sin(angle) + cub->cdir.y * cos(angle);
	tmp = cub->plane.x;
	cub->plane.x = cub->plane.x * cos(angle) - cub->plane.y * sin(angle);
	cub->plane.y = tmp * sin(angle) + cub->plane.y * cos(angle);
	get_ray(cub, 0x00FFFF00);
}

void	move(t_cub3d_data *cub, char target, double direction)
{
	reset_black(cub);
	if (target == 'x')
		cub->cpos.x += direction * cub->frameTime;
	else
		cub->cpos.y += direction * cub->frameTime;
	get_ray(cub, 0x00FFFF00);
}

int press_key(int keycode, t_cub3d_data *cub)
{

	if (keycode == KEY_W)
	{
		if (cub->map[(int)(cub->cpos.y + -1 * cub->frameTime)][(int)cub->cpos.x] == '0')
			move(cub, 'y', -1);
	}
	else if (keycode == KEY_A)
	{
		if (cub->map[(int)(cub->cpos.y)][(int)(cub->cpos.x - 1 * cub->frameTime)] == '0')
			move(cub, 'x', -1);
	}
	else if (keycode == KEY_S)
	{
		if (cub->map[(int)(cub->cpos.y + 1 * cub->frameTime)][(int)cub->cpos.x] == '0')
			move(cub, 'y', 1);
	}
	else if (keycode == KEY_D)
	{
		if (cub->map[(int)(cub->cpos.y)][(int)(cub->cpos.x + 1 * cub->frameTime)] == '0')
			move(cub, 'x', 1);
	}
	else if (keycode == KEY_LEFT)
		rotate(cub, -1);
	else if (keycode == KEY_RIGHT)
		rotate(cub, 1);
	else if (keycode == KEY_ESC)
		press_esc(cub);
	return (0);
}
/*
[cos (a) -sin (a)]
[sin (a) cos (a)]
*/