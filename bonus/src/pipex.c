/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:01:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/29 22:56:26 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_args	*args;
	t_list	*garbg;

	garbg = NULL;
	args = ft_malloc(malloc(sizeof(t_args)), &garbg);
	args->ac = ac;
	args->av = av;
	ft_parse(&garbg, &args, envp);
	// if (args->heredoc)
	// 	ft_execute_heredoc(&garbg, &args, envp);
	ft_execute(&garbg, &args, envp);
}
