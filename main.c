/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:44:55 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/07 16:39:38 by secul5972        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int p_error(char *str, int len)
{
    write(2, str, len);
    return (1);
}

int cub3d_init(t_cub3d_data *cub, t_img *img)
{
    //cub->mlx = mlx_init();
    cub->w_width = 800;
    cub->w_height = 800;
	//init elements
	cub->n_texture = 0;
	cub->s_texture = 0;
	cub->w_texture = 0;
	cub->e_texture = 0;
	cub->f_rgb[0] = -1;
	cub->f_rgb[1] = -1;
	cub->f_rgb[2] = -1;
	cub->c_rgb[0] = -1;
	cub->c_rgb[1] = -1;
	cub->c_rgb[2] = -1;
	//cub->win = mlx_new_window(cub->mlx, cub->w_width, cub->w_height, "cub3d");
	// img->img_ptr = mlx_new_image(cub->mlx, cub->width, cub->length);
	// img->data_ptr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, \
	// &img->line_length, &img->endian);
	// if (cub->mlx == 0 || cub->win == 0 || img->img_ptr == 0 || \
	// img->data_ptr == 0)
    //     return (1);
    return (0);
}

int	press_esc(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int file_open(t_cub3d_data *cub, char *cub_file)
{
	cub ->fd = open(cub_file, O_RDONLY);
	if (cub->fd < 0)
        return (1);
	return (0);
}

int	press_x_button(t_cub3d_data *cub)
{
	//mlx_destroy_window(cub->mlx, cub->win);
	exit(0);
	return (0);
}

int main(int argc, char **argv)
{
    t_cub3d_data cub;

	if (argc != 2)
		return p_error("Arguments Error\n", 17);
    if (cub3d_init(&cub, &cub.img))
        return p_error("Mlx Error\n", 11);
	if (file_open(&cub, argv[1]))
		return p_error("File Error\n", 12);
	if (parsing(&cub))
		return p_error("Parsing Error\n", 15);
	if (read_map(&cub))
	 	return p_error("Read Map Error\n", 16);

	// for (int i = 0; i < cub.m_height + 2; i++)
	// {
	// 	for (int j = 0; j < cub.m_width + 2; j++)
	// 	{
	// 		write(1, &cub.map[i][j], 1);
	// 	}
	// 	write(1, "f\n", 2);
	// }
	 /*mlx_put_image_to_window(cub.mlx, cub.win, cub.w_texture, 0, 0);
     mlx_key_hook(cub.win, press_esc, 0);
     mlx_hook(cub.win, KeyExit_X_EVENT, LeaveWindowMask, &press_x_button, &cub);
     mlx_loop(cub.mlx);*/
	//terminate
	free_map(cub.map, cub.m_height + 2);
	return (0);
}