/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 09:19:07 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_exec *exec)
{
	int		i;

	exec->data->modify_env = 1;
	if (size_arg(exec->arg) == 1)
	{
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
	if (!exec->data->pid[exec->nb])
		exit(0);
}
