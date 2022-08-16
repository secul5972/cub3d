/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:22:00 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/16 11:58:56 by secul5972        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_vec_data(t_cub3d_data *cub, t_veci idx)
{
	cub->map[idx.x][idx.y] = '0';
	make_vec(&cub->cpos, idx.y, idx.x);
	make_vec(&cub->plane, cub->cdir.y, -cub->cdir.x);
}

void	fix_map_find_pos(t_cub3d_data *cub)
{
	t_veci	idx;

	idx.x = -1;
	while (idx.x++ < cub->m_height)
	{
		idx.y = -1;
		while (idx.y++ < cub->m_width)
		{
			if (cub->map[idx.x][idx.y] == 'N')
				make_vec(&cub->cdir, 0, -1);
			if (cub->map[idx.x][idx.y] == 'S')
				make_vec(&cub->cdir, 0, 1);
			if (cub->map[idx.x][idx.y] == 'W')
				make_vec(&cub->cdir, -1, 0);
			if (cub->map[idx.x][idx.y] == 'E')
				make_vec(&cub->cdir, 1, 0);
			if (cub->map[idx.x][idx.y] == 'N' || cub->map[idx.x][idx.y] == 'S' \
			|| cub->map[idx.x][idx.y] == 'W' || cub->map[idx.x][idx.y] == 'E')
			{
				make_vec_data(cub, idx);
				return ;
			}
		}
	}
}
