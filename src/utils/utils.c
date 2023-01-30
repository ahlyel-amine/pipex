/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:53:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/30 16:32:52 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	ft_exit(char *error_msg, t_list **garbg, int status)
{
	(void)error_msg;
	if (status)
	{
		ft_lstclear(garbg, free);
		exit(EXIT_SUCCESS);
	}
	ft_putstr_fd(error_msg, STDERR_FILENO);
	if (errno)
		perror("");
	ft_lstclear(garbg, free);
	exit(EXIT_FAILURE);
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
