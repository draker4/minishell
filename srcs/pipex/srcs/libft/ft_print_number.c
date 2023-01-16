/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2022/11/23 16:54:16 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_nbr(long int n, size_t *i)
{
	if (n < 0)
	{
		ft_put_char('-');
		n *= -1;
		*i += 1;
	}
	if (n >= 10)
		ft_print_nbr(n / 10, i);
	ft_put_char(n % 10 + 48);
	*i += 1;
}

void	ft_print_nbr_uns(size_t n, size_t *i)
{
	if (n >= 10)
		ft_print_nbr_uns(n / 10, i);
	ft_put_char(n % 10 + 48);
	*i += 1;
}

void	ft_print_nbr_base_uns(size_t n, char *base, size_t size, size_t *i)
{
	if (n >= size)
		ft_print_nbr_base_uns(n / size, base, size, i);
	ft_put_char(base[n % size]);
	*i += 1;
}
