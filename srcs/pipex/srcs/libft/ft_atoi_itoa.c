/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/09 11:28:55 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				negative;
	long long int	str_int;

	i = 0;
	negative = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			negative *= -1;
	str_int = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str_int != (str_int * 10 + (str[i] - '0')) / 10)
		{
			if (negative == -1)
				return (0);
			return (-1);
		}
		str_int = str_int * 10 + str[i] - 48;
		i++;
	}
	return ((int)str_int * negative);
}

static int	ft_itoa_size(long int n)
{
	int		i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_include_nbr(long int n, char *new, int *i)
{
	if (n < 0)
	{
		new[*i] = '-';
		n *= -1;
		*i += 1;
	}
	if (n >= 10)
		ft_include_nbr(n / 10, new, i);
	new[*i] = n % 10 + 48;
	*i += 1;
}

char	*ft_itoa(int n)
{
	int		i;
	size_t	size;
	char	*new;

	size = (sizeof(char) * (ft_itoa_size(n) + 1));
	if (size > SIZE_MAX)
		return (NULL);
	new = malloc(size);
	if (new == NULL)
		return (NULL);
	i = 0;
	ft_include_nbr(n, new, &i);
	new[i] = '\0';
	return (new);
}
