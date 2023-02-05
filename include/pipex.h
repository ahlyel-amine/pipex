/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:20 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/05 05:57:13 by aahlyel          ###   ########.fr       */
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
# define ERROPEN "\e[1;91mpipex: Error open faillure\e[0m"
# define ERRCLOSE "\e[1;91mpipex: Error close faillure\e[0m"
# define ERRDUP2 "\e[1;91mpipex: Error dup2 faillure\e[0m"
# define ERRFRK "\e[1;91mpipex: Error fork faillure\e[0m"
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
/// @param s	string to split
/// @param c	separater
/// @param garbg	garbg collecter
/// @return
char	**ft_split_garbg(char const *s, char c, t_list **garbg);

/// @brief exit function in error cases
/// @param error_msg error message to write in stderr
/// @param garbg garbage collector linked list
/// @param exit_status exit status (Faillure/Success)
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
void	get_args(t_args **args, t_list **garbg);

/// @brief this function take commands from args
/// @param args args saver structur
/// @param garbg garbage collector linked list
void	get_commands(t_args **args, t_list **garbg);

/// @brief this function check if commands valid
/// @param args args saver structur
/// @param garbg garbage collector linked list
/// @param cmdind indice of a command
/// @param skip (comand is a path) if true otherwise false
/// @return command path
char	*check_commands(t_args **args, t_list **garbg, int cmdind, int skip);

/// @brief	parsing controller
/// @param garbg	garbg collecter 
/// @param args		arguments
/// @param envp		envp
void	ft_parse(t_list **garbg, t_args **args, char **envp);

/// @brief
/// @param args		arguments
/// @param garbg	garbg collecter 
/// @param envp	envp
void	exec_command(t_args *args, t_list **garbg, char **envp);

/// @brief	execute commands
/// @param garbg	garbg collecter 
/// @param args	args (commands/ commands path)
/// @param envp	envp
void	ft_execute(t_list **garbg, t_args **args, char **envp);

/// @brief print an error without exiting from program
/// @param error_msg error message
void	ft_set_err(char *error_msg);

/// @brief 	check if any functions fail
/// @param garbg	garbg collector
/// @param return_value	functions return  
/// @param exit_message error message in case of faillure
/// @return functions return  (return_value)
int		function_faillure(t_list **garbg, int return_value, char *exit_message);

/// @brief a helper function to cotroll wich error message to print
/// @param garbg 	garbg collector
/// @param args 	arguments
/// @param cmdind 	command indice
/// @param skip 	(comand is a path) if true otherwise false
/// @return 	
int		print_err(t_list **garbg, t_args **args, int cmdind, int skip);

#endif
