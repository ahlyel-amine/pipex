/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:53:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/06 20:14:53 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

int	faillure(t_list **garbg, int return_value, char *exit_message)
{
	if (return_value < 0)
		ft_exit(exit_message, garbg, 1);
	return (return_value);
}

void	ft_set_err(char *error_msg)
{
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
	else if (errno)
		perror("");
}

void	ft_exit(char *error_msg, t_list **garbg, int exit_status)
{
	if (!exit_status)
	{
		ft_lstclear(garbg, free);
		exit(EXIT_SUCCESS);
	}
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
	else if (errno)
		perror("");
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
