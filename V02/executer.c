/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:10:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/27 15:58:42 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

void	exec_command(t_args *args, t_list **garbg, char **envp, int i)
{
	*(args->pids + i) = fork();
	if (*(args->pids + i) == 0)
	{
		dup2(args->fd[i][1], STDOUT_FILENO);
		close(args->fd[i][1]);
		close(args->fd[i][0]);
		execve(args->cmds_path[i], args->cmds[i], envp);
	}
	else
	{
		dup2(args->fd[i][0], STDIN_FILENO);
		close(args->fd[i][1]);
		close(args->fd[i][0]);
		waitpid(*(args->pids + i), NULL, F_OK);
	}
}
