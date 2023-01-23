/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/23 14:20:25 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*split_home(char *str)
{
	char	**home;

	home = ft_split(str, '=');
	if (!home)
		return (perror("Get path: "), NULL);
	if (size_arg(home) != 2)
		return (perror("Get path: "), NULL);
	return (home[1]);
}

char	*get_home(char **envp)
{
	int		i;

	i = 0;
	if (!envp[0])
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp("HOME=", envp[i], 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (perror("Get_home: "), NULL);
	return (split_home(envp[i]));
}

void	ft_cd(t_exec *exec)
{
	char	*home;

	if (size_arg(exec->arg) == 1)
	{
		home = get_home(exec->data->envp);
		if (!home)
		{
			if (!exec->pid)
				exit(1);
		}
		if (chdir(home))
		{
			perror("Ft_cd");
			if (!exec->pid)
				exit(1);
		}
	}
	else if (chdir(exec->arg[1]))
	{
		perror("Ft_cd");
		if (!exec->pid)
			exit(1);
	}
	if (!exec->pid)
		exit(0);
}
