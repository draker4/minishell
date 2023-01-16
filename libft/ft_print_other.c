/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/16 13:07:11 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_put_char(char c)
{
	write(1, &c, 1);
	return (1);
}

size_t	ft_put_str(char *s)
{
	size_t	i;

	if (!s)
		return (ft_put_str("(null)"));
	i = ft_strlen(s);
	write(1, s, i);
	return (i);
}

static void	ft_print_ptr(size_t n, char *base, size_t *i)
{
	if (n >= 16)
		ft_print_ptr(n / 16, base, i);
	ft_put_char(base[n % 16]);
	*i += 1;
}

size_t	ft_put_ptr(size_t n)
{
	size_t	i;

	i = 0;
	ft_put_str("0x");
	ft_print_ptr(n, "0123456789abcdef", &i);
	i += 2;
	return (i);
}

void	ft_putstr_color(char *color, char *s, int fd)
{
	ft_putstr_fd(color, fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd(COLOR_RESET, fd);
}
