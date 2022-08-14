/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:58:46 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/14 17:59:22 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(int *colors)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (++i < 3)
	{
		res *= 16;
		res += (colors[i] / 16);
		res *= 16;
		res += (colors[i] % 16);
	}
	return (res);
}

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
	if (ft_strcmp(elem[0], "F") == 0)
		cub->floor_color = get_color(colors);
	else
		cub->ceiling_color = get_color(colors);
	return (free_and_return(rgb, 0));
}
