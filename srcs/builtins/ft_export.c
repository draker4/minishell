/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 18:53:22 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	handle_error(t_exec *exec)
{
	g_exit_status = 1;
	if (!exec->data->pid[exec->nb])
		exit(1);
	return ;
}

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

void	update_env(t_exec *exec)
{
	int		i;
	char	**var;

	i = 1;
	exec->data->modify_env = 1;
	while (exec->arg[i])
	{
		var = split_var(exec->arg[i]);
		if (!var)
			return (handle_error(exec));
		if (ft_isdigit(var[0][0]))
			ft_perror("minishell: export: `", exec->arg[i],
				"': not a valid identifier");
		else if (in_env(exec->data->env, var[0]))
			include_value(exec->data->env, var);
		else
			include_var(exec->data, var);
		free_split(var);
		i++;
	}
	g_exit_status = 0;
	if (!exec->data->pid[exec->nb])
		exit(0);
}

void	ft_export(t_exec *exec)
{
	if (size_arg(exec->arg) == 1)
		return (print_export(exec));
	return (update_env(exec));
}
