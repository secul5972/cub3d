/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungcoh <seungcoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:54:09 by seungcoh          #+#    #+#             */
/*   Updated: 2021/06/21 19:09:16 by seungcoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# ifndef FD_SIZE
#  define FD_SIZE 256
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

int		new_line_idx(char *str, int *ret, int flag);
int		sep_buf(char **t_line, int ret, int idx);
int		get_next_line(int fd, char **line);
int		ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *src, int offset);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
