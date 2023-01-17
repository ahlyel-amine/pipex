/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:01:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/17 01:22:35 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

int main(int argc, char **argv, char **envp)
{
	t_args	*args;
	t_list	*garbg;
	int	i;
	// fd = malloc(2 * sizeof(int *));
	i = 1;
	garbg = NULL;
	args = ft_malloc(malloc(sizeof(t_args)), &garbg);
	(*args).path = ft_split_garbg(env_path(envp, &garbg), ':', &garbg);
	get_args(&args, argv, argc, &garbg);
	(*args).pids = ft_malloc(malloc(sizeof(int) * argc - 2), &garbg);
	if (pipe((*args).fd) == -1)
		ft_exit("Error function pipe failure", &garbg);
	first_child_process(args, &garbg, 0, envp);
	// printf("%d\n", waitpid((*args).pids[0], NULL, 0));
	// 	char *v;
	// v = malloc(4000);
	// read((*args).fd[1], v, 4000);
	// write(STDOUT_FILENO, v, 4000);
	while (i++ < argc - 4)
	// {
		middle_childs_process(args, &garbg, i, envp);
		// printf("%d\n", waitpid((*args).pids[i++], NULL, 0));
	// }
	last_child_process(args, &garbg, i, envp);
	// printf("pid:%d\n", waitpid((*args).pids[i], NULL, 0));
	// close((*args).fd[0]);
	// close((*args).fd[1]);
	// while (j< argc - 3)
	// 	printf("%d\n", (*args).pids[j++]);
	ft_lstclear(&garbg, free);
	return 0;
}
