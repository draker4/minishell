/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 09:17:54 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!exec->data->pid[exec->nb])
		exit(0);
}
