/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:01:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/01/12 17:04:07 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"
#include "headers/libft.h"

char	*env(char **envp)
{
	int     i;

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

int main(int argc, char **argv, char **envp)
{
	t_args	*arguments;
	t_list	*garbg;

	garbg = NULL;
	arguments = ft_malloc(malloc(sizeof(t_args)), &garbg);
	(*arguments).path = ft_malloc(ft_split(env(envp), ':'), &garbg); //need impelement garbage collector in ft_split
	get_args(&arguments, argv, argc, &garbg);
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
