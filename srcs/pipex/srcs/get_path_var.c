/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 07:57:20 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/17 11:38:16 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**split_path(char *str)
{
	char	**path;

	path = ft_split(str, '=');
	if (!path)
	{
		write(2, "Malloc function error!\n", 23);
		return (NULL);
	}
	path = ft_split(path[1], ':');
	if (!path)
	{
		write(2, "Malloc function error!\n", 23);
		return (NULL);
	}
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
	{
		write(2, "Malloc function error!\n", 23);
		return (NULL);
	}
	while (envp[i])
	{
		if (!ft_strncmp(str, envp[i], 4))
			break ;
		i++;
	}
	free(str);
	if (!envp[i])
	{
		write(2, "Error: Could not find PATH!\n", 28);
		return (NULL);
	}
	return (split_path(envp[i]));
}
