/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:20 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/05 05:39:55 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/get_next_line/include/get_next_line.h"
# include "../lib/libft/include/libft.h"
# include <unistd.h>
# include <sys/errno.h>
# include <fcntl.h>

/*		define error messages		*/
# define ERRENV "pipex: Invalid envirenment"
# define ERRSNTX "pipex: Syntax Error Expected \
: ./pipex file1 cmd1 cmd2 ... cmdn file2"
# define ERR_HEREDOC_SNTX "pipex: Syntax Error \
Expected : ./pipex here_doc LIMITER cmd cmd1 file"
# define ERRFD "pipex: no such file or directory: "
# define ERRCMD "pipex: command not found: "
# define ERRALLOC "pipex: Cannot allocate memory"
# define ERRPIPE "pipex: Error pipe faillure"
# define ERREXEC "pipex: Error execve faillure"
# define ERRCLOSE "ipex: Error close faillure"
# define ERRWAIT "pipex: Error waitpid faillure"
# define ERRDUP2 "pipex: Error dup2 faillure"
# define ERREAD "pipex: Error Read faillure"
# define ERRWR "pipex: Error Write faillure"
/*--------------------------------*/
/*		define variable 		*/
# define RDWR 0644
# define HRDCCMD "pipe heredoc> "
# define HEREDOC "here_doc"
# define HRDCFILE ".heredoc"
/*--------------------------------*/

typedef struct s_args
{
	int		ac;
	char	**av;
	char	**path;
	char	***cmds;
	char	**cmds_path;
	char	*limiter;
	int		infile;
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
void	ft_exit(char *error_msg, t_list **garbg, int status);

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
void	get_commands(t_args **args, t_list **garbg, int cmdind);

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

void	get_here_doc(t_args **args, t_list **garbg);
void	ft_execute_heredoc(t_list **garbg, t_args **args, char **envp);
void	ft_set_err(char *error_msg);
int	faillure(t_list **garbg, int return_value, char *exit_message);
int	adprint_err(t_list **garbg, t_args **args, int cmdind, int skip);

#endif
