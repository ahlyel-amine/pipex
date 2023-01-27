/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:01:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/27 16:00:25 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

int	main(int ac, char **av, char **envp)
{
	t_args	*args;
	t_list	*garbg;

	garbg = NULL;
	args = ft_malloc(malloc(sizeof(t_args)), &garbg);
	args->ac = ac;
	args->av = av;
	ft_parse(&garbg, &args, envp);
	args->fd = ft_malloc(malloc(sizeof(int[2]) * ac - 3), &garbg);
	args->pids = ft_malloc(malloc(sizeof(int) * ac - 3), &garbg);
	int	i = 0;
	while (i < ac - 4)
		if (pipe(*(args->fd + i++)) < 0)
			ft_exit("yo", &garbg);
	i = 0;
	while (i < ac - 3)
	{
		if (i != ac  - 4)
			exec_command(args, &garbg, envp, i);
		else
		{
			dup2(args->outfile, STDOUT_FILENO);
			execve(args->cmds_path[i], args->cmds[i], envp);
		}
		i++;
	}
}
