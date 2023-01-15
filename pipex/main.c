/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:01:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/14 17:55:34 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

int main(int argc, char **argv, char **envp)
{
	t_args	*arguments;
	t_list	*garbg;
	int	i;
	int	fd[2][2];
	// fd = malloc(2 * sizeof(int *));
	i = 1;
	garbg = NULL;
	arguments = ft_malloc(malloc(sizeof(t_args)), &garbg);
	(*arguments).path = ft_split(env_path(envp, &garbg), ':', &garbg); //need impelement garbage collector in ft_split
	get_args(&arguments, argv, argc, &garbg);
	if (pipe(arguments->fd) == -1)
		ft_exit("Error function pipe failure", &garbg);
	(*arguments).pids = ft_malloc(malloc(sizeof(int) * argc - 2), &garbg);
	first_child_process(arguments, &garbg, 0, envp);
	printf("%d\n", waitpid((*arguments).pids[0], NULL, 0));
	while (i < argc - 4)
	{
		middle_childs_process(arguments, &garbg, i, envp);
		printf("%d\n", waitpid((*arguments).pids[i++], NULL, 0));
	}
	last_child_process(arguments, &garbg, i, envp);
	printf("%d\n", waitpid((*arguments).pids[i], NULL, 0));
	// close((*arguments).fd[0]);
	// close((*arguments).fd[1]);
			close(fd[1][0]);
		close(fd[0][0]);
		close(fd[1][0]);
		close(fd[1][1]);
	// while (j< argc - 3)
	// 	printf("%d\n", (*arguments).pids[j++]);
	ft_lstclear(&garbg, free);
	return 0;
}
