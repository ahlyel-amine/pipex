/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:01:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/30 14:48:31 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>
int	main(int ac, char **av, char **envp)
{
	t_args	*args;
	t_list	*garbg;

	garbg = NULL;
	args = ft_malloc(malloc(sizeof(t_args)), &garbg);
	args->ac = ac;
	args->av = av;
	ft_parse(&garbg, &args, envp);
	if (args->limiter)
		args->ac--;
	ft_execute(&garbg, &args, envp);
	if (args->limiter)
		unlink(".heredoc");
}
