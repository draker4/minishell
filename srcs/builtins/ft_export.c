/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/27 17:52:47 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	include_value(t_env *full_env, char **var)
{
	t_env	*tmp;

	if (size_arg(var) == 1)
		return ;
	tmp = in_env(full_env, var[0]);
	tmp->has_equal = 1;
	if (tmp->value)
		free (tmp->value);
	tmp->value = var[1];
	free(var[0]);
}

void	include_var(t_data *data, char **var)
{
	t_env	*new;

	new = NULL;
	if (size_arg(var) == 1)
		new = new_env(var[0], var[1], 0);
	else if (size_arg(var) == 2)
		new = new_env(var[0], var[1], 1);
	if (!new)
	{
		free_split(var);
		return ;
	}
	env_add_back(&data->env, new);
}

int	check_export_arg(char *var, char *arg)
{
	int	i;

	if (var[0] == '_' && !var[1])
		return (1);
	else if (!ft_isalpha(var[0]) && var[0] != '_')
		return (g_exit_status = 1, ft_man_perror("minishell: export: `",
				arg, "': not a valid identifier"), 1);
	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (g_exit_status = 1, ft_man_perror("minishell: export: `",
					arg, "': not a valid identifier"), 1);
		i++;
	}
	return (0);
}

void	update_env(t_exec *exec)
{
	int		i;
	char	**var;

	i = 1;
	exec->data->modify_env = 1;
	g_exit_status = 0;
	while (exec->arg[i])
	{
		var = split_var(exec->arg[i]);
		if (!var)
			return (handle_error(exec));
		if (!check_export_arg(var[0], exec->arg[i]))
		{
			if (in_env(exec->data->env, var[0]))
				include_value(exec->data->env, var);
			else
				include_var(exec->data, var);
		}
		free(var);
		i++;
	}
	if (!exec->data->pid[exec->nb])
		exit(g_exit_status);
}

void	ft_export(t_exec *exec)
{
	if (size_arg(exec->arg) == 1
		|| (size_arg(exec->arg) == 2 && !exec->arg[1][0]))
		return (print_export(exec));
	return (update_env(exec));
}
