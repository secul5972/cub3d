/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 21:07:23 by secul5972         #+#    #+#             */
/*   Updated: 2022/08/11 13:56:51 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int isClosed(t_cub3d_data *cub)
{
	int dx[] = {1, 0, -1, 0};
	int dy[] = {0, 1, 0, -1};
	int x;
	int y;
    for (int i = 0; i < cub->m_height; i++)
    {
        for (int j = 0; j < cub->m_width; j++)
        {
            if (cub->map[i][j] != ' ')
                continue;
            for (int k = 0; k < 4; k++)
            {
                int x = i + dx[k];
                int y = j + dy[k];
                if (x < 0 || x >= cub->m_height || y < 0 || y >= cub->m_width)
                    continue;
                if (cub->map[x][y] == '0')
                    return 1;
            }
        }
    }
    return 0;
}

int	chk_char(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}


int read_map(t_cub3d_data *cub)
{
    int len;
    int i;
    int j;
    char *line;
    t_line_lst head;
    t_line_lst *curr;
	char **map;

    len = 1;
	cub->m_width = 0;
    cub->m_height = 0;

	head.line = 0;
	head.next = 0;
    curr = &head;

    while (1)
    {
        len = read_line(cub->fd, &line);
        if (len < 0)
            break;
		else if (len == 0)
			continue;
		if (chk_char(line))
			return free_list(&head);
        cub->m_width = ft_max(len, cub->m_width);
        cub->m_height++;
        curr->next = malloc(sizeof(t_line_lst));
		if (curr->next == 0)
			return free_list(&head);
        curr->next->next = 0;
		curr->next->line = line;
        curr->next->len = len;
        curr = curr->next;
    }
    close(cub->fd);

    map = (char **)malloc(sizeof(char*) * (cub->m_height + 2));
	if (map == 0)
		free_list(&head);
    i = 0;
    while (i < cub->m_height + 2)
	{
        map[i] = (char *)malloc(sizeof(char) * (cub->m_width + 2));
		if (map[i] == 0)
		{
			free_list(&head);
			free_map(map, i);
			return (1);
		}
		i++;
	}

    i = 0;
    while (i < cub->m_width + 2)
    {
        map[0][i] = ' ';
        i++;
    }

    i = 1;
    curr = &head;
    while (curr->next)
    {
        map[i][0] = ' ';
        j = ft_strcpy(&map[i][1], curr->line, 0, curr->len) + 1;
        while (j < cub->m_width + 2)
        {
            map[i][j] = ' ';
            j++;
        }
        i++;
        curr = curr->next;
    }
	free_list(&head);

    i = 0;
    while (i < cub->m_width + 2)
    {
        map[cub->m_height + 1][i] = ' ';
        i++;
    }
	cub->map = map;

	if (isClosed(cub))
	{
		free_map(cub->map, cub->m_height + 2);
		return (1);
	}

    // 플레이어 위치, 방향 맵에서 읽기 
    fix_map_find_pos(cub);
    return 0;
}