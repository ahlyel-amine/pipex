/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:10:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/17 01:22:34 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

// int	child_process(t_args *args, t_list **garbg, int pid_indice, char **envp)
// {
// 	(*args).pids[pid_indice] = fork();
// 	if (!(*args).pids[pid_indice])
// 	{
// 		dup2((*args).infile, STDIN_FILENO);
// 		dup2((*args).fd[1], STDOUT_FILENO);
// 		close((*args).fd[1]);
// 		close((*args).fd[0]);
// 		execve((*args).cmds_path[pid_indice], (*args).cmds[pid_indice], envp);
// 		return (1);
// 	}
// 	return (0);
// }

int	first_child_process(t_args *args, t_list **garbg, int pid_indice, char **envp)
{

	puts("a");
	(*args).pids[pid_indice] = fork();
	if (!(*args).pids[pid_indice])
	{
		if (pipe((*args).fd) == -1)
			ft_exit("Error function pipe failure", garbg);
		dup2((*args).fd[1], STDOUT_FILENO);
		close((*args).fd[1]);
		close((*args).fd[0]);
		dup2((*args).infile, STDIN_FILENO);
		execve((*args).cmds_path[pid_indice], (*args).cmds[pid_indice], envp);
	}
	if ((*args).pids[pid_indice])
	{
		close((*args).fd[0]);
		printf("%d\n", waitpid((*args).pids[0], NULL, 0));
	}
	return (0);
}

int	middle_childs_process(t_args *args, t_list **garbg, int pid_indice, char **envp)
{
	puts("b");

	(*args).pids[pid_indice] = fork();
	if (!(*args).pids[pid_indice])
	{
		if (pipe((*args).fd) == -1)
			ft_exit("Error function pipe failure", garbg);
		dup2((*args).fd[0], STDIN_FILENO);
		close((*args).fd[1]);
		close((*args).fd[0]);
		dup2((*args).fd[1], STDOUT_FILENO);
		execve((*args).cmds_path[pid_indice], (*args).cmds[pid_indice], envp);
		return (1);
	}
	if ((*args).pids[pid_indice])
	{
		// close((*args).fd[0]);
		// close((*args).fd[1]);
		waitpid((*args).pids[pid_indice], NULL, 0);
	}
	return (0);
}

int	last_child_process(t_args *args, t_list **garbg, int pid_indice, char **envp)
{
	puts("c");
	char *v = malloc(4000);
	read((*args).fd[0], v, 4000);
	write((*args).fd[1], v, 10);
	(*args).pids[pid_indice] = fork();
	if (!(*args).pids[pid_indice])
	{
		if (pipe((*args).fd) == -1)
			ft_exit("Error function pipe failure", garbg);
		dup2((*args).fd[0], STDIN_FILENO);
		close((*args).fd[1]);
		close((*args).fd[0]);
		dup2((*args).outfile, STDOUT_FILENO);
		execve((*args).cmds_path[pid_indice], (*args).cmds[pid_indice], envp);
	}
	if ((*args).pids[pid_indice])
	{
		puts("tyo");
		close((*args).fd[0]);
		close((*args).fd[1]);
		printf("%d\n",waitpid((*args).pids[pid_indice], NULL, 0));
	}
	return (0);
}
