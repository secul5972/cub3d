/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isClosed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:44:57 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/03 14:34:37 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int width = 12;
int height = 12;

int isClosed(char map[][12])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] != ' ')
                continue;
            for (int k = 0; k < 4; k++)
               {
                int x = i + dx[k];
                int y = j + dy[k];

                if (x < 0 || x >= height || y < 0 || y >= width)
                    continue;
                if (map[x][y] == '0')
                    return 1;
            }
        }
    }
    return 0;
}

int ft_max(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

int	ft_strcpy(char *dest, const char *src, int size)
{
	int i;
	int len;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	return (len);
}

int read_map(char **map)
{
    int fd;
    int len;
    int width;
    int height;
    int i;
    int j;
    char *line;

    fd = open("map.cub",O_RDONLY);
    if (fd < 0)
        return 1;

    len = 1;
    while (len < 0)
    {
        len = get_next_line(fd, &line);
        printf("%s\n", line);
        width = ft_max(len, width);
        height++;
    }
    close(fd);

    fd = open("map.cub",O_RDONLY);
    map = malloc(sizeof(char) * (width + 2) * (height + 2));

    i = 0;
    while (i < width + 2)
    {
        map[0][i] = ' ';
        i++;
    }

    i = 1;
    while (1)
    {
        len = get_next_line(fd, &line);
        map[i][0] = ' ';
        ft_strcpy(&map[i][1], line, len);
        j = len;
        while (j < width + 2)
        {
            map[i][j] = ' ';
        }
        i++;
    }

    i = 0;
    while (i < width + 2)
    {
        map[height + 1][i] = ' ';
        i++;
    }

    for (int i=0; i<height;i++)
    {
        for (int j=0; j<width;j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    close(fd);
    return 0;
}

int main()
{
    char **map;
    char arr[12][12] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', ' '},
        {' ', ' ', ' ', '1', '0', '0', '0', '0', '0', '0', '1', ' '},
        {' ', '1', '1', '1', '1', '0', '0', '0', '0', '0', '1', ' '},
        {' ', '1', '0', '0', '0', '0', '1', '1', '1', '1', '1', ' '},
        {' ', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1', ' '},
        {' ', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1', ' '},
        {' ', '1', '0', '0', '0', '0', '0', '1', '1', '1', '1', ' '},
        {' ', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1', ' '},
        {' ', '1', '0', '0', '0', '0', '1', '0', '1', '1', '1', ' '},
        {' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };
    if (read_map(map))
        printf("Error\n");
    // if (isClosed(map))
    //     printf("Error\n");

    return 0;
}