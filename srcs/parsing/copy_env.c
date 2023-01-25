/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:20:47 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 18:34:14 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_shlvl(t_data *data)
{
	if (in_env(data->env, "SHLVL"))
	{
		if (!shlvl_plus_one(&data->env))
			return (0);
	}
	else
	{
		if (!add_shlvl(&data->env))
			return (0);
	}
	return (1);
}

int	which_env_add(t_data *data)
{
	if (!in_env(data->env, "PWD"))
	{
		if (!add_pwd(&data->env))
			return (0);
	}
	if (!in_env(data->env, "_"))
	{
		if (!add_last(&data->env))
			return (0);
	}
	if (!in_env(data->env, "OLDPWD"))
	{
		if (!add_oldpwd(&data->env))
			return (0);
	}
	return (1);
}

int	copy_env(char **envp, t_data *data)
{
	int		i;
	t_env	*new;
	char	**split;

	i = -1;
	while (envp[++i])
	{
		split = split_var(envp[i]);
		if (!split)
			return (perror("Copy_env - Malloc"), \
			env_clear_data(&data->env), 0);
		if (split[0] && split[1])
			new = new_env(split[0], split[1], 1);
		else
			new = new_env(split[0], NULL, 0);
		if (!new)
			return (free_split(split), perror("Copy_env - Malloc"), \
			env_clear_data(&data->env), 0);
		new->has_equal = 0;
		if (split[1])
			new->has_equal = 1;
		env_add_back(&data->env, new);
		free(split);
	}
	return (1);
}
