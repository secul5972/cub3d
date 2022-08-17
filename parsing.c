/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:32:09 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/17 14:18:27 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_invalid_elements(char **elems)
{
	int	i;

	i = 0;
	while (elems[i])
		i++;
	if (i != 2)
		return (1);
	if (!(ft_strcmp(elems[0], "NO") == 0 || ft_strcmp(elems[0], "SO") == 0 \
	|| ft_strcmp(elems[0], "WE") == 0 || ft_strcmp(elems[0], "EA") == 0 \
	|| ft_strcmp(elems[0], "F") == 0 || ft_strcmp(elems[0], "C") == 0))
		return (1);
	return (0);
}

void	get_img_data(t_cub3d_data *cub, int dir, char *file)
{
	int	img_width;
	int	img_height;

	cub->dir_img[dir].img_ptr = mlx_xpm_file_to_image(cub->mlx, file, \
		&cub->dir_img[dir].t_width, &cub->dir_img[dir].t_height);
	cub->dir_img[dir].data_ptr = \
	(int *)mlx_get_data_addr(cub->dir_img[dir].img_ptr, \
	&cub->dir_img[dir].bits_per_pixel, &cub->dir_img[dir].line_length, \
	&cub->dir_img[dir].endian);
}

int	get_elements(char *line, t_cub3d_data *cub)
{
	char	**elem;

	elem = ft_split(line, ' ');
	if (!elem[0])
		return (free_and_return(elem, 0));
	if (is_invalid_elements(elem))
		return (free_and_return(elem, 1));
	if (ft_strcmp(elem[0], "NO") == 0)
		get_img_data(cub, 0, elem[1]);
	else if (ft_strcmp(elem[0], "SO") == 0)
		get_img_data(cub, 1, elem[1]);
	else if (ft_strcmp(elem[0], "WE") == 0)
		get_img_data(cub, 2, elem[1]);
	else if (ft_strcmp(elem[0], "EA") == 0)
		get_img_data(cub, 3, elem[1]);
	else if (ft_strcmp(elem[0], "F") == 0 || ft_strcmp(elem[0], "C") == 0)
	{
		if (get_rgb(elem, cub))
			return (free_and_return(elem, 1));
	}
	return (free_and_return(elem, 0));
}

int	parsing(t_cub3d_data *cub)
{
	char	*line;
	int		len;
	int		res;

	while (1)
	{
		len = read_line(cub->fd, &line);
		if (len < 0)
			return (1);
		else if (len == 0)
			continue ;
		res = get_elements(line, cub);
		free(line);
		if (res)
			return (1);
		if (cub->dir_img[0].img_ptr && cub->dir_img[1].img_ptr \
		&& cub->dir_img[2].img_ptr && cub->dir_img[3].img_ptr \
		&& cub->dir_img[0].data_ptr && cub->dir_img[1].data_ptr \
		&& cub->dir_img[2].data_ptr && cub->dir_img[3].data_ptr \
		&& cub->floor_color > -1 && cub->ceiling_color > -1)
			return (0);
	}
	return (1);
}
