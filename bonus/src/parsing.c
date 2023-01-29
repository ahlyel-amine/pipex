/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/29 22:55:17 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_parse(t_list **garbg, t_args **args, char **envp)
{
	if (!envp)
		ft_exit("Invalid envirenment", garbg);
	(*args)->path = ft_split_garbg(env_path(envp, garbg), ':', garbg);
	if ((*args)->av[1] && !ft_memcmp((*args)->av[1], "here_doc", ft_strlen("here_doc")))
		get_here_doc(args, garbg);
	else
		get_args(args, garbg);
}

void	get_here_doc(t_args **args, t_list **garbg)
{
	char	*tmp;

	tmp = NULL;
	if ((*args)->ac != 6)
		ft_exit("Syntax Error, Expected : ./pipex here_doc LIMITER cmd cmd1 file", garbg);
	(*args)->outfile = open((*args)->av[(*args)->ac - 1], O_CREAT | O_TRUNC | O_RDWR, RDWR);
	(*args)->infile = open(".heredoc", O_CREAT | O_RDWR, RDWR);
	if ((*args)->outfile < 0 || (*args)->infile < 0)
		ft_exit("Error cannot open file", garbg);
	get_commands(args, garbg, 3);
	(*args)->limiter = ft_malloc(ft_strdup((*args)->av[2]), garbg);
	(*args)->limiter = ft_malloc(ft_strjoin((*args)->limiter, "\n"), garbg);
	while (1)
	{
		write(1, "pipe heredoc> ", ft_strlen("pipe heredoc> "));
		tmp = get_next_line(0, garbg);
		if(!tmp || (tmp && !ft_memcmp((*args)->limiter, tmp, ft_strlen((*args)->limiter))))
			break ;
		write((*args)->infile, tmp, ft_strlen(tmp));
		// ft_lstadd_back(&(*args)->heredoc, ft_malloc(ft_lstnew(tmp), garbg));
	}
}

void	get_args(t_args **args, t_list **garbg)
{
	if ((*args)->ac < 5)
		ft_exit("Syntax Error, Expected : ./pipex file1 cmd1 cmd2 ... cmdn file2", garbg);
	(*args)->infile = open((*args)->av[1], O_RDWR, RDWR);
	(*args)->outfile = open((*args)->av[(*args)->ac - 1], O_CREAT | O_TRUNC | O_RDWR, RDWR);
	if ((*args)->outfile < 0 || (*args)->infile < 0)
		ft_exit("Error cannot open file", garbg);
	get_commands(args, garbg, 2);
}

void	get_commands(t_args **args, t_list **garbg, int cmdind)
{
	char	*tmp;
	int		cmd;
	int		skip;

	tmp = NULL;
	cmd = 0;
	(*args)->cmds = ft_malloc(malloc(sizeof(char **) * (*args)->ac - cmdind), garbg);
	(*args)->cmds_path = \
		ft_malloc(malloc(sizeof(char *) * (*args)->ac - cmdind), garbg);
	(*args)->cmds[(*args)->ac - cmdind - 1] = NULL;
	(*args)->cmds_path[(*args)->ac - cmdind - 1] = NULL;
	while (cmdind < (*args)->ac - 1)
	{
		skip = 0;
		(*args)->cmds[cmd] = ft_split_garbg((*args)->av[cmdind], ' ', garbg);
		while ((*args)->cmds[cmd][0])
		{
			if ((*args)->cmds[cmd][0][skip] == '/')
				skip++;
			else if ((*args)->cmds[cmd][0][skip] == '.' && (*args)->cmds[cmd][0][skip + 1] == '/')
				skip++;
			else
				break ;
		}
		tmp = check_commands(args, garbg, cmd, skip);
		(*args)->cmds_path[cmd++] = ft_malloc(ft_strdup(tmp), garbg);
		cmdind++;
	}
}

char	*check_commands(t_args **args, t_list **garbg, int cmdind, int skip)
{
	char	*tmp;
	int		acs;
	int		j;

	j = 0;
	tmp = NULL;
	while ((*args)->path[j])
	{
		tmp = ft_malloc(ft_strjoin((*args)->path[j], "/"), garbg);
		tmp = ft_malloc(ft_strjoin(tmp, (*args)->cmds[cmdind][0] + skip), garbg);
		acs = access(tmp, F_OK);
		if (acs != -1)
			break ;
		j++;
	}
	if (acs == -1)
		ft_exit(ft_malloc(ft_strjoin("Error : Cannot find command ", (*args)->cmds[cmdind][0]), garbg), garbg);
	return (tmp);
}

char	*env_path(char **envp, t_list **garbg)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (ft_malloc(ft_substr(envp[i], 5,
						ft_strlen(envp[i] + 5)), garbg));
		i++;
	}
	return (ft_exit("Envirenment PATH NOT FOUND", garbg), NULL);
}
