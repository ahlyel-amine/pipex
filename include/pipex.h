/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:20 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/04 20:55:33 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/include/libft.h"
# include <unistd.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <string.h>

/*						define error variables						*/
# define ERRENV "\e[1;91mpipex: Errror Invalid envirenment\e[0m"
# define ERRSNTX "\e[1;91mpipex: Syntax Error,\e[0m Expected : \
./pipex file1 cmd1 cmd2 file2"
# define ERRFD "\e[1;91mpipex: no such file or directory: "
# define ERRCMD "\e[1;91mpipex: command not found: "
# define ERRALLOC "\e[1;91mpipex: Cannot allocate memory\e[0m"
# define ERRPIPE "\e[1;91mpipex: Error pipe faillure\e[0m"
# define ERREXEC "\e[1;91mpipex: Error execve faillure\e[0m"
# define ERRWAIT "\e[1;91mpipex: Error waitpid faillure\e[0m"
# define ERRDUP2 "\e[1;91mpipex: Error dup2 faillure\e[0m"
/*----------------------------------------------------------------*/

/*		define variable 		*/
# define RDWR 0644
/*--------------------------------*/

typedef struct s_args
{
	int		ac;
	char	**av;
	char	**path;
	char	***cmds;
	char	**cmds_path;
	int		infile;
	int		is_infile;
	int		outfile;
	int		fd[2];
}	t_args;

/// @brief
/// @param s
/// @param c
/// @param garbg
/// @return
char	**ft_split_garbg(char const *s, char c, t_list **garbg);

/// @brief exit function in error cases
/// @param error_msg error message to write in stderr
/// @param garbg garbage collector linked list
void	ft_exit(char *error_msg, t_list **garbg, int exit_status);

/// @brief purpose of this function is to save all addresses being allocated
/// @param pointer pointer being allocated
/// @param garbg garbage collector linked list
/// @return pointer being allocated
void	*ft_malloc(void *pointer, t_list **garbg);

/// @brief get environment path
/// @param envp environment variables
/// @return environment path
char	*env_path(char **envp, t_list **garbg);

/// @brief this function translate/check/save the program args
/// @param args args saver structur
/// @param argv	program args
/// @param argc number of program args
void	get_args(t_args **args, t_list **garbg);

/// @brief this function take commands from args
/// @param args args saver structur
/// @param argv program args
/// @param argc number of program args
/// @param garbg garbage collector linked list
void	get_commands(t_args **args, t_list **garbg);

/// @brief this function check if commands valid
/// @param args args saver structur
/// @param garbg garbage collector linked list
/// @param cmdind indice of a command
/// @param skip 
/// @return command path
char	*check_commands(t_args **args, t_list **garbg, int cmdind, int skip);

/// @brief
/// @param garbg
/// @param args
/// @param envp
void	ft_parse(t_list **garbg, t_args **args, char **envp);

/// @brief
/// @param args
/// @param garbg
/// @param envp
/// @param i
void	exec_command(t_args *args, t_list **garbg, char **envp, int i);

/// @brief
/// @param garbg
/// @param args
/// @param ac
/// @param envp
void	ft_execute(t_list **garbg, t_args **args, char **envp);

/// @brief 
/// @param error_msg 
void	ft_set_err(char *error_msg);

#endif
