/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:10:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/26 19:37:38 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

// // int	child_process(t_args *args, t_list **garbg, int pid_indice, char **envp)
// // {
// // 	(*args).pids[pid_indice] = fork();
// // 	if (!(*args).pids[pid_indice])
// // 	{
// // 		dup2((*args).infile, STDIN_FILENO);
// // 		dup2((*args).fd[1], STDOUT_FILENO);
// // 		close((*args).fd[1]);
// // 		close((*args).fd[0]);
// // 		execve((*args).cmds_path[pid_indice], (*args).cmds[pid_indice], envp);
// // 		return (1);
// // 	}
// // 	return (0);
// // }

void	first_child_process(t_args *args, t_list **garbg, char **envp, int i)
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
