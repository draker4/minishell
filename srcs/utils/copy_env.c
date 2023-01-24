/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:20:47 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/23 19:50:35 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_shlvl(t_data *data)
{
	if (getenv("SHLVL"))
	{
		if (!shlvl_plus_one(data->envp))
			return (0);
	}
	else
	{
		data->envp = add_shlvl(data->envp);
		if (!data->envp)
			return (0);
	}
	return (1);
}

int	which_env_add(t_data *data)
{
	if (!getenv("PWD"))
	{
		data->envp = add_pwd(data->envp);
		if (!data->envp)
			return (0);
	}
	if (!getenv("_"))
	{
		data->envp = add_last_cmd(data->envp);
		if (!data->envp)
			return (0);
	}
	if (!getenv("OLDPWD"))
	{
		data->envp = add_oldpwd(data->envp);
		if (!data->envp)
			return (0);
	}
	return (1);
}

char	**copy_env(char **envp)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (size_arg(envp) + 1));
	if (!copy)
		return (perror("Copy_env - Malloc"), NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
