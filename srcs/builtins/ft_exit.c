/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 14:40:35 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_exec *exec)
{
	write(2, "exit\n", 5);
	if (size_arg(exec->arg) == 1)
		exit(0);
	else if (!ft_is_num(exec->arg[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, exec->arg[2], ft_strlen(exec->arg[2]));
		write(2, ": numeric argument required\n", 28);
		exit(255);
	}
	else if (size_arg(exec->arg) > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		g_exit_status = 1;
	}
	else if (size_arg(exec->arg) == 2)
		exit(ft_atoi(exec->arg[1]));
}
