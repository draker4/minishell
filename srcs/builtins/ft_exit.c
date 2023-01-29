/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:30:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/29 14:19:59 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "math.h"

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

static long long int	ft_long_atoi(char *str)
{
	size_t			i;
	long long int	result;
	long long int	sign;

	i = 0;
	result = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

static int	ft_check_atoi(char *str)
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
			return (0);
		result = result * 10 + str[i] - '0';
		if (result > LLONG_MAX && str[0] != '-')
			return (1);
		if (-result < LLONG_MIN)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_exec *exec)
{
	long long int	code;

	write(1, "exit\n", 5);
	if (size_arg(exec->arg) == 1)
		return (free_exit(exec, 0));
	else if (ft_is_num(exec->arg[1]) || ft_check_atoi(exec->arg[1]))
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
