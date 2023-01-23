/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 07:57:20 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/23 14:42:14 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_path(char *str)
{
	char	**path_all;
	char	**path_after_equal;

	path_all = ft_split(str, '=');
	if (!path_all)
		return (perror("Get path: "), NULL);
	path_after_equal = ft_split(path_all[1], ':');
	free_split(path_all);
	if (!path_after_equal)
		return (perror("Get path: "), NULL);
	return (path_after_equal);
}

char	**get_path(char **envp)
{
	int		i;

	i = 0;
	if (!envp[0])
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (perror("Get path: "), NULL);
	return (split_path(envp[i]));
}
