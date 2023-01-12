/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foramtter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/12 17:18:12 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

void	get_args(t_args **arguments, char **argv, int argc, t_list **garbg)
{
	if (argc < 5)
		ft_exit("Syntax Error, Expected : ./pipex file1 cmd1 cmd2 file2",
			garbg);
	(*arguments)->infile = open(argv[1],
			O_CREAT | O_TRUNC/* | O_NONBLOCK*/ | O_RDWR, RDWR);
	(*arguments)->outfile = open(argv[argc - 1],
			O_CREAT | O_TRUNC/* | O_NONBLOCK*/ | O_RDWR, RDWR);
	if ((*arguments)->outfile < 0 || (*arguments)->infile < 0)
		ft_exit("Error cannot open file", garbg);
	get_commands(arguments, argc, argv, garbg);
}

void	get_commands(t_args **arguments, char **argv, int argc, t_list **garbg)
{
	char	*tmp;
	int		i;
	int		k;
	int		j;

	j = 0;
	k = 0;
	i = 2;
	(*arguments).cmds = ft_malloc(malloc(sizeof(char **) * argc - i));
	*((*arguments).cmds + argc - i) = NULL;
	while (i < argc - 1)
	{
		*((*arguments).cmds + k++) = ft_malloc(ft_split(argv[i], ' '), garbg);
		while (*((*arguments).path + j))
		{
			tmp = ft_malloc(ft_strjoin(*((*arguments).path + j), "/");
			access(ft_malloc(tmp, ), F_OK)
		}
	}
}
