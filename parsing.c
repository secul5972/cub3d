/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:32:09 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/11 14:39:50 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(char **elem, t_cub3d_data *cub)
{
	char	**rgb;
	int		colors[3];
	int		i;

	rgb = ft_split(elem[1], ',');
	if (rgb[3] != 0)
		return (free_and_return(rgb, 1));
	i = -1;
	while (++i < 3)
	{
		colors[i] = ft_atoi(rgb[i]);
		if (!(0 <= colors[i] && colors[i] <= 255))
			break ;
	}
	if (i != 3)
		return (free_and_return(rgb, 1));
	while (--i >= 0)
	{
		if (ft_strcmp(elem[0], "F") == 0)
			cub->f_rgb[i] = colors[i];
		else
			cub->c_rgb[i] = colors[i];
	}
	return (free_and_return(rgb, 0));
}

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

void	change_xpm_file_to_image(char **elem, t_cub3d_data *cub)
{
	int	img_width;
	int	img_height;

	if (ft_strcmp(elem[0], "NO") == 0)
		cub->n_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], \
		&img_width, &img_height);
	else if (ft_strcmp(elem[0], "SO") == 0)
		cub->s_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], \
		&img_width, &img_height);
	else if (ft_strcmp(elem[0], "WE") == 0)
		cub->w_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], \
		&img_width, &img_height);
	else if (ft_strcmp(elem[0], "EA") == 0)
		cub->e_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], \
		&img_width, &img_height);
}

int	get_elements(char *line, t_cub3d_data *cub)
{
	char	**elem;

	elem = ft_split(line, ' ');
	if (!elem[0])
		return (free_and_return(elem, 0));
	if (is_invalid_elements(elem))
		return (free_and_return(elem, 1));
	if (ft_strcmp(elem[0], "NO") == 0 || ft_strcmp(elem[0], "SO") == 0 \
	|| ft_strcmp(elem[0], "WE") == 0 || ft_strcmp(elem[0], "EA") == 0)
		change_xpm_file_to_image(elem, cub);
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
		if (cub->n_texture && cub->s_texture \
		&& cub->w_texture && cub->e_texture \
		&& cub->f_rgb[0] > -1 && cub->f_rgb[1] > -1 && cub->f_rgb[2] > -1 \
		&& cub->c_rgb[0] > -1 && cub->c_rgb[1] > -1 && cub->c_rgb[2] > -1)
			return (0);
	}
	return (1);
}
