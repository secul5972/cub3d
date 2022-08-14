/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:44:55 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/12 14:25:20 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	p_error(char *str, int len)
{
	write(2, str, len);
	return (1);
}

int	cub3d_init(t_cub3d_data *cub, t_img *img)
{
	cub->mlx = mlx_init();
	cub->w_width = 800;
	cub->w_height = 800;
	cub->n_texture = 0;
	cub->s_texture = 0;
	cub->w_texture = 0;
	cub->e_texture = 0;
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
	cub->frameTime = 0.1;
	cub->win = mlx_new_window(cub->mlx, cub->w_width, cub->w_height, "cub3d");
	img->img_ptr = mlx_new_image(cub->mlx, cub->w_width, cub->w_height);
	img->data_ptr = (int *)mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	if (cub->mlx == 0 || cub->win == 0 || img->img_ptr == 0 || \
	img->data_ptr == 0)
		return (1);
	return (0);
}

void free_all(t_cub3d_data *cub)
{
	mlx_destroy_image(cub->mlx, cub->n_texture);
	mlx_destroy_image(cub->mlx, cub->s_texture);
	mlx_destroy_image(cub->mlx, cub->w_texture);
	mlx_destroy_image(cub->mlx, cub->e_texture);
	mlx_destroy_window(cub->mlx, cub->win);
	free(cub->mlx);
}

int	file_open(t_cub3d_data *cub, char *cub_file)
{
	cub->fd = open(cub_file, O_RDONLY);
	if (cub->fd < 0)
		return (1);
	return (0);
}

int press_x_button(t_cub3d_data *cub)
{
	free_all(cub);
	exit(0);
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
    // for (int i = 0; i < cub.m_height; i++)
    // {
    //     for (int j = 0; j < cub.m_width; j++)
    //     {
    //         write(1, &cub.map[i][j], 1);
    //     }
    //     write(1, "f\n", 2);
    // }

	reset_background(&cub);

	// plane
	make_vec(&cub.plane, cub.cdir.y, -cub.cdir.x);

	// ray
	ray_casting(&cub);

	mlx_hook(cub.win, KEYPRESS_X_EVENT, 1L<<0, &press_key, &cub);
	mlx_hook(cub.win, KEYEXIT_X_EVENT, 1L<<5, &press_x_button, &cub);
	mlx_loop(cub.mlx);
	//terminate
	free_map(cub.map, cub.m_height);
	free_all(&cub);
	return (0);
}
