/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2022/11/23 16:54:55 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_printf_nbr(int n, char type)
{
	size_t	i;

	i = 0;
	if (type == 'u')
		ft_print_nbr_uns(n, &i);
	else if (type == 'x')
		ft_print_nbr_base_uns(n, "0123456789abcdef", 16, &i);
	else if (type == 'X')
		ft_print_nbr_base_uns(n, "0123456789ABCDEF", 16, &i);
	else
		ft_print_nbr(n, &i);
	return (i);
}

static int	ft_conv_type(const char *str, va_list ap, int i)
{
	if (str[i] == 'c')
		return (ft_put_char((char)va_arg(ap, int)));
	else if (str[i] == 's')
		return (ft_put_str(va_arg(ap, char *)));
	else if (str[i] == 'p')
		return (ft_put_ptr(va_arg(ap, size_t)));
	else if (str[i] == 'd' || str[i] == 'i')
		return (ft_printf_nbr(va_arg(ap, int), 0));
	else if (str[i] == 'u')
		return (ft_printf_nbr(va_arg(ap, int), 'u'));
	else if (str[i] == 'x')
		return (ft_printf_nbr(va_arg(ap, int), 'x'));
	else if (str[i] == 'X')
		return (ft_printf_nbr(va_arg(ap, int), 'X'));
	else if (str[i] == '%')
		return (ft_put_char('%'));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	size_t	i;
	size_t	total;

	va_start(ap, str);
	i = 0;
	total = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			total += ft_conv_type(str, ap, i + 1);
			i += 2;
		}
		else
		{
			write(1, &str[i], 1);
			total++;
			i++;
		}
	}
	va_end(ap);
	return (total);
}
