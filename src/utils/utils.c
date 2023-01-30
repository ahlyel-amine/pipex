/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:53:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/30 17:47:54 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	ft_exit(char *error_msg, t_list **garbg, int status)
{
	(void)error_msg;
	if (!status)
	{
		ft_lstclear(garbg, free);
		exit(EXIT_SUCCESS);
	}
	if (errno)
		perror(error_msg);
	else
		ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_lstclear(garbg, free);
	exit(status);
}

void	*ft_malloc(void *pointer, t_list **garbg)
{
	t_list	*new;

	new = NULL;
	if (!pointer)
		ft_exit(ERRALLOC, garbg, 0);
	new = ft_lstnew(pointer);
	if (!new)
	{
		free(pointer);
		ft_exit(ERRALLOC, garbg, 0);
	}
	ft_lstadd_back(garbg, new);
	return (pointer);
}
