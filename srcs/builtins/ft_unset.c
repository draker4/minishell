/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 13:35:48 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	ft_unset(t_exec *exec)
{
	int		i;

	exec->data->modify_env = 1;
	if (size_arg(exec->arg) == 1)
	{
		g_exit_status = 0;
		if (!exec->data->pid[exec->nb])
			exit(0);
		return ;
	}
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
