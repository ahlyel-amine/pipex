/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:20 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/14 17:55:10 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <sys/errno.h>
# include <fcntl.h>

# define STDERR 2
# define RDWR 0644
char	**ft_split(char const *s, char c, t_list **garbg);
/// @brief argumets saver structur
typedef struct s_args
{
	char	**path;
	char	***cmds;
	char	**cmds_path;
	int		infile;
	int		outfile;
	int		*pids;
	int		pid1;
	int		pid2;
	int		fd[2];
}	t_args;

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_list;


/// @brief garbage collector structur
typedef struct s_garbage_collector
{
	void	*pointer;
	struct s_garbage_collector	*next;
}	t_garbg;

/// @brief exit function in error cases
/// @param error_msg error message to write in stderr
/// @param garbg garbage collector linked list
void	ft_exit(char *error_msg, t_list **garbg);

/// @brief purpose of this function is to save all addresses being allocated
/// @param pointer pointer being allocated
/// @param garbg garbage collector linked list
/// @return pointer being allocated
void	*ft_malloc(void *pointer, t_list **garbg);

/// @brief get environment path
/// @param envp environment variables
/// @return environment path
char	*env_path(char **envp, t_list **garbg);

/// @brief this function translate/check/save the program arguments
/// @param arguments arguments saver structur
/// @param argv	program arguments
/// @param argc number of program arguments
void	get_args(t_args **arguments, char **argv, int argc, t_list **garbg);

/// @brief this function take commands from arguments
/// @param arguments arguments saver structur
/// @param argv program arguments
/// @param argc number of program arguments
/// @param garbg garbage collector linked list
void	get_commands(t_args **arguments, char **argv, int argc, t_list **garbg);

/// @brief this function check if commands valid
/// @param arguments arguments saver structur
/// @param garbg garbage collector linked list
/// @param cmdind indice of a command
/// @return command path
char	*check_commands(t_args **arguments, t_list **garbg, int cmdind);


/// @brief
/// @param arguments
/// @param garbage
/// @param pid_indice
/// @param envp
/// @return
int	child_process(t_args *arguments, t_list **garbg, int pid_indice, char **envp);

/// @brief
/// @param arguments
/// @param garbage
/// @param pid_indice
/// @param envp
/// @return
int	last_child_process(t_args *arguments, t_list **garbg, int pid_indice, char **envp);
int	first_child_process(t_args *arguments, t_list **garbg, int pid_indice, char **envp);
int	middle_childs_process(t_args *arguments, t_list **garbg, int pid_indice, char **envp);

#endif
