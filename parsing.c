/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:32:09 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/07 16:40:11 by secul5972        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// rgb 색상 숫자로 저장 (색상 문자열에서 공백일 포함될 떄의 경우 처리 필요?)
int	get_rgb(char **elem, t_cub3d_data *cub) // return 0 - success, 1 - fail
{
	char	**rgb;
	int		colors[3];
	int		i;

	rgb = ft_split(elem[1], ',');
	if (rgb[3] != 0)
		return (1);
	i = -1;
	while (++i < 3)
	{
		colors[i] = ft_atoi(rgb[i]);
		if (!(0 <= colors[i] && colors[i] <= 255))
			break ;
	}
	if (i != 3)
		return (1);
	if (ft_strcmp(elem[0], "F") == 0)
	{
		while (--i >= 0)
			cub->f_rgb[i] = colors[i];
	}
	else
	{
		while (--i >= 0)
			cub->c_rgb[i] = colors[i];
	}
	return (0);
}

int is_invalid_elements(char **elems) // return 0 - success, 1 - fail
{
	int	i;

	i = 0;
	while (elems[i])
		i++;
	if (i != 2)
		return (1);
	if (!(ft_strcmp(elems[0], "NO") == 0 || ft_strcmp(elems[0], "SO") == 0\
		|| ft_strcmp(elems[0], "WE") == 0 || ft_strcmp(elems[0], "EA") == 0\
		|| ft_strcmp(elems[0], "F") == 0 || ft_strcmp(elems[0], "C") == 0))
		return (1);
	return (0);
}

// 각 식별자를 기준으로 필요한 정보 저장
int	get_elements(char *line, t_cub3d_data *cub) // return 0 - success, 1 - fail, -1 - empty line
{
	char	**elem;
	int		img_width;
	int		img_height;

	elem = ft_split(line, ' ');
	if (!elem[0])
		return (0);
	if (is_invalid_elements(elem))
		return (1);
	printf("%s: %s\n", elem[0], elem[1]);
	// mlx_xpm_file_to_image: 존재하지 않는 파일이면 null 반환
	if (ft_strcmp(elem[0], "NO") == 0)
		cub->n_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], &img_width, &img_height);
	else if (ft_strcmp(elem[0], "SO") == 0)
		cub->s_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], &img_width, &img_height);
	else if (ft_strcmp(elem[0], "WE") == 0)
		cub->w_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], &img_width, &img_height);
	else if (ft_strcmp(elem[0], "EA") == 0)
		cub->e_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], &img_width, &img_height);
	else if (ft_strcmp(elem[0], "F") == 0 || ft_strcmp(elem[0], "C") == 0)
	{
		if (get_rgb(elem, cub))
			return (1);
	}
	return (0);
}

// 필요한 정보들이 다 저장되었는지
int	is_all_stored(t_cub3d_data *cub) // return 0 - fail, 1 - success
{
	if (!cub->n_texture || !cub->s_texture || !cub->w_texture || !cub->e_texture)
		return (0);
	if (cub->f_rgb[0] == -1 || cub->f_rgb[1] == -1 || cub->f_rgb[2] == -1)
		return (0);
	if (cub->c_rgb[0] == -1 || cub->c_rgb[1] == -1 || cub->c_rgb[2] == -1)
		return (0);
	return (1);
}

//.cub 파일 데이터 파싱 (맵 전까지)
int	parsing(t_cub3d_data *cub) // return 0 - success, 1 - fail
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
			continue;
		res = get_elements(line, cub);
		free(line);
		if (res)
			return (1);
		if (is_all_stored(cub))
			return (0);
	}
	return (1);
}
