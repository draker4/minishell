/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/27 18:21:18 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	ft_echo_no_arg(t_exec *exec)
{
	write(1, "\n", 1);
	g_exit_status = 0;
	if (!exec->data->pid[exec->nb])
		exit(0);
	return ;
}

int	flag_n(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (1);
	if (arg[1] != 'n')
		return (1);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(t_exec *exec)
{
	int	i;
	int	new_line;

	if (size_arg(exec->arg) == 1)
		return (ft_echo_no_arg(exec));
	i = 1;
	new_line = 1;
	while (!flag_n(exec->arg[i]))
	{
		new_line = 0;
		i++;
	}
	while (exec->arg[i])
	{
		write(1, exec->arg[i], ft_strlen(exec->arg[i]));
		if (exec->arg[++i])
			write(1, " ", 1);
	}
	if (new_line)
		write(1, "\n", 1);
	g_exit_status = 0;
	if (!exec->data->pid[exec->nb])
		exit(0);
}
