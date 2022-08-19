/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:32:35 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/19 13:32:03 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	vec_scale(t_vecd v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

void	free_all(t_cub3d_data *cub)
{
	if (cub->dir_img[0].img_ptr)
		mlx_destroy_image(cub->mlx, cub->dir_img[0].img_ptr);
	if (cub->dir_img[1].img_ptr)
		mlx_destroy_image(cub->mlx, cub->dir_img[1].img_ptr);
	if (cub->dir_img[2].img_ptr)
		mlx_destroy_image(cub->mlx, cub->dir_img[2].img_ptr);
	if (cub->dir_img[3].img_ptr)
		mlx_destroy_image(cub->mlx, cub->dir_img[3].img_ptr);
	if (cub->img.img_ptr)
		mlx_destroy_image(cub->mlx, cub->img.img_ptr);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->map)
		free_map(cub->map, cub->m_height);
}

int	p_error(char *str, int len, t_cub3d_data *cub)
{
	write(2, str, len);
	free_all(cub);
	return (1);
}
