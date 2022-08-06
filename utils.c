/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:33:21 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/06 21:09:03 by secul5972        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_str(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
}

int read_line(int fd, char **line)
{
    char buffer[100000];
    int i;
    char ch;
    i = 0;
    while (read(fd, &ch, 1) > 0)
    {
        if (ch == '\n')
            break;
        buffer[i] = ch;
        i++;
    }
    *line = (char *)malloc(sizeof(char) * i);
    ft_strcpy(*line, buffer, 0, i);
    return i;
}
