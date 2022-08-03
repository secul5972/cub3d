/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:18:08 by seungcoh          #+#    #+#             */
/*   Updated: 2021/05/21 12:03:48 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;
	char	*ret;

	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (0);
	i = 0;
	j = 0;
	while (j < s1_len)
		ret[i++] = s1[j++];
	j = 0;
	while (j < s2_len)
		ret[i++] = s2[j++];
	ret[i] = 0;
	if (s1_len)
		free(s1);
	return (ret);
}

char	*ft_strdup(char *src, int offset)
{
	char	*ret;
	int		s_len;

	s_len = ft_strlen(src + offset);
	if (!(ret = (char *)malloc(sizeof(char) * (s_len + 1))))
		return (0);
	while (s_len >= 0)
	{
		ret[s_len] = (src + offset)[s_len];
		s_len--;
	}
	free(src);
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	s_len;
	size_t			i;

	if (!s)
		s_len = 0;
	else
		s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	if (s_len < len)
		len = s_len;
	if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len)
	{
		ret[i] = s[i + start];
		i++;
	}
	ret[len] = 0;
	return (ret);
}
