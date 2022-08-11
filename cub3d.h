/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:44:51 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/11 15:07:03 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include <stdio.h>

# define KEYEXIT_X_EVENT	17
# define KEYPRESS_X_EVENT	02

/*# define LEAVEWINDOWMASK	1L << 5
# define KEYPRESS_X_MASK	1L << 0*/

# define KEY_ESC 53

typedef struct s_line_lst
{
	struct s_line_lst	*next;
	char				*line;
	int					len;
}	t_line_lst;

typedef struct s_img
{
	void	*img_ptr;
	char	*data_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_cub3d_data
{
	void	*win;
	void	*mlx;
	t_img	img;
	// window
	float	w_width;
	float	w_height;
	
	// texture pointerS
	void	*n_texture;
	void	*s_texture;
	void	*w_texture;
	void	*e_texture;
	// rgb colors
	int		f_rgb[3];
	int		c_rgb[3];

	//file
	int		fd;
	char	contents[300000];

	// map
	char	**map;
	int		m_width;
	int		m_height;

    //vec
    t_vec cpos;
    t_vec cdir;
    t_vec plane;
    
    //dx
    int dx[4];
    int dy[4];
}   t_cub3d_data;

int		read_map(t_cub3d_data *cub);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);
int		ft_strcpy(char *s1, char *s2, int start, int end);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_max(int a, int b);
void	free_str(char **strs);
int		free_and_return(char **strs, int ret);
int		read_line(int fd, char **line);
int     free_list(t_line_lst *head);
int 	free_map(char **map, int height);
void    make_vec(t_vec *v, double x, double y);
int		parsing(t_cub3d_data *cub);
void    fix_map_find_pos(t_cub3d_data *cub);
int     get_lst(t_cub3d_data *cub, t_line_lst *head, t_line_lst *curr);
int     lst_to_map(t_cub3d_data *cub, t_line_lst *head, t_line_lst *curr);
void	get_ray(t_cub3d_data *cub);

#endif