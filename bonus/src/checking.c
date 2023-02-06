/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 04:59:41 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/06 05:39:33 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	print_err(t_list **garbg, t_args **args, int cmdind, int skip)
{
	if (!cmdind && (*args)->infile < 0)
		return (0);
	else if (skip)
		return (ft_set_err(ft_malloc(\
		ft_strjoin(ERRFD, (*args)->cmds[cmdind][0]), garbg)), 0);
	else if (!skip)
		return (ft_set_err(ft_malloc(\
		ft_strjoin(ERRCMD, (*args)->cmds[cmdind][0]), garbg)), 0);
	return (0);
}

int	check_is_path(t_args *args, int cmd)
{
	int	count;
	int	skip;

	count = -1;
	skip = 0;
	while (args->cmds[cmd][0][++count])
		if (args->cmds[cmd][0][count] == '/')
			skip++;
	return (skip);
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
	if (acs == -1 && !print_err(garbg, args, cmdind, skip))
		return (NULL);
	return (tmp);
}
