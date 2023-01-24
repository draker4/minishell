/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:53:47 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 17:41:54 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	join_var_value(char **envp, t_env *env)
{
	int		i;
	int		j;

	*envp = malloc(sizeof(char) * (ft_strlen(env->var) + ft_strlen(env->value)
				+ env->has_equal + 1));
	if (*envp == NULL)
		return (perror("Join_var_value - malloc"), FAIL);
	i = 0;
	j = 0;
	while (env->var[j])
		(*envp)[i++] = env->var[j++];
	if (env->has_equal)
		(*envp)[i++] = '=';
	j = 0;
	while (env->value && env->value[j])
		(*envp)[i++] = env->value[j++];
	(*envp)[i] = '\0';
	return (0);
}

int	update_envp(t_data *data)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = data->env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (data->envp)
		free_split(data->envp);
	data->envp = malloc(sizeof(char *) * (i + 1));
	if (!data->envp)
		return (perror("Update_envp - malloc"), FAIL);
	i = 0;
	tmp = data->env;
	while (tmp)
	{
		if (join_var_value(&data->envp[i++], tmp))
			return (free_split(data->envp), FAIL);
		tmp = tmp->next;
	}
	data->envp[i] = NULL;
	return (data->modify_env = 0, 0);
}

int	remove_var(t_env **full_env, char *search_var)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *full_env;
	prev = NULL;
	while ((tmp))
	{
		if (!ft_strncmp(tmp->var, search_var, ft_strlen(tmp->var) + 1))
		{
			if (!prev)
				*full_env = tmp->next;
			else
				prev->next = tmp->next;
			if (tmp->var)
				free(tmp->var);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

t_env	*in_env(t_env *full_env, char *search_var)
{
	if (!full_env || !search_var)
		return (NULL);
	while (full_env)
	{
		if (!ft_strncmp(full_env->var, search_var, ft_strlen(full_env->var) + 1))
			return (full_env);
		full_env = full_env->next;
	}
	return (NULL);
}
