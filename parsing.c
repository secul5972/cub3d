/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:32:09 by chaekim           #+#    #+#             */
/*   Updated: 2022/08/06 21:04:46 by secul5972        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

// elements structure 
typedef struct s_elements
{
	// texture pointerS
	void	*n_texture;
	void	*s_texture;
	void	*w_texture;
	void	*e_texture;
	// rgb colors
	int		f_rgb[3];
	int		c_rgb[3];
}	t_elements;

// .cub 파일 내에서 줄바꿈 기호의 위치 반환
int	until_newline(char *content, int i)
{
	while (content[i] != '\n')
		i++;
	return (i);
}

// rgb 색상 숫자로 저장 (색상 문자열에서 공백일 포함될 떄의 경우 처리 필요?)
int	get_rgb(char **elem, t_elements *dt)
{
	char	**rgb;
	int		colors[3];
	int		i;

	rgb = ft_split(elem[1], ',');
	if (rgb[3] != 0)
		return (0);
	i = -1;
	while (++i < 3)
	{
		colors[i] = ft_atoi(rgb[i]);
		if (!(0 <= colors[i] && colors[i] <= 255))
			break ;
	}
	if (i != 3)
		return (0);
	if (ft_strcmp(elem[0], "F") == 0)
	{
		while (--i >= 0)
			dt->f_rgb[i] = colors[i];
	}
	else
	{
		while (--i >= 0)
			dt->c_rgb[i] = colors[i];
	}
	return (1);
}

int	is_map_start(char **elems)
{
	int	i;
	int	j;

	i = 0;
	while (elems[i])
	{
		j = 0;
		while (elems[i][j])
		{
			if (elems[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int is_valid_elements(char **elems) // return 0 - fail, 1 - success, 2 - map started
{
	int	i;

	i = 0;
	if (is_map_start(elems))
		return (2);
	while (elems[i])
		i++;
	if (i != 2)
		return (0);
	if (!(ft_strcmp(elems[0], "NO") == 0 || ft_strcmp(elems[0], "SO") == 0\
		|| ft_strcmp(elems[0], "WE") == 0 || ft_strcmp(elems[0], "EA") == 0\
		|| ft_strcmp(elems[0], "F") == 0 || ft_strcmp(elems[0], "C") == 0))
		return (0);
	return (1);
}

// 각 식별자를 기준으로 필요한 정보 저장
int	get_elements(char *line, t_elements *dt, t_cub3d_data *cub) // return 0 - fail, 1 - success, 2 - map started
{
	char	**elem;
	int		img_width;
	int		img_height;

	if (line[0] == '\0')
		return (-1);
	elem = ft_split(line, ' ');
	if (!is_valid_elements(elem))
		return (0);
	printf("%s: %s\n", elem[0], elem[1]);
	// mlx_xpm_file_to_image: 존재하지 않는 파일이면 null 반환
	if (ft_strcmp(elem[0], "NO") == 0)
		dt->n_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], &img_width, &img_height);
	else if (ft_strcmp(elem[0], "SO") == 0)
		dt->s_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], &img_width, &img_height);
	else if (ft_strcmp(elem[0], "WE") == 0)
		dt->w_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], &img_width, &img_height);
	else if (ft_strcmp(elem[0], "EA") == 0)
		dt->e_texture = mlx_xpm_file_to_image(cub->mlx, elem[1], &img_width, &img_height);
	else if (ft_strcmp(elem[0], "F") == 0 || ft_strcmp(elem[0], "C") == 0)
	{
		if (!get_rgb(elem, dt))
			return (0);
	}
	else
		return (2);
	return (1);
}

// 필요한 정보들이 다 저장되었는지
int	is_all_stored(t_elements *dt) // return 0 - fail, 1 - success
{
	if (!dt->n_texture || !dt->s_texture || !dt->w_texture || !dt->e_texture)
		return (0);
	if (dt->f_rgb[0] == -1 || dt->f_rgb[1] == -1 || dt->f_rgb[2] == -1)
		return (0);
	if (dt->c_rgb[0] == -1 || dt->c_rgb[1] == -1 || dt->c_rgb[2] == -1)
		return (0);
	return (1);
}

//.cub 파일 데이터 파싱 (맵 전까지)
int	parsing(char *content, t_elements *dt, t_cub3d_data *cub) // return 0 - fail, 1 - success
{
	char	*line;
	int		i;
	int		res;
	int		new_line_idx;

	line = 0;
	i = 0;
	while (content[i])
	{
		new_line_idx = until_newline(content, i);
		line = (char *)malloc(sizeof(char) * (new_line_idx - i + 1));
		if (!line)
			return (0);
		ft_strcpy(line, content, i, new_line_idx);
		res = get_elements(line, dt, cub);
		free(line);
		if (res == 0)
			return (0);
		else if (res == 2)
			break ;
		i = new_line_idx + 1;
	}
	if (!is_all_stored(dt))
		return (0);
	return (1);
}

// t_elements 구조체 초기화
void	init_texture(t_elements *dt)
{
	dt->n_texture = 0;
	dt->s_texture = 0;
	dt->w_texture = 0;
	dt->e_texture = 0;
	dt->f_rgb[0] = -1;
	dt->f_rgb[1] = -1;
	dt->f_rgb[2] = -1;
	dt->c_rgb[0] = -1;
	dt->c_rgb[1] = -1;
	dt->c_rgb[2] = -1;
}

/*---------------main.c copy----------------------------*/
int p_error(char *str, int len)
{
    write(2, str, len);
    return (1);
}

int cub3d_init(t_cub3d_data *cub, t_img *img)
{
    cub->mlx = mlx_init();
    cub->width = 800;
    cub->length = 800;
	cub->win = mlx_new_window(cub->mlx, cub->width, cub->length, "cub3d");
	/*img->img_ptr = mlx_new_image(cub->mlx, cub->width, cub->length);
	img->data_ptr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	if (cub->mlx == 0 || cub->win == 0 || img->img_ptr == 0 || \
	img->data_ptr == 0)
        return p_error("mlx error\n", 11);*/

    return (0);
}

int	press_esc(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}
/*-----------------------------------------------------*/

int main()
{
	char str[] = "NO ./texture/sample.xpm\n\
SO ./texture/sample.xpm\n\
WE ./texture/sample.xpm\n\
EA ./texture/sample.xpm\n\n\
F 220,100,0\n\
C 225,30,0\n\n\
        1111111111111111111111111\n\
        1000000000110000000000001\n\
        1011000001110000000000001\n\
        1001000000000000000000001\n\
111111111011000001110000000000001\n\
100000000011000001110111111111111\n\
11110111111111011100000010001\n\
11110111111111011101010010001\n\
11000000110101011100000010001\n\
10000000000000001100000010001\n\
10000000000000001101010010001\n\
11000001110101011111011110N0111\n\
11110111 1110101 101111010001\n\
11111111 1111111 111111111111";
	t_elements	dt;
	t_cub3d_data cub;

	if (cub3d_init(&cub, &cub.img))
        return (1);
	init_texture(&dt);
	if (!parsing(str, &dt, &cub))
		printf("Error\n");
	else
		printf("OK\n");
	mlx_put_image_to_window(cub.mlx, cub.win, dt.n_texture, 0, 0);
	mlx_key_hook(cub.win, press_esc, 0);
    mlx_loop(cub.mlx);
	return (0);
}