/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:39:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/06 05:39:33 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*get_next_line(int fd, t_list **garbg)
{
	static char	*hold;
	char		*line;
	char		*tmp;
	int			count;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (line);
	count = 0;
	line = ft_read(fd, garbg);
	if (hold)
	{
		tmp = ft_strfreejoin(hold, line, garbg);
		line = tmp;
		hold = NULL;
	}
	if (line && ft_memchr_ind(line, '\n') != -1)
	{
		hold = ft_hold(line, garbg);
		line = ft_line(line, garbg);
	}
	return (line);
}

char	*ft_hold(char *line, t_list **garbg)
{
	char	*hold;
	size_t	i;
	int		j;

	i = -1;
	hold = NULL;
	while (line && line[++i])
		if (line[i] == '\n')
			break ;
	if (line && line[i] == '\n' && line[i + 1])
	{
		j = 0;
		hold = ft_malloc(malloc(ft_strlen_util(line) - i + 2), garbg);
		while (line[i] && i++ < ft_strlen_util(line))
			hold[j++] = line[i];
		hold[j] = 0;
	}
	return (hold);
}

char	*ft_line(char *line, t_list **garbg)
{
	char	*tmp;
	int		i;
	int		count;

	i = -1;
	while (line[++i])
		if (line[i] == '\n')
			break ;
	if (line[i] == '\n' && line[i + 1])
	{
		tmp = ft_malloc(malloc(i + 2), garbg);
		count = -1;
		while (++count <= i)
			tmp[count] = line[count];
		tmp[count] = 0;
		line = tmp;
	}
	return (line);
}

char	*ft_read(int fd, t_list **garbg)
{
	char	*line;
	char	*tmp;
	int		count;

	line = NULL;
	tmp = ft_malloc(malloc((BUFFER_SIZE + 1) * sizeof(char)), garbg);
	count = 1;
	while (ft_memchr_ind(line, '\n') == -1 && count)
	{
		count = read(fd, tmp, BUFFER_SIZE);
		if (count < 0)
			return (ft_exit(ERREAD, garbg, 1), NULL);
		tmp[count] = 0;
		if (count)
			line = ft_strfreejoin(line, tmp, garbg);
	}
	return (line);
}
