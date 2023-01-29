/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/29 11:45:19 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	ft_is_num(char *str)
{
	size_t	i;

	i = 0;
	if (!*str)
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

static double	modulo(double x, double y)
{
	return (x - (int)(x / y) *y);
}

static unsigned char	ft_long_atoi(char *str)
{
	size_t			i;
	long double		result;

	i = 0;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		result = result * 10 + str[i] - '0';
		if (result > LLONG_MAX && str[0] != '-')
			return (-1);
		if (-result < LLONG_MIN)
			return (-1);
		i++;
	}
	return (result);
}

unsigned char	ft_exit(t_exec *exec)
{
	long double	code;

	write(1, "exit\n", 5);
	if (size_arg(exec->arg) == 1)
		return (free_exit(exec, 0));
	else if (ft_is_num(exec->arg[1]) || ft_long_atoi(exec->arg[1]) == -1)
		return (ft_man_perror("minishell: exit: ", exec->arg[1],
				": numeric argument required"), free_exit(exec, 255));
	else if (size_arg(exec->arg) == 2)
	{
		code = ft_long_atoi(exec->arg[1]);
		return (free_exit(exec, code));
	}
	write(2, "minishell: exit: too many arguments\n", 36);
	g_exit_status = 1;
}
