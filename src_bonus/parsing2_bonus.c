/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:32:53 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/19 12:58:53 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

int	make_color_str(char **rgb, char **elem)
{
	int	size;
	int	i;
	int	j;
	int	k;
	int	cnt;

	size = 0;
	cnt = 0;
	while (elem[++cnt])
		size += ft_strlen(elem[cnt]);
	*rgb = (char *)malloc(sizeof(char) * (size + cnt - 2 + 1));
	if (!(*rgb))
		return (1);
	i = 0;
	k = 0;
	while (elem[++i])
	{
		j = -1;
		while (elem[i][++j])
			(*rgb)[k++] = elem[i][j];
		if (i < cnt - 1)
			(*rgb)[k++] = ' ';
	}
	(*rgb)[k] = 0;
	return (0);
}

int	have_color(char *rgb, int i, int res)
{
	if (i == 0 || rgb[i - 1] == ',' || (rgb[i - 1] == ' ' && rgb[i - 2] == ','))
		return (1);
	if (!(0 <= res && res <= 255))
		return (1);
	return (0);
}

int	func(char *rgb, int *colors, int *i, int *k)
{
	int	res;

	res = 0;
	while (rgb[++(*i)])
	{
		if (*k == 3 || !(rgb[*i] == ',' || \
		is_num_ch(rgb[*i]) || rgb[*i] == ' '))
			return (-1);
		else if (rgb[*i] == ' ' \
		&& is_num_ch(rgb[(*i) - 1]) && is_num_ch(rgb[(*i) + 1]))
			return (-1);
		else if (rgb[*i] == ',')
		{
			if (have_color(rgb, *i, res))
				return (-1);
			colors[(*k)++] = res;
			res = 0;
		}
		else if (is_num_ch(rgb[*i]))
		{
			res *= 10;
			res += (rgb[*i] - '0');
		}
	}
	return (res);
}

int	get_rgb(char **elem, t_cub3d_data *cub)
{
	char	*rgb;
	int		colors[3];
	int		i;
	int		k;
	int		res;

	i = 0;
	if (make_color_str(&rgb, elem))
		return (1);
	i = -1;
	k = 0;
	res = func(rgb, colors, &i, &k);
	if (res == -1 || have_color(rgb, i, res) || k != 2)
		return (error_return(rgb, 1));
	colors[k] = res;
	get_color(colors, elem, cub);
	return (error_return(rgb, 0));
}
