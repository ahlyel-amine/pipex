/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:01:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/12 21:23:48 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

int main(int argc, char **argv, char **envp)
{
	t_args	*arguments;
	t_list	*garbg;
	int	i;

	i = 0;
	garbg = NULL;
	arguments = ft_malloc(malloc(sizeof(t_args)), &garbg);
	(*arguments).path = ft_malloc(ft_split(env_path(envp), ':'), &garbg); //need impelement garbage collector in ft_split
	get_args(&arguments, argv, argc, &garbg);
	if (pipe(arguments->fd) == -1)
		ft_exit("Error function pipe failure", &garbg);
	(*arguments).pids = ft_malloc(malloc(sizeof(int) * argc - 2));
	(*arguments).pids[argc - 3] = NULL;
	while (i++ < argc - 2)
	{
		if (child_process(arguments, &garbage, i, envp))
	}
	// int i =0, j = 0, k = 0;
	// while (*((*arguments).cmds_path + k))
	// {
	// 	printf("%s\n", *((*arguments).cmds_path + k++));
	// }
	// while (((*arguments).cmds)[i])
	// {
	// 	j = 0;
	// 	while (((*arguments).cmds)[i][j])
	// 	{
	// 		printf("%s\n", ((*arguments).cmds)[i][j++]);
	// 	}
	// 	i++;
	// }
	// char **ls;
	// ls = malloc(3 * sizeof(char *));
	// *ls = malloc(3);
	// *(ls + 1) = malloc(5);
	// ft_memcpy(*ls, "ls\0", 3);
	// ft_memcpy(*(ls + 1), "-lha\0", 5);
	// *(ls + 2) = NULL;
	// int i = -999;
	// i = execve("/bin/ls", ls, envp);
	return 0;
}
