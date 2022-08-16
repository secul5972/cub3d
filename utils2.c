/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:32:35 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/16 11:53:51 by secul5972        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_and_return(char **strs, int ret)
{
	free_str(strs);
	return (ret);
}

double	vec_scale(t_vecd v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}
