/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:58:38 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/17 17:48:11 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	chk_char(char *line, int *cnt)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && \
		line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && \
		line[i] != ' ')
		{
			free(line);
			return (1);
		}
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || \
		line[i] == 'W')
			*cnt = *cnt + 1;
		if (*cnt > 1)
		{
			free(line);
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_lst(t_cub3d_data *cub, t_line_lst *head, t_line_lst *curr, int *cnt)
{
	int		len;
	char	*line;

	*cnt = 0;
	while (1)
	{
		len = read_line(cub->fd, &line);
		if (len < 0)
			break ;
		else if (len == 0)
			continue ;
		if (chk_char(line, cnt))
			return (free_list(head));
		cub->m_width = ft_max(len, cub->m_width);
		cub->m_height++;
		curr->next = malloc(sizeof(t_line_lst));
		if (curr->next == 0)
			return (free_list(head));
		curr->next->next = 0;
		curr->next->line = line;
		curr->next->len = len;
		curr = curr->next;
	}
	close(cub->fd);
	return (0);
}

int	lst_to_map(t_cub3d_data *cub, t_line_lst *head, t_line_lst *curr)
{
	int	i;
	int	j;

	cub->map = (char **)malloc(sizeof(char *) * (cub->m_height));
	if (cub->map == 0)
		free_list(head);
	i = 0;
	while (i < cub->m_height)
	{
		cub->map[i] = (char *)malloc(sizeof(char) * (cub->m_width));
		if (cub->map[i] == 0)
		{
			free_list(head);
			return (1);
		}
		j = ft_strcpy(&(cub->map[i][0]), curr->line, 0, curr->len);
		while (j < cub->m_width)
		{
			cub->map[i][j] = ' ';
			j++;
		}
		i++;
		curr = curr->next;
	}
	return (0);
}
