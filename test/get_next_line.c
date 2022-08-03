/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:52:36 by seungcoh          #+#    #+#             */
/*   Updated: 2021/06/24 14:10:08 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		new_line_idx(char *str, int *ret, int flag)
{
	int i;

	i = 0;
	if (!str)
	{
		*ret = 0;
		return (0);
	}
	while (str[i] != '\n')
	{
		if (!str[i])
		{
			if (flag)
				break ;
			else
				return (-1);
		}
		i++;
	}
	if (!str[i])
		*ret = 0;
	return (i);
}

int		sep_buf(char **t_line, int ret, int idx)
{
	if (ret && (ft_strlen(*t_line) == idx + 1))
	{
		free(*t_line);
		*t_line = 0;
		return (ret);
	}
	if (ret && !(*t_line = ft_strdup(*t_line, idx + 1)))
		return (-1);
	if (!ret && *t_line)
	{
		free(*t_line);
		*t_line = 0;
	}
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char		*t_line[FD_SIZE];
	char			buf[BUFFER_SIZE + 1];
	int				len;
	int				ret;

	ret = 1;
	if ((fd < 0) || (fd >= FD_SIZE) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((len = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[len] = 0;
		if (!(t_line[fd] = ft_strjoin(t_line[fd], buf)))
			return (-1);
		if (new_line_idx(t_line[fd], &ret, 0) != -1)
			break ;
	}
	if (len == -1)
		return (-1);
	len = new_line_idx(t_line[fd], &ret, 1);
	if (!(*line = ft_substr(t_line[fd], 0, len)))
		return (-1);
	return (sep_buf(&t_line[fd], ret, len));
}
