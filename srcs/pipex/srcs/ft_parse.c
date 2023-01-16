/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 12:12:05 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_check_duplicates(int data, t_stack *a)
{
	t_arg	*tmp;

	tmp = a->top;
	while (tmp)
	{
		if (tmp->data == data)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_get_data(const char *str, t_stack *a)
{
	int				i;
	int				neg;
	long int		str_int;

	i = 0;
	neg = 1;
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			neg *= -1;
	str_int = 0;
	if ((str[i] < '0' || '9' < str[i]))
		return (ft_putstr_fd("Error\n", 2), ft_free_arg(a));
	while (str[i] >= '0' && str[i] <= '9')
	{
		str_int = str_int * 10 + str[i++] - 48;
		if (str_int * neg < INT_MIN || INT_MAX < str_int * neg)
			return (ft_putstr_fd("Error\n", 2), ft_free_arg(a));
	}
	if (str[i] != '\0')
		return (ft_putstr_fd("Error\n", 2), ft_free_arg(a));
	if (!ft_check_duplicates(str_int * neg, a))
		return (ft_putstr_fd("Error\n", 2), ft_free_arg(a));
	return (ft_add_back((int)str_int * neg, a));
}

void	ft_parse(int argc, char **argv, t_stack *a)
{
	int		i;
	int		size;
	char	**arg;

	if (argc == 2)
	{
		arg = ft_split(argv[1], ' ');
		if (arg[0] == NULL)
			return (ft_free_split(arg));
		size = 0;
		while (arg[size])
			size++;
		i = 0;
		while (i < size)
			if (!ft_get_data(arg[i++], a))
				return (ft_free_split(arg));
		ft_free_split(arg);
	}
	else
	{
		i = 1;
		while (i < argc)
			if (!ft_get_data(argv[i++], a))
				return ;
	}
}
