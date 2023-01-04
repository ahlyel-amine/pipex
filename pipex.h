#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>

typedef struct s_pipex
{
	char	**path;
	char	*cmd1;
	char	*cmd2;
	int		infile;
	int		outfile;
	int		pid1;
	int		pid2;
	int		fd[2];
}	t_pipex;

#endif
