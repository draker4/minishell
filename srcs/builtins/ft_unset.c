/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/27 18:32:00 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	not_delete(t_exec *exec)
{
	g_exit_status = 0;
	if (!exec->data->pid[exec->nb])
		exit(0);
	return ;
}

void	ft_unset(t_exec *exec)
{
	int	i;

	exec->data->modify_env = 1;
	if (size_arg(exec->arg) == 1)
	{
		g_exit_status = 0;
		if (!exec->data->pid[exec->nb])
			exit(0);
		return ;
	}
	if (exec->arg[1][0] == '_' && !exec->arg[1][1])
		return (not_delete(exec));
	i = 1;
	while (exec->arg[i])
	{
		if (in_env(exec->data->env, exec->arg[i]))
			remove_var(&exec->data->env, exec->arg[i]);
		i++;
	}
	g_exit_status = 0;
	if (!exec->data->pid[exec->nb])
		exit(0);
}
