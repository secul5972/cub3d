/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:32:35 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/17 13:31:40 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_and_return(char **strs, int ret)
{
	free_str(strs);
	return (ret);
}

double	vec_scale(t_vecd v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

void	free_all(t_cub3d_data *cub)
{
	mlx_destroy_image(cub->mlx, cub->dir_img[0].img_ptr);
	mlx_destroy_image(cub->mlx, cub->dir_img[1].img_ptr);
	mlx_destroy_image(cub->mlx, cub->dir_img[2].img_ptr);
	mlx_destroy_image(cub->mlx, cub->dir_img[3].img_ptr);
	mlx_destroy_window(cub->mlx, cub->win);
	free(cub->mlx);
}

int	p_error(char *str, int len)
{
	write(2, str, len);
	return (1);
}
