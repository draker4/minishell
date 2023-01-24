/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 10:43:52 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_no_arg(t_exec *exec)
{
	write(1, "\n", 1);
	if (!exec->pid)
		exit(0);
	return ;
}

void	ft_echo(t_exec *exec)
{
	int	i;
	int	new_line;

	if (size_arg(exec->arg) == 1)
		return (ft_echo_no_arg(exec));
	i = 1;
	new_line = 1;
	if (!ft_strncmp(exec->arg[1], "-n", 2) && !exec->arg[1][2])
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
	if (!exec->pid)
		exit(0);
}
