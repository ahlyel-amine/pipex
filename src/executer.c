/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:01:44 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/04 23:45:57 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_execute(t_list **garbg, t_args **args, char **envp)
{
	int	pid;

	if ((*args)->infile >= 0)
		function_faillure(garbg, dup2((*args)->infile, STDIN_FILENO), ERRDUP2);
	function_faillure(garbg, pipe((*args)->fd), ERRPIPE);
	exec_command(*args, garbg, envp);
	pid = fork();
	function_faillure(garbg, pid, ERRFRK);
	if (!pid)
	{
		function_faillure(garbg, \
		dup2((*args)->outfile, STDOUT_FILENO), ERRDUP2);
		function_faillure(garbg, \
		execve((*args)->cmds_path[1], (*args)->cmds[1], envp), ERREXEC);
	}
}

void	exec_command(t_args *args, t_list **garbg, char **envp)
{
	int	pid;

	if (args->infile >= 0)
	{

		pid = fork();
		function_faillure(garbg, pid, ERRFRK);
		if (!pid)
		{
			puts("in");
			// function_faillure(garbg, 
			dup2(args->fd[1], STDOUT_FILENO);/*, ERRDUP2);*/
			puts("out");
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
		function_faillure(garbg, dup2(args->outfile, STDIN_FILENO), ERRDUP2);
}
