/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:33:21 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/08 10:24:39 by secul5972        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void free_str(char **strs)
{
	int i;

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
	char	buffer[100000];
	int		i;
	char	ch;
	
	i = 0;
	ch = 0;
	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\n')
			break;
		buffer[i] = ch;
		i++;
	}
	if (ch == '\n' && i == 0)
		return (0);
	else if (i == 0)
		return (-1);
	*line = (char *)malloc(sizeof(char) * (i + 1));
	ft_strcpy(*line, buffer, 0, i);
	return i;
}

void free_list(t_line_lst *head)
{
	t_line_lst *curr;
	t_line_lst *next;

	if (head->line)
		free(head->line);
	if (head->next == 0)
		return;
	curr = head->next;
	next = 0;
	while (curr)
	{
		if (curr->line)
			free(curr->line);
		next = curr->next;
		free(curr);
		curr = next;
	}
	curr = head;
}

void free_map(char **map, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}