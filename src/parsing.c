/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/06 22:58:15 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_parse(t_list **garbg, t_args **args, char **envp)
{
	if ((*args)->ac != 5)
		ft_exit(ERRSNTX, garbg, 1);
	if (!envp)
		ft_exit(ERRENV, garbg, 1);
	(*args)->path = ft_split_garbg(env_path(envp, garbg), ':', garbg);
	get_args(args, garbg);
}

void	get_args(t_args **args, t_list **garbg)
{
	int	fd_perm;
	int	fd_flag_out;

	fd_perm = S_IWUSR | S_IRUSR;
	fd_flag_out = O_CREAT | O_TRUNC | O_RDWR;
	(*args)->infile = open((*args)->av[1], O_RDONLY, fd_perm);
	if ((*args)->infile < 0)
		ft_set_err(ft_malloc(ft_strjoin(ERRFD, (*args)->av[1]), garbg));
	(*args)->outfile = function_faillure(garbg, \
	open((*args)->av[(*args)->ac - 1], fd_flag_out, fd_perm), ERROPEN);
	get_commands(args, garbg);
}

void	init_commands(t_args **args, t_list **garbg)
{
	(*args)->cmds = ft_malloc(\
	malloc(sizeof(char **) * ((*args)->ac - 2)), garbg);
	(*args)->cmds_path = ft_malloc(\
	malloc(sizeof(char *) * ((*args)->ac - 2)), garbg);
	(*args)->cmds[(*args)->ac - 3] = NULL;
	(*args)->cmds_path[(*args)->ac - 3] = NULL;
}

void	get_commands(t_args **args, t_list **garbg)
{
	char	*tmp;
	int		i;
	int		count;
	int		skip;
	int		cmndind;

	cmndind = 0;
	i = 2;
	tmp = NULL;
	init_commands(args, garbg);
	while (i < (*args)->ac - 1)
	{
		skip = 0;
		count = -1;
		(*args)->cmds[cmndind] = ft_split_garbg((*args)->av[i], ' ', garbg);
		if (!(*args)->cmds[cmndind][0])
			ft_exit(ERRSNTX, garbg, 1);
		while ((*args)->cmds[cmndind][0][++count])
			if ((*args)->cmds[cmndind][0][count] == '/')
				skip++;
		tmp = check_commands(args, garbg, cmndind, skip);
		if (tmp)
			(*args)->cmds_path[cmndind++] = ft_malloc(ft_strdup(tmp), garbg);
		else
			(*args)->cmds_path[cmndind++] = NULL;
		i++;
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
