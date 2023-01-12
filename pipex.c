/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:04:09 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/12 13:44:28 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <fcntl.h>

/// @brief
/// @param path		double pointer to lists of paths in the env
/// @param command	command line
/// @return			pointer to the path of command or NULL if doesnt exist
char	*check_command(char **path, char *command)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = -1;
	cmd_path = NULL;
	while (i == -1 && *path)
	{
		tmp = ft_strjoin(*path++, "/");
		cmd_path = ft_strjoin(tmp, command);
		free(tmp);
		i = access(cmd_path, F_OK);
		if (i != -1)
			break ;
		free (cmd_path);
		cmd_path = NULL;
	}
	return (cmd_path);
}

/// @brief
/// @param argv
/// @param envp
/// @param pi
/// @return
int	child_process1(char **argv, char **envp, t_pipex pi)
{
	pi.pid1 = fork();
	if (!pi.pid1)
	{
		dup2(pi.fd[1], STDOUT_FILENO);
		close(pi.fd[1]);
		close(pi.fd[0]);
		dup2(pi.infile, STDIN_FILENO);
		execve(pi.cmd1, ft_split(argv[2], ' '), envp);
		return (1);
	}
	return (0);
}

/// @brief
/// @param argv
/// @param envp
/// @param pi
/// @return
int	child_process2(char **argv, char **envp, t_pipex pi)
{
	pi.pid2 = fork();
	if (!pi.pid2)
	{
		dup2(pi.fd[0], STDIN_FILENO);
		close(pi.fd[1]);
		close(pi.fd[0]);
		dup2(pi.outfile, STDOUT_FILENO);
		execve(pi.cmd2, ft_split(argv[3], ' '), envp);
		return (1);
	}
	return (0);
}

char	*env(char **envp)
{
	int	i;

	i = 0;
	while (*(envp + i))
	{
		if (ft_strnstr(*(envp + i), "PATH=", 5))
			return (ft_substr(*(envp + i), 5,
				ft_strlen((*(envp + i)) + 5)));
		i++;
	}
	return (NULL);
}

/// @brief
/// @param argc
/// @param argv
/// @param envp
/// @return
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pi;

	unlink(argv[argc - 1]);
	pi.infile = open(argv[1], O_CREAT | O_RDONLY, RDWR);
	pi.outfile = open(argv[argc - 1], O_CREAT | O_RDWR, RDWR);
	if (pi.infile < 0 || pi.outfile < 0)
		ft_exit("Error file");
	if (pipe(pi.fd) == -1)
		close(pi.fd[0]), close(pi.fd[1]), ft_exit("Error pipe");
	pi.path = ft_split(env(envp), ':');
	pi.cmd1 = check_command(pi.path, *ft_split(argv[2], ' '));
	pi.cmd2 = check_command(pi.path, *ft_split(argv[3], ' '));
	if (!pi.cmd1 || !pi.cmd2)
		close(pi.fd[0]), close(pi.fd[1]), ft_exit("Error Command not found");
	if (child_process1(argv, envp, pi)
		|| child_process2(argv, envp, pi))
		close(pi.fd[0]), close(pi.fd[1]), ft_exit("Error child process");
	if (close(pi.fd[0]) || close(pi.fd[1]))
		ft_exit("file does not closed correctly");
	if (waitpid(pi.pid1, NULL, 0) == -1 || waitpid(pi.pid2, NULL, 0) == -1)
		ft_exit("Error child process does not exit correctly");
	return (0);
}
