/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/05 05:28:50 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_parse(t_list **garbg, t_args **args, char **envp)
{
	if (!envp)
		ft_exit(ERRENV, garbg, 1);
	(*args)->path = ft_split_garbg(env_path(envp, garbg), ':', garbg);
	if ((*args)->av[1] && !ft_memcmp((*args)->av[1], HEREDOC, 8))
		get_here_doc(args, garbg);
	else
		get_args(args, garbg);
}

void	get_here_doc(t_args **args, t_list **garbg)
{
	char	*tmp;

	tmp = NULL;
	if ((*args)->ac != 6)
		ft_exit(ERR_HEREDOC_SNTX, garbg, 1);
	(*args)->outfile = open((*args)->av[(*args)->ac - 1], O_CREAT | O_APPEND | O_RDWR, RDWR);
	(*args)->infile = open(HRDCFILE, O_CREAT | O_TRUNC | O_RDWR, RDWR);
	if ((*args)->outfile < 0 || (*args)->infile < 0)
		ft_exit(ERRFD, garbg, 1);
	(*args)->limiter = ft_malloc(ft_strjoin((*args)->av[2], "\n"), garbg);
	while (1)
	{
		write(1, HRDCCMD, 14);
		tmp = get_next_line(0, garbg);
		if(!tmp || (tmp && !ft_memcmp((*args)->limiter, tmp, ft_strlen((*args)->limiter))))
			break ;
		if (write((*args)->infile, tmp, ft_strlen(tmp)) == -1)
			ft_exit(ERRWR, garbg, 1);
	}
	close((*args)->infile);
	(*args)->infile = open(HRDCFILE, O_RDWR, RDWR);
	get_commands(args, garbg, 3);
}

void	get_args(t_args **args, t_list **garbg)
{
	if ((*args)->ac < 5)
		ft_exit(ERRSNTX, garbg, 1);
	(*args)->infile = open((*args)->av[1], O_RDWR, RDWR);
	if ((*args)->infile < 0)
		ft_set_err(ft_malloc(ft_strjoin(ERRFD, (*args)->av[1]), garbg));
	(*args)->outfile = open((*args)->av[(*args)->ac - 1], O_CREAT | O_TRUNC | O_RDWR, RDWR);
	if ((*args)->outfile < 0)
		ft_exit(ERRFD, garbg, 1);
	get_commands(args, garbg, 2);
}

void	get_commands(t_args **args, t_list **garbg, int cmdind)
{
	char	*tmp;
	int		cmd;
	int		skip;
	int		count;

	tmp = NULL;
	cmd = 0;
	(*args)->cmds = ft_malloc(malloc(sizeof(char **) * (*args)->ac - cmdind), garbg);
	(*args)->cmds_path = \
		ft_malloc(malloc(sizeof(char *) * (*args)->ac - cmdind), garbg);
	(*args)->cmds[(*args)->ac - cmdind - 1] = NULL;
	(*args)->cmds_path[(*args)->ac - cmdind - 1] = NULL;
	while (cmdind < (*args)->ac - 1)
	{
		count = 0;
		skip = 0;
		(*args)->cmds[cmd] = ft_split_garbg((*args)->av[cmdind], ' ', garbg);
		while ((*args)->cmds[cmd][0][count++])
			if ((*args)->cmds[cmd][0][count++] == '/')
				skip++;
		tmp = check_commands(args, garbg, cmd, skip);
		if (tmp)
			(*args)->cmds_path[cmd++] = ft_malloc(ft_strdup(tmp), garbg);
		else
			(*args)->cmds_path[cmd++] = NULL;
		cmdind++;
	}
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
	return (NULL);
}
