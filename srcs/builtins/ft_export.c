/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 17:35:44 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	include_value(t_env *full_env, char **var)
{
	t_env	*tmp;

	if (size_arg(var) == 2)
		return ;
	tmp = in_env(full_env, var[0]);
	if (tmp->value)
		free (tmp->value);
	tmp->has_equal = 1;
	tmp->value = var[2];
}

void	include_var(t_data *data, char **var)
{
	t_env	*new;

	if (size_arg(var) == 1)
		new = new_env(var[0], var[1], 0);
	else if (size_arg(var) == 2)
		new = new_env(var[0], var[1], 1);
	else
		return ;
	if (!new)
	{
		free_split(var);
		return ;
	}
	env_add_back(&data->env, new);
}

void	ft_export(t_exec *exec)
{
	int		i;
	char	**var;

	if (size_arg(exec->arg) == 1)
		return (print_export(exec));
	i = 1;
	exec->data->modify_env = 1;
	while (exec->arg[i])
	{
		var = split_var(exec->arg[i]);
		if (!var)
		{
			if (!exec->pid)
				exit(FAIL);
			return ;
		}
		if (in_env(exec->data->env, var[0]))
			include_value(exec->data->env, var);
		else
			include_var(exec->data, var);
		i++;
	}
	if (!exec->pid)
		exit(0);
}
