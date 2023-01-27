/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/27 17:29:33 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_exec *exec)
{
	int	code;

	write(2, "exit\n", 5);
	if (size_arg(exec->arg) == 1)
		return (free_exit(exec, 0));
	else if (ft_is_num(exec->arg[1]))
		return (ft_man_perror("minishell: exit: ", exec->arg[1],
				": numeric argument required\n"), free_exit(exec, 255));
	else if (size_arg(exec->arg) == 2)
	{
		code = ft_atoi(exec->arg[1]) % 256;
		return (free_exit(exec, code));
	}
	write(2, "minishell: exit: too many arguments\n", 36);
	g_exit_status = 1;
}
