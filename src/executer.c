/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:01:44 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/07 23:41:42 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_execute(t_list **garbg, t_args **args, char **envp)
{
	if ((*args)->infile >= 0)
		function_faillure(garbg, dup2((*args)->infile, STDIN_FILENO), ERRDUP2);
	function_faillure(garbg, pipe((*args)->fd), ERRPIPE);
	exec_command(*args, garbg, envp);
	if ((*args)->cmds_path[1])
	{
		function_faillure(garbg, \
		dup2((*args)->outfile, STDOUT_FILENO), ERRDUP2);
		function_faillure(garbg, \
		execve((*args)->cmds_path[1], (*args)->cmds[1], envp), ERREXEC);
	}
}

void	exec_command_noinfile(t_args *args, t_list **garbg)
{
	function_faillure(garbg, dup2(args->fd[0], STDIN_FILENO), ERRDUP2);
	function_faillure(garbg, close(args->fd[1]), ERRCLOSE);
	function_faillure(garbg, close(args->fd[0]), ERRCLOSE);
}

void	exec_command(t_args *args, t_list **garbg, char **envp)
{
	int	pid;

	if (args->infile >= 0 && args->cmds_path[0])
	{
		pid = fork();
		function_faillure(garbg, pid, ERRFRK);
		if (!pid)
		{
			function_faillure(garbg, \
			dup2(args->fd[1], STDOUT_FILENO), ERRDUP2);
			function_faillure(garbg, close(args->fd[1]), ERRCLOSE);
			function_faillure(garbg, close(args->fd[0]), ERRCLOSE);
			function_faillure(garbg, \
			execve(args->cmds_path[0], args->cmds[0], envp), ERREXEC);
		}
		else
		{
			function_faillure(garbg, dup2(args->fd[0], STDIN_FILENO), ERRDUP2);
			function_faillure(garbg, close(args->fd[1]), ERRCLOSE);
			function_faillure(garbg, close(args->fd[0]), ERRCLOSE);
			function_faillure(garbg, waitpid(pid, NULL, F_OK), ERRWAIT);
		}
	}
	else
		exec_command_noinfile(args, garbg);
}
