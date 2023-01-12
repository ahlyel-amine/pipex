/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:10:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/12 21:27:02 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

int	child_process(t_args *arguments, t_list **garbage, int pid_indice, char **envp)
{
	(*arguments).pids[pid_indice] = fork();
	if (!(**arguments).pids[pid_indice])
	{
		dup2((*arguments).fd[1], STDOUT_FILENO);
		close((*arguments).fd[1]);
		close((*arguments).fd[0]);
		dup2((*arguments).infile, STDIN_FILENO);
		execve((*arguments).cmd_path[pid_indice], (*arguments).cmds[pid_indice], envp);
		return (1);
	}
	return (0);
}
