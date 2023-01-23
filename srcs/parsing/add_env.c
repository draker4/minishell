/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:41:18 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/23 19:44:18 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_pwd(char **env)
{
	char	**copy;
	char	*buf;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (size_arg(env) + 2));
	if (!copy)
		return (free_split(env), perror("Add_env - Malloc"), NULL);
	while (env[i])
	{
		copy[i] = env[i];
		i++;
	}
	buf = getcwd(NULL, 0);
	if (!buf)
		return (free_split(env), perror("Add_env - Getcwd"), NULL);
	copy[i] = ft_strjoin("PWD=", buf);
	free(buf);
	if (!copy[i++])
		return (free_split(env), perror("Add_env - ft_strjoin"), NULL);
	copy[i] = NULL;
	return (copy);
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

char	**add_last_cmd(char **env)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (size_arg(env) + 2));
	if (!copy)
		return (free_split(env), perror("Add_last_cmd - Malloc"), NULL);
	while (env[i])
	{
		copy[i] = env[i];
		i++;
	}
	copy[i] = ft_strdup("_=/usr/bin/env");
	if (!copy[i++])
		return (free_split(env), perror("Add_last_cmd - ft_strdup"), NULL);
	copy[i] = NULL;
	return (copy);
}

char	**add_oldpwd(char **env)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (size_arg(env) + 2));
	if (!copy)
		return (free_split(env), perror("Add_oldpwd - Malloc"), NULL);
	while (env[i])
	{
		copy[i] = env[i];
		i++;
	}
	copy[i] = ft_strdup("OLDPWD");
	if (!copy[i++])
		return (free_split(env), perror("Add_oldpwd - ft_strdup"), NULL);
	copy[i] = NULL;
	return (copy);
}
