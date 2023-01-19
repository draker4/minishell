/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 07:57:20 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/17 15:54:05 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_path(char *str)
{
	char	**path;

	path = ft_split(str, '=');
	if (!path)
		return (perror("Get path: "), NULL);
	path = ft_split(path[1], ':');
	if (!path)
		return (perror("Get path: "), NULL);
	return (path);
}

char	**get_path(char **envp)
{
	int		i;
	char	*str;

	i = 0;
	if (!envp[0])
		return (NULL);
	str = ft_strdup("PATH");
	if (!str)
		return (perror("Get path: "), NULL);
	while (envp[i])
	{
		if (!ft_strncmp(str, envp[i], 4))
			break ;
		i++;
	}
	free(str);
	if (!envp[i])
		return (perror("Get path: "), NULL);
	return (split_path(envp[i]));
}
