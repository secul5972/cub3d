/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:33:21 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/17 17:46:17 by seungcoh         ###   ########.fr       */
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

int	read_line(int fd, char **line)
{
	char	buffer[100000];
	int		i;
	char	ch;

	i = 0;
	ch = 0;
	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\n')
			break ;
		buffer[i] = ch;
		i++;
	}
	if (ch == '\n' && i == 0)
		return (0);
	else if (i == 0)
		return (-1);
	*line = (char *)malloc(sizeof(char) * (i + 1));
	ft_strcpy(*line, buffer, 0, i);
	return (i);
}

int	free_list(t_line_lst *head)
{
	t_line_lst	*curr;
	t_line_lst	*next;

	curr = head->next;
	while (curr)
	{
		free(curr->line);
		next = curr->next;
		free(curr);
		curr = next;
	}
	return (1);
}

int	free_map(char **map, int height)
{
	int	i;

	i = 0;
	if (map)
	{
		while (i < height)
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
	return (1);
}

void	make_vec(t_vecd *v, double x, double y)
{
	v->x = x;
	v->y = y;
}
