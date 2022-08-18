/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:33:00 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/18 18:33:01 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	free_and_return(t_cub3d_data *cub, char **strs, int ret)
{
	if (ret == 1)
		close(cub->fd);
	free_str(strs);
	return (ret);
}

int	error_return(char *str, int ret)
{
	free(str);
	return (ret);
}

int	is_num_ch(char c)
{
	return ('0' <= c && c <= '9');
}
