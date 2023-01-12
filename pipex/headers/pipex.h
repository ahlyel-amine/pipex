/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:20 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/12 14:34:58 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <sys/errno.h>

#define STDERR 2

/// @brief argumets
typedef struct s_args
{
		char	**path;
		char	*cmd1;
		char	*cmd2;
		int		infile;
		int		outfile;
		int		pid1;
		int		pid2;
		int		fd[2];
}	t_args;

/// @brief
/// @param arguments
/// @param argv
/// @param argc
void	get_args(t_args *arguments, char **argv, int argc);

#endif
