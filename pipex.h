/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:04:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/12 13:22:05 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"
#include <sys/errno.h>
#include <fcntl.h>

# define STDOUT 1
# define STDIN 0
# define STDERR 2
# define SIDE_OUT 1
# define SIDE_IN 0

# define R_LEFT 1
# define R_RIGHT 2
# define R_DRIGHT 3
# define R_DLEFT 4
# define PIPE 5

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
