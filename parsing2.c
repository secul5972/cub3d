/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:58:46 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/17 18:57:26 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_color(int *colors, char **elem, t_cub3d_data *cub)
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
	if (ft_strcmp(elem[0], "F") == 0)
		cub->floor_color = res;
	else
		cub->ceiling_color = res;
}

int	change_to_space(char **elem)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	cnt = 0;
	while (elem[++i])
	{
		j = -1;
		while (elem[i][++j])
		{
			if (elem[i][j] == ',')
			{
				cnt++;
				elem[i][j] = ' ';
			}
			else if (!(('0' <= elem[i][j] \
			&& elem[i][j] <= '9') || elem[i][j] == ' '))
				return (1);
		}
	}
	if (cnt != 2)
		return (1);
	return (0);
}

int	check_number(int *cnt, int *colors, char *rgb)
{
	(*cnt)++;
	if (*cnt == 3)
		return (1);
	colors[*cnt] = ft_atoi(rgb);
	if (colors[*cnt] == -1 || !(0 <= colors[*cnt] && colors[*cnt] <= 255))
		return (1);
	return (0);
}

// 수정(119, ,136 153)
int	get_rgb(char **elem, t_cub3d_data *cub)
{
	char	**rgb;
	int		colors[3];
	int		i;
	int		j;
	int		cnt;

	if (change_to_space(elem))
		return (1);
	i = 0;
	cnt = -1;
	while (elem[++i])
	{
		rgb = ft_split(elem[i], ' ');
		j = -1;
		while (rgb[++j])
		{
			if (check_number(&cnt, colors, rgb[j]))
				return (free_and_return(rgb, 1));
		}
		free_str(rgb);
	}
	if (cnt != 2)
		return (1);
	get_color(colors, elem, cub);
	return (0);
}
