/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:32:11 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 13:55:29 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *var, char *value, int has_equal)
{
	t_env	*env;

	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("New_env: "), NULL);
	new->var = var;
	new->value = value;
	new->has_equal = has_equal;
	new->next = NULL;
	return (new);
}

void	env_clear_data(t_env **env)
{
	t_env	*clear;
	t_env	*tmp;

	if (!env)
		return ;
	clear = *env;
	while (clear)
	{
		tmp = clear;
		clear = clear->next;
		if (tmp->var)
			free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	*env = NULL;
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*current;

	if (env && *env)
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else if (env)
		*env = new;
}
