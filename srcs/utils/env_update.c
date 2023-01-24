/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:53:47 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 14:47:16 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_var(t_env **full_env, char *search_var)
{
	t_env	*tmp;
	t_env	*prev;

	if (!full_env || !search_var)
		return (FAIL);
	tmp = *full_env;
	prev = NULL;
	while ((tmp))
	{
		if (ft_strncmp(tmp->var, search_var,
				ft_strlen(tmp->var)))
		{
			prev->next = tmp->next;
			if (tmp->var)
				free(tmp->var);
			if (tmp->value)
				free(tmp->value);
			free (tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

t_env	*in_env(t_env *full_env, char *search_var)
{
	if (!full_env || !search_var)
		return (NULL);
	while (full_env)
	{
		if (!ft_strncmp(full_env->var, search_var, ft_strlen(full_env->var)))
			return (full_env);
		full_env = full_env->next;
	}
	return (NULL);
}
