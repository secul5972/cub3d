/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:32:37 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/18 18:32:37 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cub3d_init(t_cub3d_data *cub)
{
	cub->w_width = 800;
	cub->w_height = 800;
	cub->dir_img[0].img_ptr = 0;
	cub->dir_img[1].img_ptr = 0;
	cub->dir_img[2].img_ptr = 0;
	cub->dir_img[3].img_ptr = 0;
	cub->dir_img[0].data_ptr = 0;
	cub->dir_img[1].data_ptr = 0;
	cub->dir_img[2].data_ptr = 0;
	cub->dir_img[3].data_ptr = 0;
	cub->dx[0] = 1;
	cub->dx[1] = 0;
	cub->dx[2] = -1;
	cub->dx[3] = 0;
	cub->dy[0] = 0;
	cub->dy[1] = 1;
	cub->dy[2] = 0;
	cub->dy[3] = -1;
	cub->floor_color = -1;
	cub->ceiling_color = -1;
	cub->map = 0;
	cub->m_width = 0;
	cub->m_height = 0;
	cub->rotate_angle = 3;
	cub->frame_time = 0.1;
}

int	cub3d_init2(t_cub3d_data *cub, t_img *img)
{
	cub->mlx = mlx_init();
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
	int	len;

	len = ft_strlen(cub_file);
	if (!(cub_file[len - 4] == '.' && cub_file[len - 3] == 'c' \
	&& cub_file[len - 2] == 'u' && cub_file[len - 1] == 'b'))
		return (1);
	cub->fd = open(cub_file, O_RDONLY);
	if (cub->fd < 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d_data	cub;

	if (argc != 2)
		return (p_error("Arguments Error\n", 17, &cub));
	cub3d_init(&cub);
	if (cub3d_init2(&cub, &cub.img))
		return (p_error("Mlx Error\n", 11, &cub));
	if (file_open(&cub, argv[1]))
		return (p_error("File Error\n", 12, &cub));
	if (parsing(&cub))
	{
		close(cub.fd);
		return (p_error("Parsing Error\n", 15, &cub));
	}
	if (read_map(&cub))
		return (p_error("Read Map Error\n", 16, &cub));
	cub.cpos.y += 0.5;
	cub.cpos.x += 0.5;
	reset_background(&cub);
	ray_casting(&cub);
	mlx_hook(cub.win, KEYPRESS_X_EVENT, 1L << 0, &press_key, &cub);
	mlx_hook(cub.win, KEYEXIT_X_EVENT, 1L << 5, &press_x_button, &cub);
	mlx_loop(cub.mlx);
	free_all(&cub);
	return (0);
}
