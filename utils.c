/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:19:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/12 13:21:06 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(char *error_msg)
{
	if (errno)
		perror(error_msg);
	else
		ft_putendl_fd(error_msg, STDERR);
	exit(EXIT_FAILURE);
}
