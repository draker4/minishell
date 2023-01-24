/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:41:18 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 17:18:10 by bperriol         ###   ########lyon.fr   */
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

int	add_shlvl(t_env **env)
{
	char	*var;
	char	*value;
	t_env	*new;

	var = ft_strdup("SHLVL");
	if (!var)
		return (env_clear_data(env), perror("Add_shlvl- ft_strdup"), 0);
	value = ft_strdup("1");
	if (!value)
		return (free(var), env_clear_data(env), \
		perror("Add_shlvl - ft_strdup"), 0);
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

int	shlvl_plus_one(t_env **env)
{
	t_env	*tmp;
	int		nb_atoi;
	char	*nb_itoa;

	tmp = in_env(*env, "SHLVL");
	nb_atoi = (ft_atoi(tmp->value));
	nb_atoi++;
	nb_itoa = ft_itoa(nb_atoi);
	if (!nb_itoa)
		return (env_clear_data(env), perror("Shlvl_plus_one - ft_itoa"), 0);
	free(tmp->value);
	tmp->value = nb_itoa;
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

int	add_oldpwd(t_env **env)
{
	char	*var;
	t_env	*new;

	var = ft_strdup("OLDPWD");
	if (!var)
		return (env_clear_data(env), perror("Add_oldpwd - ft_strdup"), 0);
	new = new_env(var, NULL, 0);
	if (!new)
	{
		free(var);
		env_clear_data(env);
		return (0);
	}
	env_add_back(env, new);
	return (1);
}
