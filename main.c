/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:44:55 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/03 14:02:04 by seungcoh         ###   ########.fr       */
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
    cub->mlx = mlx_init();
    cub->width = 800;
    cub->length = 800;
	cub->win = mlx_new_window(cub->mlx, cub->width, cub->length, "cub3d");
	img->img_ptr = mlx_new_image(cub->mlx, cub->width, cub->length);
	img->data_ptr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	if (cub->mlx == 0 || cub->win == 0 || img->img_ptr == 0 || \
	img->data_ptr == 0)
        return p_error("mlx error\n", 11);
        
    return (0);
}

int read_map()
{
    
}

int	press_esc(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int	press_x_button(t_cub3d_data *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	exit(0);
	return (0);
}

int main(int argc, char **argv)
{
    t_cub3d_data cub;

    if (cub3d_init(&cub, &cub.img))
        return (1);
    if (read_map())
        return (1);
    mlx_put_image_to_window(cub.mlx, cub.win, cub.img.img_ptr, 0, 0);
    mlx_key_hook(cub.win, press_esc, 0);
    mlx_hook(cub.win, KeyExit_X_EVENT, LeaveWindowMask, &press_x_button, &cub);
    mlx_loop(cub.mlx);
}