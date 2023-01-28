/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/28 18:33:43 by aahlyel          ###   ########.fr       */
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
	if ((*args)->ac != 6)
		ft_exit("Syntax Error, Expected : ./pipex here_doc LIMITER cmd cmd1 file", garbg);
	(*args)->outfile = open((*args)->av[(*args)->ac - 1], O_CREAT | O_TRUNC | O_RDWR, RDWR);
	if ((*args)->outfile < 0)
		ft_exit("Error cannot open file", garbg);
	get_commands(args, garbg, 3);
	
}

void	get_args(t_args **args, t_list **garbg)
{
	if ((*args)->ac < 5)
		ft_exit("Syntax Error, Expected : ./pipex file1 cmd1 cmd2 ... cmdn file2", garbg);
	(*args)->infile = open((*args)->av[1], O_TRUNC | O_RDWR, RDWR);
	(*args)->outfile = open((*args)->av[(*args)->ac - 1], O_CREAT | O_TRUNC | O_RDWR, RDWR);
	if ((*args)->outfile < 0 || (*args)->infile < 0)
		ft_exit("Error cannot open file", garbg);
	get_commands(args, garbg, 2);
}

void	get_commands(t_args **args, t_list **garbg, int cmdind)
{
	char	*tmp;
	int		k;

	tmp = NULL;
	k = 0;
	(*args)->cmds = ft_malloc(malloc(sizeof(char **) * (*args)->ac - cmdind), garbg);
	(*args)->cmds_path = \
		ft_malloc(malloc(sizeof(char *) * (*args)->ac - cmdind), garbg);
	(*args)->cmds[(*args)->ac - cmdind - 1] = NULL;
	(*args)->cmds_path[(*args)->ac - cmdind - 1] = NULL;
	while (cmdind < (*args)->ac - 1)
	{
		(*args)->cmds[k] = ft_split_garbg((*args)->av[cmdind], ' ', garbg);
		tmp = check_commands(args, garbg, k);
		(*args)->cmds_path[k++] = ft_malloc(ft_strdup(tmp), garbg);
		cmdind++;
	}
}

char	*check_commands(t_args **args, t_list **garbg, int cmdind)
{
	char	*tmp;
	int		acs;
	int		j;

	j = 0;
	tmp = NULL;
	while ((*args)->path[j])
	{
		tmp = ft_malloc(ft_strjoin((*args)->path[j], "/"), garbg);
		tmp = ft_malloc(ft_strjoin(tmp, (*args)->cmds[cmdind][0]), garbg);
		acs = access(tmp, F_OK);
		if (acs != -1)
			break ;
		j++;
	}
	if (acs == -1)
	{
		ft_exit(ft_malloc(ft_strjoin("Error : Cannot find command ", \
		(*args)->cmds[cmdind][0]), garbg), garbg);
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
	return (ft_exit("Envirenment PATH NOT FOUND", garbg), NULL);
}
