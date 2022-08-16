/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secul5972 <secul5972@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:44:51 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/16 11:51:27 by secul5972        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h" //# include "mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# include <stdio.h>

# define KEYEXIT_X_EVENT	17
# define KEYPRESS_X_EVENT	02

/*# define LEAVEWINDOWMASK	1L << 5
# define KEYPRESS_X_MASK	1L << 0*/

# define KEY_ESC	65307 //mac: 53, linux: 65307
# define KEY_W		119 //mac: 13, linux: 119
# define KEY_A		97 //mac: 0, linux: 97
# define KEY_S		115 //mac: 1, linux: 115
# define KEY_D		100 //mac: 2, linux: 100

# define KEY_LEFT	65361 //mac: 123, linux: 65361
# define KEY_RIGHT	65363 //mac: 124, linux: 65363

# define BORDER 0.0001

typedef struct s_line_lst
{
	struct s_line_lst	*next;
	char				*line;
	int					len;
}	t_line_lst;

typedef struct s_img
{
	void	*img_ptr;
	int		*data_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_vecd
{
	double	x;
	double	y;
}	t_vecd;

typedef struct s_veci
{
	int	x;
	int	y;
}	t_veci;

typedef struct s_dda_data
{
	t_veci	map_pos;
	t_veci	dmap_pos;
	t_vecd	len;
	t_vecd	dlen;
	int		side;
}	t_dda_data;

typedef struct s_cub3d_data
{
	void	*win;
	void	*mlx;
	t_img	img;
	// window
	float	w_width;
	float	w_height;
	
	// texture pointers
	void	*n_texture;
	void	*s_texture;
	void	*w_texture;
	void	*e_texture;
	// rgb colors
	int		floor_color;
	int		ceiling_color;

	//file
	int		fd;
	char	contents[300000];

	// map
	char	**map;
	int		m_width;
	int		m_height;

	//vec
	t_vecd	cpos;
	t_vecd	cdir;
	t_vecd	plane;
	t_vecd	ray;

	//dx
	int		dx[4];
	int		dy[4];

	double	xrate;
	double	yrate;

	double	rotate_angle;
	double	frame_time;
}	t_cub3d_data;

int		read_map(t_cub3d_data *cub);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);
int		ft_strcpy(char *s1, char *s2, int start, int end);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_max(int a, int b);
void	free_str(char **strs);
int		free_and_return(char **strs, int ret);
int		read_line(int fd, char **line);
int		free_list(t_line_lst *head);
int		free_map(char **map, int height);
void	make_vec(t_vecd *v, double x, double y);
int		parsing(t_cub3d_data *cub);
int		get_rgb(char **elem, t_cub3d_data *cub);
void	free_all(t_cub3d_data *cub);
void	fix_map_find_pos(t_cub3d_data *cub);
int		get_lst(t_cub3d_data *cub, t_line_lst *head, t_line_lst *curr);
int		lst_to_map(t_cub3d_data *cub, t_line_lst *head, t_line_lst *curr);
void	ray_casting(t_cub3d_data *cub);
void	dda(t_cub3d_data *cub, t_vecd ray, int screenX, double cposToWallDist);
double	vec_scale(t_vecd v);
int		press_key(int keycode, t_cub3d_data *cub);
int		press_x_button(t_cub3d_data *cub);
int		press_esc(t_cub3d_data *cub);
void	reset_background(t_cub3d_data *cub);
void	free_all(t_cub3d_data *cub);
int		p_error(char *str, int len);

#endif