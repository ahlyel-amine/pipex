/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/04 21:36:19 by aahlyel          ###   ########.fr       */
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
	(*args)->infile = open((*args)->av[1], O_RDONLY, RDWR);
	if ((*args)->infile < 0)
		ft_set_err(ft_malloc(ft_strjoin(ERRFD, (*args)->av[1]), garbg));
	(*args)->outfile = function_faillure(garbg, open((*args)->av[(*args)->ac - 1], O_CREAT | O_TRUNC | O_RDWR, RDWR), ERROPEN);
	get_commands(args, garbg);
	if (!(*args)->cmds_path)
		ft_exit(NULL, garbg, 0);
}

void	get_commands(t_args **args, t_list **garbg)
{
	char	*tmp;
	int		i;
	int		count;
	int		skip;
	int		cmndind;

	cmndind = 0;
	count = 0;
	i = 2;
	tmp = NULL;
	(*args)->cmds = ft_malloc(malloc(sizeof(char **) * (*args)->ac - i), garbg);
	(*args)->cmds_path = ft_malloc(malloc(sizeof(char *) * (*args)->ac - i), garbg);
	(*args)->cmds[(*args)->ac - i - 1] = NULL;
	(*args)->cmds_path[(*args)->ac - i - 1] = NULL;
	while (i < (*args)->ac - 1)
	{
		skip = 0;
		count = 0;
		(*args)->cmds[cmndind] = ft_split_garbg((*args)->av[i], ' ', garbg);
		while ((*args)->cmds[cmndind][0][count])
			if ((*args)->cmds[cmndind][0][count++] == '/')
				skip++;
		tmp = check_commands(args, garbg, cmndind, skip);
		if ((*args)->cmds_path && tmp)
			(*args)->cmds_path[cmndind++] = ft_malloc(ft_strdup(tmp), garbg);
		else
			(*args)->cmds_path = NULL;
		i++;
	}
}

char	*check_commands(t_args **args, t_list **garbg, int cmdind, int skip)
{
	char	*tmp;
	int		acs;
	int		j;

	j = 0;
	acs = -1;
	tmp = NULL;
	while ((*args)->path && (*args)->path[j])
	{
		acs = access((*args)->cmds[cmdind][0], F_OK);
		if (acs != -1)
			return ((*args)->cmds[cmdind][0]);
		if (skip)
			break ;
		tmp = ft_malloc(ft_strjoin((*args)->path[j], "/"), garbg);
		tmp = ft_malloc(ft_strjoin(tmp, (*args)->cmds[cmdind][0]), garbg);
		acs = access(tmp, F_OK);
		if (acs != -1)
			return (tmp);
		j++;
	}
	if (acs == -1 && skip)
	{
		ft_set_err(ft_malloc(ft_strjoin(ERRFD, (*args)->cmds[cmdind][0]), garbg));
		tmp = NULL;
	}
	else if (acs == -1 && !skip)
	{
		ft_set_err(ft_malloc(ft_strjoin(ERRCMD, (*args)->cmds[cmdind][0]), garbg));
		tmp = NULL;
	}
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
	return (NULL);
}
