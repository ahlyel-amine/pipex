/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:59:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/06 20:14:06 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../../libft/include/libft.h"
# include "../../../include/pipex_bonus.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd, t_list **garbg);
char	*ft_strfreejoin(char *s1, char *s2, t_list **garbg);
int		ft_memchr_ind(char *str, char c);
size_t	ft_strlen_util(const char *s);
char	*ft_strdup_util(const char *s1);
char	*ft_read(int fd, t_list **garbg);
char	*ft_line(char *line, t_list **garbg);
char	*ft_hold(char *line, t_list **garbg);

#endif
