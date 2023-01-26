/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptiste <baptiste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/26 09:58:42 by baptiste         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
		i++;
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
	int	code;

	write(2, "exit\n", 5);
	if (size_arg(exec->arg) == 1)
	{
		free_all(exec->data);
		exit(0);
	}
	else if (!ft_is_num(exec->arg[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, exec->arg[1], ft_strlen(exec->arg[1]));
		write(2, ": numeric argument required\n", 28);
		free_all(exec->data);
		exit(255);
	}
	else if (size_arg(exec->arg) == 2)
	{
		code = ft_atoi(exec->arg[1]) % 256;
		free_all(exec->data);
		exit(code);
	}
	write(2, "minishell: exit: too many arguments\n", 36);
	g_exit_status = 1;
}
