/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:32:33 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/03 14:32:38 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	long	minus;
	long	res;

	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	minus = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			minus *= -1;
	res = 0;
	while (nptr[i] && ('0' <= nptr[i] && nptr[i] <= '9'))
	{
		res *= 10;
		res += (nptr[i] - '0');
		if (res > 2147483647 && minus == 1)
			return (-1);
		if (res > 2147483648 && minus == -1)
			return (0);
		i++;
	}
	return (res * minus);
}
