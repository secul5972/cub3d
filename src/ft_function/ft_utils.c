/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:31:55 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/17 18:46:29 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strcpy(char *s1, char *s2, int start, int end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		s1[i] = s2[start];
		i++;
		start++;
	}
	s1[i] = '\0';
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		else if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

size_t	ft_strlen(char *s1)
{
	size_t	len;

	if (!s1)
		return (0);
	len = 0;
	while (s1[len])
		len++;
	return (len);
}
