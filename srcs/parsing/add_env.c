/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:41:18 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 15:12:35 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_pwd(t_env **env)
{
	char	*buf;
	char	*var;
	t_env	*new;

	buf = getcwd(NULL, 0);
	if (!buf)
		return (env_clear_data(env), perror("Add_pwd - Getcwd"), 0);
	var = ft_strdup("PWD");
	if (!var)
		return (env_clear_data(env), free(buf), \
		perror("Add_pwd - ft_strdup"), 0);
	new = new_env(var, buf, 1);
	if (!new)
		return (env_clear_data(env), free(buf), \
		free(var), perror("Add_pwd - ft_strdup"), 0);
	env_add_back(env, new);
	return (1);
}

char	**add_shlvl(char **env)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (size_arg(env) + 2));
	if (!copy)
		return (free_split(env), perror("Add_shlvl - Malloc"), NULL);
	while (env[i])
	{
		copy[i] = env[i];
		i++;
	}
	copy[i] = ft_strdup("SHLVL=1");
	if (!copy[i++])
		return (free_split(env), perror("Add_shlvl - ft_strdup"), NULL);
	copy[i] = NULL;
	return (copy);
}

int	shlvl_plus_one(char **env)
{
	int		nb_atoi;
	int		i;
	char	*nb_itoa;
	char	*nb_join;

	nb_atoi = (ft_atoi(getenv("SHLVL")));
	nb_atoi++;
	nb_itoa = ft_itoa(nb_atoi);
	if (!nb_itoa)
		return (free_split(env), perror("Shlvl_plus_one - ft_itoa"), 0);
	nb_join = ft_strjoin("SHLVL=", nb_itoa);
	if (!nb_join)
		return (free_split(env), perror("Shlvl_plus_one - ft_strjoin"), 0);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			break ;
		i++;
	}
	free(env[i]);
	env[i] = nb_join;
	return (1);
}

int	add_last(t_env **env)
{
	char	*var;
	char	*value;
	t_env	*new;

	var = ft_strdup("_");
	if (!var)
		return (env_clear_data(env), perror("Add_last - ft_strdup"), 0);
	value = ft_strdup("/usr/bin/env");
	if (!value)
		return (free(var), env_clear_data(env), \
		perror("Add_last - ft_strdup"), 0);
	new = new_env(var, value, 1);
	if (!new)
	{
		free(var);
		free(value);
		env_clear_data(env);
		return (0);
	}
	env_add_back(env, new);
	return (1);
}

int	add_oldpwd(char **env)
{
	char	**var;
	t_env	*new;

	var = ft_strdup("OLDPWD");
	if (!var)
		return (env_clear_data(env), perror("Add_oldpwd - ft_strdup"), 0);
	new = new_env(var, NULL, 1);
	if (!new)
	{
		free(var);
		env_clear_data(env);
		return (0);
	}
	env_add_back(env, new);
	return (1);
}
