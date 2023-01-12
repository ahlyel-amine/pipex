/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:27:09 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/12 14:29:32 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

void	ft_exit(char *error_msg)
{
	if (errno)
		perror(error_msg);
	else
		ft_putendl_fd(error_msg, STDERR);
	exit(EXIT_FAILURE);
}
