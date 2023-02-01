/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:53:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/01 12:24:25 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	ft_set_err(char *error_msg, int status)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	write(2, "\n", 1);
	errno = status;
}

void	ft_exit(char *error_msg, t_list **garbg, int status)
{
	if (!status)
	{
		ft_lstclear(garbg, free);
		exit(EXIT_SUCCESS);
	}
	if (errno)
	{
		ft_lstclear(garbg, free);
		perror("");
		exit(errno);
	}
	else
	{
		ft_putstr_fd(error_msg, STDERR_FILENO);
		ft_lstclear(garbg, free);
		exit(status);
	}
}

void	*ft_malloc(void *pointer, t_list **garbg)
{
	t_list	*new;

	new = NULL;
	if (!pointer)
		ft_exit(ERRALLOC, garbg, ENOMEM);
	new = ft_lstnew(pointer);
	if (!new)
	{
		free(pointer);
		ft_exit(ERRALLOC, garbg, ENOMEM);
	}
	ft_lstadd_back(garbg, new);
	return (pointer);
}
