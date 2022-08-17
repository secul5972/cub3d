/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 21:07:23 by secul5972         #+#    #+#             */
/*   Updated: 2022/08/17 15:59:51 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	chk_cell(int i, int j, t_cub3d_data *cub)
{
	int	x;
	int	y;
	int	k;

	k = 0;
	while (k < 4)
	{
		x = i + cub->dx[k];
		y = j + cub->dy[k];
		if (x < 0 || x >= cub->m_height || y < 0 || y >= cub->m_width)
			return (1);
		if (cub->map[x][y] == ' ')
			return (1);
		k++;
	}
	return (0);
}

int	isclosed(t_cub3d_data *cub)
{
	int	i;
	int	j;

	cub->dx[0] = 1;
	cub->dx[1] = 0;
	cub->dx[2] = -1;
	cub->dx[3] = 0;
	cub->dy[0] = 0;
	cub->dy[1] = 1;
	cub->dy[2] = 0;
	cub->dy[3] = -1;
	i = 0;
	while (i < cub->m_height)
	{
		j = 0;
		while (j < cub->m_width)
		{
			if (cub->map[i][j] == '0' && chk_cell(i, j, cub))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	read_map(t_cub3d_data *cub)
{
	t_line_lst	head;
	t_line_lst	*curr;
	char		**map;

	head.next = 0;
	if (get_lst(cub, &head, &head))
		return (1);
	if (lst_to_map(cub, &head, head.next))
		return (1);
	free_list(&head);
	if (isclosed(cub))
	{
		free_map(cub->map, cub->m_height);
		return (1);
	}
	fix_map_find_pos(cub);
	return (0);
}
