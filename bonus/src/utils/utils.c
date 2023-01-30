/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:53:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/30 14:54:25 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	ft_exit(char *error_msg, t_list **garbg)
{
	if(error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
	ft_lstclear(garbg, free);
	exit(EXIT_FAILURE);
}

void	*ft_malloc(void *pointer, t_list **garbg)
{
	t_list	*new;

	new = NULL;
	if (!pointer)
		ft_exit("Allocation failure", garbg);
	new = ft_lstnew(pointer);
	if (!new)
	{
		free(pointer);
		ft_exit("Allocation failure", garbg);
	}
	ft_lstadd_back(garbg, new);
	return (pointer);
}
