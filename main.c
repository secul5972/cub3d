/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:44:55 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/06 20:18:46 by secul5972        ###   ########.fr       */
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
    // cub->mlx = mlx_init();
    cub->w_width = 800;
    cub->w_height = 800;
	// cub->win = mlx_new_window(cub->mlx, cub->width, cub->length, "cub3d");
	// img->img_ptr = mlx_new_image(cub->mlx, cub->width, cub->length);
	// img->data_ptr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, \
	// &img->line_length, &img->endian);
	// if (cub->mlx == 0 || cub->win == 0 || img->img_ptr == 0 || \
	// img->data_ptr == 0)
    //     return (1);
    return (0);
}

int read_line(int fd, char **line)
{
    char buffer[100000];
    int i;
    char ch;
    i = 0;
    while (read(fd, &ch, 1) > 0)
    {
        if (ch == '\n')
            break;
        buffer[i] = ch;
        i++;
    }
    *line = (char *)malloc(sizeof(char) * i);
    ft_strcpy(*line, buffer, 0, i);
    return i;
}



int isClosed(t_cub3d_data *cub)
{
	int dx[] = {1, 0, -1, 0};
	int dy[] = {0, 1, 0, -1};

    for (int i = 0; i < cub->w_height; i++)
    {
        for (int j = 0; j < cub->w_width; j++)
        {
            if (cub->map[i][j] != ' ')
                continue;
            for (int k = 0; k < 4; k++)
            {
                int x = i + dx[k];
                int y = j + dy[k];

                if (x < 0 || x >= cub->w_height || y < 0 || y >= cub->w_width)
                    continue;
                if (cub->map[x][y] == '0')
                    return 1;
            }
        }
    }
    return 0;
}


int read_map(t_cub3d_data *cub)
{
    int len;
    int i;
    int j;
    char *line;
    t_line_lst head;
    t_line_lst *curr;
	char **map;

    len = 1;
	cub->m_width = 0;
    cub->m_height = 0;

    curr = &head;
    while (1)
    {
        len = read_line(cub->fd, &line);
        if (len <= 0)
            break;
        cub->m_width = ft_max(len, cub->m_width);
        cub->m_height++;
        curr->next = malloc(sizeof(t_line_lst));
        curr->next->next = 0;
        curr->line = line;
        curr->len = len;
        curr = curr->next;
    }
    close(cub->fd);

    map = (char **)malloc(sizeof(char*) * (cub->m_height + 2));
    i = 0;
    while (i < cub->m_height + 2)
         map[i++] = (char *)malloc(sizeof(char) * (cub->m_width + 2));

    i = 0;
    while (i < cub->m_width + 2)
    {
        map[0][i] = ' ';
        i++;
    }

    i = 1;
    curr = &head;
    while (curr)
    {
        map[i][0] = ' ';
        j = ft_strcpy(&map[i][1], curr->line, 0, curr->len) + 1;
        while (j < cub->m_width + 2)
        {
            map[i][j] = ' ';
            j++;
        }
        i++;
        curr = curr->next;
    }

    i = 0;
    while (i < cub->m_width + 2)
    {
        map[cub->m_height + 1][i] = ' ';
        i++;
    }

	cub->map = map;
    return 0;
}

int	press_esc(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int file_open(t_cub3d_data *cub)
{
	cub ->fd = open("map.cub", O_RDONLY);
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

    if (cub3d_init(&cub, &cub.img))
        return p_error("mlx error\n", 11);
	if (file_open(&cub))
		return p_error("file_error\n", 12);
	//if (!parsing(str, &dt, &cub))
	//	return p_error("Error\n", 6);
    if (read_map(&cub))
        return (1);

	for (int i = 0; i < cub.m_height + 2; i++)
    {
        for (int j = 0; j < cub.m_width + 2; j++)
        {
            write(1, &cub.map[i][j], 1);
        }
        write(1, "f\n", 2);
    }
    // mlx_put_image_to_window(cub.mlx, cub.win, cub.img.img_ptr, 0, 0);
    // mlx_key_hook(cub.win, press_esc, 0);
    // mlx_hook(cub.win, KeyExit_X_EVENT, LeaveWindowMask, &press_x_button, &cub);
    // mlx_loop(cub.mlx);
}