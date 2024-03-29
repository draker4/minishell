/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 11:06:40 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	ft_env(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->data->envp[i])
	{
		if (has_equal(exec->data->envp[i]))
		{
			write(1, exec->data->envp[i], ft_strlen(exec->data->envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	g_exit_status = 0;
	if (!exec->data->pid[exec->nb])
		exit(0);
}
