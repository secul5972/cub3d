/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pos_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:32:09 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/18 18:32:09 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
