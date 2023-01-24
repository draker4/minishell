/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:20:47 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 13:59:17 by bperriol         ###   ########lyon.fr   */
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

void	copy_env(char **envp, t_data *data)
{
	int		i;
	t_env	*new;
	char	**split;

	i = 0;
	while (envp[i])
	{
		split = split_var(envp[i]);
		if (!split)
			return (perror("Copy_env - Malloc"), \
			env_clear_data(&data->env), NULL);
		if (split[0] && split[1])
			new = new_env(split[0], split[1], 1);
		else
			new = new_env(split[0], NULL, 0);
		if (!new)
		{
			free_split(split);
			perror("Copy_env - Malloc");
			env_clear_data(&data->env);
		}
		env_add_back(&data->env, new);
	}
}
