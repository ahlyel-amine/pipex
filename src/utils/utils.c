/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:53:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/03 18:09:17 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	ft_set_err(char *error_msg)
{
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
	else if (errno)
		perror("");
}

void	ft_exit(char *error_msg, t_list **garbg, int exit_status)
{
	(void)garbg;
	garbg = NULL;
	if (!exit_status)
	{
		ft_lstclear(garbg, free);
		exit(EXIT_SUCCESS);
	}
	if (errno)
		perror("");
	else
		ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_lstclear(garbg, free);
	exit(EXIT_FAILURE);
}

void	*ft_malloc(void *pointer, t_list **garbg)
{
	t_list	*new;

	new = NULL;
	if (!pointer)
		ft_exit(ERRALLOC, garbg, 1);
	new = ft_lstnew(pointer);
	if (!new)
	{
		free(pointer);
		ft_exit(ERRALLOC, garbg, 1);
	}
	ft_lstadd_back(garbg, new);
	return (pointer);
}
