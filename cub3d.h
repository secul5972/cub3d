/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:44:51 by seungcoh          #+#    #+#             */
/*   Updated: 2022/08/03 13:19:00 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>

# define KeyExit_X_EVENT 17
# define LeaveWindowMask 1L<<5

typedef struct s_img
{
    void *img_ptr;
    char *data_ptr;
    int bits_per_pixel;
    int line_length;
    int endian;
}   t_img;

typedef struct s_cub3d_data
{
    void *win;
    void *mlx;
    t_img img;
    float width;
    float length;
}   t_cub3d_data;

char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);
void	ft_strcpy(char *s1, char *s2, int start, int end);
int		ft_strcmp(const char *s1, const char *s2);
void	free_str(char **strs);

#endif