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
#include <stdlib.h>
#include <unistd.h>

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int width = 12;
int height = 12;

typedef struct s_line_lst
{
    struct s_line_lst *next;
    char *line;
    int len;
}   t_line_lst;

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

int ft_strcpy(char *dest, const char *src, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        dest[i] = src[i];
        i++;
    }
    return (i);
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
    ft_strcpy(*line, buffer, i);
    return i;
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
    t_line_lst head;
    t_line_lst *curr;

    fd = open("map.cub", O_RDONLY);
    if (fd < 0)
        return 1;

    len = 1;
    height = 0;
    width = 0;

    curr = &head;
    while (1)
    {
        len = read_line(fd, &line);
        if (len <= 0)
            break;
        width = ft_max(len, width);
        height++;
        curr->next = malloc(sizeof(t_line_lst));
        curr->next->next = 0;
        curr->line = line;
        curr->len = len;
        curr = curr->next;
    }
    close(fd);

    map = (char **)malloc(sizeof(char*) * (height + 2));
    i = 0;
    while (i < height + 2)
         map[i++] = (char *)malloc(sizeof(char) * (width + 2));

    i = 0;
    while (i < width + 2)
    {
        map[0][i] = ' ';
        i++;
    }

    i = 1;
    curr = &head;
    while (curr)
    {
        map[i][0] = ' ';
        j = ft_strcpy(&map[i][1], curr->line, curr->len);
        while (j < width + 2)
        {
            printf("%d\n", j);
            map[i][j] = ' ';
            j++;
        }
        i++;
        curr = curr->next;
    }

    i = 0;
    while (i < width + 2)
    {
        map[height + 1][i] = ' ';
        i++;
    }

    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("f\n");
    }
    return 0;
}

int main()
{
    char **map;
    // char arr[12][12] = {
    //     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    //     {' ', ' ', ' ', '1', '1', '1', '1', '1', '1', '1', '1', ' '},
    //     {' ', ' ', ' ', '1', '0', '0', '0', '0', '0', '0', '1', ' '},
    //     {' ', '1', '1', '1', '1', '0', '0', '0', '0', '0', '1', ' '},
    //     {' ', '1', '0', '0', '0', '0', '1', '1', '1', '1', '1', ' '},
    //     {' ', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1', ' '},
    //     {' ', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1', ' '},
    //     {' ', '1', '0', '0', '0', '0', '0', '1', '1', '1', '1', ' '},
    //     {' ', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1', ' '},
    //     {' ', '1', '0', '0', '0', '0', '1', '0', '1', '1', '1', ' '},
    //     {' ', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', ' '},
    //     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
    if (read_map(map))
        printf("Error\n");
    // if (isClosed(map))
    //     printf("Error\n");

    return 0;
}