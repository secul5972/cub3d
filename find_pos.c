/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:22:00 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/11 15:07:02 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fix_map_find_pos(t_cub3d_data *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->m_height)
	{
		j = 0;
		while (j < cub->m_width)
		{
			if (cub->map[i][j] != '1' && cub->map[i][j] != '0'\
			&& cub->map[i][j] != ' ')
				make_vec(&cub->cpos, j, i);
			if (cub->map[i][j] == 'N')
				make_vec(&cub->cdir, 0, -1);
			if (cub->map[i][j] == 'S')
				make_vec(&cub->cdir, 0, 1);
			if (cub->map[i][j] == 'W')
				make_vec(&cub->cdir, -1, 0);
			if (cub->map[i][j] == 'E')
				make_vec(&cub->cdir, 1, 0);
			j++;
		}
		i++;
	}
}
