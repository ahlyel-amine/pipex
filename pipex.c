// #include "pipex.h"
#include "libft/libft.h"

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

int main(int argc, char **argv, char **envp)
{
	char	**path;
	char	*cmd1;
	char	*cmd2;
	int		infile;
	int		outfile;
	int		ppid;
	int		cpid;
	int		fd[2];

	unlink(argv[argc - 1]);
	infile = open(argv[1], O_CREAT | O_RDONLY, 0644);
	outfile = open(argv[argc - 1], O_CREAT | O_RDWR, 0644);
	if (pipe(fd) == -1)
		return (perror("Error"), 1);
	path = ft_split(&envp[6][5], ':');
	cmd1 = check_command(path, *ft_split(argv[2], ' '));
	cmd2 = check_command(path, *ft_split(argv[3], ' '));
	ppid = fork();
	if (!ppid)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		dup2(infile, STDIN_FILENO);
		execve(cmd1, ft_split(argv[2], ' '), envp);
	}
	cpid = fork();
	if (!cpid)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		dup2(outfile, STDOUT_FILENO);
		execve(cmd2, ft_split(argv[3], ' '), envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(ppid, NULL, 0);
	waitpid(cpid, NULL, 0);
	return 0;
}
