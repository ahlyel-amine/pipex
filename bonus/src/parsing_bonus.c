/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:24:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/07 00:45:17 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	ft_parse(t_list **garbg, t_args **args, char **envp)
{
	if (!envp)
		ft_exit(ERRENV, garbg, 1);
	(*args)->path = ft_split_garbg(env_path(envp, garbg), ':', garbg);
	if ((*args)->av[1] && !ft_memcmp((*args)->av[1], HEREDOC, 8))
		get_here_doc(args, garbg);
	else
		get_args(args, garbg);
}

void	get_here_doc(t_args **args, t_list **garbg)
{
	char	*tmp;
	int		fd_perm;
	int		fd_flag_herdoc;

	tmp = NULL;
	fd_perm = S_IWUSR | S_IRUSR;
	fd_flag_herdoc = O_CREAT | O_APPEND | O_RDWR;
	if ((*args)->ac != 6)
		ft_exit(ERR_HEREDOC_SNTX, garbg, 1);
	(*args)->outfile = faillure(garbg, \
	open((*args)->av[(*args)->ac - 1], fd_flag_herdoc, fd_perm), ERRFD);
	faillure(garbg, pipe((*args)->fd), ERRPIPE);
	(*args)->infile = (*args)->fd[0];
	(*args)->limiter = ft_malloc(ft_strjoin((*args)->av[2], "\n"), garbg);
	while (1337)
	{
		faillure(garbg, write(1, HRDCCMD, 14), ERRWR);
		tmp = get_next_line(0, garbg);
		if (!tmp || \
		(tmp && !ft_memcmp((*args)->limiter, tmp, ft_strlen((*args)->limiter))))
			break ;
		faillure(garbg, write((*args)->fd[1], tmp, ft_strlen(tmp)), ERRWR);
	}
	faillure(garbg, close((*args)->fd[1]), ERRCLOSE);
	get_commands(args, garbg, 3);
}

void	get_args(t_args **args, t_list **garbg)
{
	int	fd_perm;
	int	fd_flag_out;

	fd_perm = S_IWUSR | S_IRUSR;
	fd_flag_out = O_CREAT | O_TRUNC | O_RDWR;
	if ((*args)->ac < 5)
		ft_exit(ERRSNTX, garbg, 1);
	(*args)->infile = open((*args)->av[1], O_RDWR, ERRFD);
	if ((*args)->infile < 0)
		ft_set_err(ft_malloc(ft_strjoin(ERRFD, (*args)->av[1]), garbg));
	(*args)->outfile = faillure(garbg, \
	open((*args)->av[(*args)->ac - 1], fd_flag_out, fd_perm), ERRFD);
	get_commands(args, garbg, 2);
}

void	get_commands(t_args **args, t_list **garbg, int cmdind)
{
	char	*tmp;
	int		cmd;
	int		skip;
	int		count;

	tmp = NULL;
	cmd = 0;
	(*args)->cmds = ft_malloc(\
	malloc(sizeof(char **) * (*args)->ac - cmdind), garbg);
	(*args)->cmds_path = \
		ft_malloc(malloc(sizeof(char *) * (*args)->ac - cmdind), garbg);
	(*args)->cmds[(*args)->ac - cmdind - 1] = NULL;
	(*args)->cmds_path[(*args)->ac - cmdind - 1] = NULL;
	while (cmdind < (*args)->ac - 1)
	{
		count = -1;
		(*args)->cmds[cmd] = ft_split_garbg((*args)->av[cmdind], ' ', garbg);
		skip = check_is_path(garbg, *args, cmd);
		tmp = check_commands(args, garbg, cmd, skip);
		if (tmp)
			(*args)->cmds_path[cmd++] = ft_malloc(ft_strdup(tmp), garbg);
		else
			(*args)->cmds_path[cmd++] = NULL;
		cmdind++;
	}
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
	return (NULL);
}
