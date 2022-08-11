/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:32:35 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/11 16:56:53 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_and_return(char **strs, int ret)
{
	free_str(strs);
	return (ret);
}

double vec_scale(t_vec v)
{
    return sqrt(v.x*v.x+v.y*v.y);
}