/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:01:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/26 19:52:42 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

int	main(int ac, char **av, char **envp)
{
	t_args	*args;
	t_list	*garbg;

	garbg = NULL;
	args = ft_malloc(malloc(sizeof(t_args)), &garbg);
	args->ac = ac;
	args->av = av;
	ft_parse(&garbg, &args, envp);
	args->fd = ft_malloc(malloc(sizeof(int[2]) * ac - 3), &garbg);
	args->pids = ft_malloc(malloc(sizeof(int) * ac - 3), &garbg);
	int	i = 0;
	while (i < ac - 3)
		if (pipe(*(args->fd + i++)) < 0)
			ft_exit("yo", &garbg);
	i = 0;
	while (i < ac - 3)
	{

		// *(args->pids + i) = fork();
		if (i != ac  - 4)
			first_child_process(args, &garbg, envp, i);
		else
		{
			// *(args->pids + i) = fork();
			dup2(args->outfile, STDOUT_FILENO);
			execve(args->cmds_path[i], args->cmds[i], envp);
		}
		// if (*(args->pids + i) == 0)
		// {
			// if (!i)
			// 	first_child_process()
			// {
			// 	// close(args->fd[i][0]);
			// 	//command 1
			// 	dup2(args->fd[i][1], 1);
			// }
			// if (!i || i != ac - 3)
			// {
			// 	first_child_process()

			// 	// dup2(args->fd[1], STDOUT_FILENO);
			// 	// close(args->fd[1]);
			// 	// close(args->fd[2]);
			// }
			// 	// middle_childs_process();
			// // {

			// // 	dup2(args->fd[i + 1][0], 0);
			// // }
			// else if (i == ac - 3)
			// 	dup2((*args).outfile, STDOUT_FILENO);
			// 	// dup2(args->fd[i + 1][1], args->outfile);
			// // close(1);
			// close(args->fd[i][0]);
			// close(args->fd[i][1]);
		// }
		i++;
	}
	// while (*args->path)
	// 	printf("%s\n", *args->path++);
	// int  j = 0;
	// while (args->cmds[i])
	// {
	// 	j = 0;
	// 	while (args->cmds[i][j])
	// 		printf("%s ", args->cmds[i][j++]);
	// 	printf(": %s\n", args->cmds_path[i]);
	// 	i++;
	// }
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_args	*args;
// 	t_list	*garbg;
// 	int		i;
// 	// fd = malloc(2 * sizeof(int *));
// 	i = 1;
// 	garbg = NULL;
// 	args = ft_malloc(malloc(sizeof(t_args)), &garbg);

// 	(*args).path = ft_split_garbg(env_path(envp, &garbg), ':', &garbg);
// 	get_args(&args, argv, argc, &garbg);
// 	(*args).pids = ft_malloc(malloc(sizeof(int) * argc - 2), &garbg);
// 	if (pipe((*args).fd) == -1)
// 		ft_exit("Error function pipe failure", &garbg);
// 	first_child_process(args, &garbg, 0, envp);
// 	// printf("%d\n", waitpid((*args).pids[0], NULL, 0));
// 	// 	char *v;
// 	// v = malloc(4000);
// 	// read((*args).fd[1], v, 4000);
// 	// write(STDOUT_FILENO, v, 4000);
// 	while (i++ < argc - 4)
// 	// {
// 		middle_childs_process(args, &garbg, i, envp);
// 		// printf("%d\n", waitpid((*args).pids[i++], NULL, 0));
// 	// }
// 	last_child_process(args, &garbg, i, envp);
// 	// printf("pid:%d\n", waitpid((*args).pids[i], NULL, 0));
// 	// close((*args).fd[0]);
// 	// close((*args).fd[1]);
// 	// while (j< argc - 3)
// 	// 	printf("%d\n", (*args).pids[j++]);
// 	ft_lstclear(&garbg, free);
// 	return 0;
// }
