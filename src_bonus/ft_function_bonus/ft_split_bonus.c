/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:45:04 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/18 18:45:04 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	init_str(char **strs, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		strs[i] = 0;
		i++;
	}
}

int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i])
	{
		if (!flag && s[i] != c)
		{
			flag = 1;
			count++;
		}
		else if (flag && s[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

void	ft_findword(char const *s, char c, int *start, int *end)
{
	int	i;

	while (s[*start] == c)
		(*start)++;
	i = *start;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	*end = i;
}

void	ft_cpy(char *str, char const *s, int start, int end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		se[2];

	str = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!str)
		return (0);
	init_str(str, ft_wordcount(s, c) + 1);
	i = 0;
	se[0] = 0;
	se[1] = 0;
	while (i < ft_wordcount(s, c))
	{
		ft_findword(s, c, &se[0], &se[1]);
		str[i] = (char *)malloc(sizeof(char) * (se[1] - se[0] + 1));
		if (!str[i])
		{
			free_str(str);
			return (0);
		}
		ft_cpy(str[i++], s, se[0], se[1]);
		se[0] = se[1];
	}
	str[i] = 0;
	return (str);
}
