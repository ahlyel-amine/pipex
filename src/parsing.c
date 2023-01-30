/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/30 16:19:23 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_parse(t_list **garbg, t_args **args, char **envp)
{
	if ((*args)->ac != 5)
		ft_exit(ERRSNTX, garbg, 0);
	if (!envp)
		ft_exit(ERRENV, garbg, 0);
	(*args)->path = ft_split_garbg(env_path(envp, garbg), ':', garbg);
	get_args(args, garbg);
}

void	get_args(t_args **args, t_list **garbg)
{
	(*args)->infile = open((*args)->av[1], O_RDONLY, RDWR);
	(*args)->outfile = open((*args)->av[(*args)->ac - 1], O_CREAT | O_TRUNC | O_RDWR, RDWR);
	if ((*args)->outfile < 0 || (*args)->infile < 0)
		ft_exit(ERRFD, garbg, 0);
	get_commands(args, garbg);
}

void	get_commands(t_args **args, t_list **garbg)
{
	char	*tmp;
	int		i;
	int		skip;
	int		cmndind;

	cmndind = 0;
	i = 2;
	tmp = NULL;
	(*args)->cmds = ft_malloc(malloc(sizeof(char **) * (*args)->ac - i), garbg);
	(*args)->cmds_path = ft_malloc(malloc(sizeof(char *) * (*args)->ac - i), garbg);
	(*args)->cmds[(*args)->ac - i - 1] = NULL;
	(*args)->cmds_path[(*args)->ac - i - 1] = NULL;
	while (i < (*args)->ac - 1)
	{
		skip = 0;
		(*args)->cmds[cmndind] = ft_split_garbg((*args)->av[i], ' ', garbg);
		while ((*args)->cmds[cmndind][0])
		{
			if ((*args)->cmds[cmndind][0][skip] == '/')
				skip++;
			else if ((*args)->cmds[cmndind][0][skip] == '.' && (*args)->cmds[cmndind][0][skip + 1] == '/')
				skip++;
			else
				break ;
		}
		tmp = check_commands(args, garbg, cmndind, skip);
		(*args)->cmds_path[cmndind++] = ft_malloc(ft_strdup(tmp), garbg);
		i++;
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
		ft_exit(ft_malloc(ft_strjoin(ERRCMD, (*args)->cmds[cmdind][0]), garbg), garbg, 0);
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
	return (ft_exit(ERRPTH, garbg, 0), NULL);
}
