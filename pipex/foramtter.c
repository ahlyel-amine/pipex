/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foramtter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/12 19:26:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

void	get_args(t_args **arguments, char **argv, int argc, t_list **garbg)
{
	if (argc < 5)
		ft_exit("Syntax Error, Expected :\
			./pipex file1 cmd1 cmd2 ... cmdn file2", garbg);
	(*arguments)->infile = open(argv[1],
			O_CREAT | O_TRUNC/* | O_NONBLOCK*/ | O_RDWR, RDWR);
	(*arguments)->outfile = open(argv[argc - 1],
			O_CREAT | O_TRUNC/* | O_NONBLOCK*/ | O_RDWR, RDWR);
	if ((*arguments)->outfile < 0 || (*arguments)->infile < 0)
		ft_exit("Error cannot open file", garbg);
	get_commands(arguments, argv, argc, garbg);
}

void	get_commands(t_args **arguments, char **argv, int argc, t_list **garbg)
{
	char	*tmp;
	int		acs;
	int		i;
	int		k;

	tmp = NULL;
	k = 0;
	i = 2;
	(*arguments)->cmds = ft_malloc(malloc(sizeof(char **) * argc - i), garbg);
	(*arguments)->cmds_path = \
		ft_malloc(malloc(sizeof(char *) * argc - i), garbg);
	*((*arguments)->cmds + argc - i - 1) = NULL;
	*((*arguments)->cmds_path + argc - i - 1) = NULL;
	while (i < argc - 1)
	{
		*((*arguments)->cmds + k) = ft_malloc(ft_split(argv[i], ' '), garbg);
		tmp = check_commands(arguments, garbg, k);
		(*arguments)->cmds_path[k++] = ft_malloc(ft_strdup(tmp), garbg);
		i++;
	}
}

char	*check_commands(t_args **arguments, t_list **garbg, int cmdind)
{
	char	*tmp;
	int		acs;
	int		j;

	j = 0;
	tmp = NULL;
	while (*((*arguments)->path + j))
	{
		tmp = ft_malloc(ft_strjoin(*((*arguments)->path + j), "/"), garbg);
		tmp = ft_malloc(ft_strjoin(tmp,
					*(*((*arguments)->cmds + cmdind))), garbg);
		acs = access(tmp, F_OK);
		if (acs != -1)
			break ;
		j++;
	}
	if (acs == -1)
		ft_exit("Error : command not found", garbg);
	return (tmp);
}

char	*env_path(char **envp)
{
	int	i;

	i = 0;
	while (*(envp + i))
	{
		if (ft_strnstr(*(envp + i), "PATH=", 5))
			return (ft_substr(*(envp + i), 5,
					ft_strlen((*(envp + i)) + 5)));
		i++;
	}
	return (NULL);
}
