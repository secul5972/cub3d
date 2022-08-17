/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:44:55 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/17 13:26:11 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub3d_init(t_cub3d_data *cub, t_img *img)
{
	cub->mlx = mlx_init();
	cub->w_width = 800;
	cub->w_height = 800;
	cub->dir_img[0].img_ptr = 0;
	cub->dir_img[1].img_ptr = 0;
	cub->dir_img[2].img_ptr = 0;
	cub->dir_img[3].img_ptr = 0;
	cub->floor_color = -1;
	cub->ceiling_color = -1;
	cub->dx[0] = 1;
	cub->dx[1] = 0;
	cub->dx[2] = -1;
	cub->dx[3] = 0;
	cub->dy[0] = 0;
	cub->dy[1] = 1;
	cub->dy[2] = 0;
	cub->dy[3] = -1;
	cub->m_width = 0;
	cub->m_height = 0;
	cub->rotate_angle = 5;
	cub->frame_time = 0.1;
	cub->win = mlx_new_window(cub->mlx, cub->w_width, cub->w_height, "cub3d");
	img->img_ptr = mlx_new_image(cub->mlx, cub->w_width, cub->w_height);
	img->data_ptr = (int *)mlx_get_data_addr(img->img_ptr, \
	&img->bits_per_pixel, &img->line_length, &img->endian);
	if (cub->mlx == 0 || cub->win == 0 || img->img_ptr == 0 || \
	img->data_ptr == 0)
		return (1);
	return (0);
}

int	file_open(t_cub3d_data *cub, char *cub_file)
{
	cub->fd = open(cub_file, O_RDONLY);
	if (cub->fd < 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d_data	cub;

	if (argc != 2)
		return (p_error("Arguments Error\n", 17));
	if (cub3d_init(&cub, &cub.img))
		return (p_error("Mlx Error\n", 11));
	if (file_open(&cub, argv[1]))
		return (p_error("File Error\n", 12));
	if (parsing(&cub))
		return (p_error("Parsing Error\n", 15));
	if (read_map(&cub))
		return (p_error("Read Map Error\n", 16));
	cub.cpos.y += 0.5;
	cub.cpos.x += 0.5;
	reset_background(&cub);
	ray_casting(&cub);
	mlx_hook(cub.win, KEYPRESS_X_EVENT, 1L << 0, &press_key, &cub);
	mlx_hook(cub.win, KEYEXIT_X_EVENT, 1L << 5, &press_x_button, &cub);
	mlx_loop(cub.mlx);
	free_map(cub.map, cub.m_height);
	free_all(&cub);
	return (0);
}
