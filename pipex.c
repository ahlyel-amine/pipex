#include "pipex.h"

#include <errno.h>
#include <fcntl.h>

char *check_command(char **path, char *command)
{
	char	*cmd_path;
	char	*tmp;
	int		i;
	int		j;

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

int	child_process1(char **argv, char **envp, t_pipex pipex)
{
	pipex.pid1 = fork();
	if (!pipex.pid1)
	{
		dup2(pipex.fd[1], STDOUT_FILENO);
		close(pipex.fd[1]);
		close(pipex.fd[0]);
		dup2(pipex.infile, STDIN_FILENO);
		execve(pipex.cmd1, ft_split(argv[2], ' '), envp);
		return (1);
	}
	return (0);
}

int	child_process2(char **argv, char **envp, t_pipex pipex)
{
	pipex.pid2 = fork();
	if (!pipex.pid2)
	{
		dup2(pipex.fd[0], STDIN_FILENO);
		close(pipex.fd[1]);
		close(pipex.fd[0]);
		dup2(pipex.outfile, STDOUT_FILENO);
		execve(pipex.cmd2, ft_split(argv[3], ' '), envp);
		return (1);
	}
	return (0);
}

int	destroy(int open, int pipe, int command, int child_process)
{
	if (open)
		return (perror("Error file"), 1);
	else if (pipe)
		return (perror("Error pipe"), 1);
	else if (command)
		return (perror("Error Command not found"), 1);
	else if (child_process)
		return (perror("Error child process"), 1);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	unlink(argv[argc - 1]);
	pipex.infile = open(argv[1], O_CREAT | O_RDONLY, 0644);
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_RDWR, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
		return (destroy(1, 0, 0, 0));
	if (pipe(pipex.fd) == -1)
		return (close(pipex.fd[0]), close(pipex.fd[1]),
		destroy(0, 1, 0, 0));
	pipex.path = ft_split(&envp[6][5], ':');
	pipex.cmd1 = check_command(pipex.path, *ft_split(argv[2], ' '));
	pipex.cmd2 = check_command(pipex.path, *ft_split(argv[3], ' '));
	if (!pipex.cmd1 || !pipex.cmd2)
		return (close(pipex.fd[0]), close(pipex.fd[1]),
		destroy(0, 0, 1, 0));
	if (!child_process1(argv, envp, pipex) || !child_process2(argv, envp, pipex))
		return (close(pipex.fd[0]), close(pipex.fd[1]),
		destroy(0, 0, 0, 1));
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return 0;
}
