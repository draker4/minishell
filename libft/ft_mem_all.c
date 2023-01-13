/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:51:02 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/13 15:37:35 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			*search;
	unsigned int	i;

	search = (char *)s;
	i = 0;
	while (i < n)
	{
		if (search[i] == (char) c)
			return (&search[i]);
		i++;
	}
	if (c == '\0' && n > 0)
		return (&search[i]);
	return (NULL);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}

void	*ft_memset(void *b, int c, size_t len)
{
	int		i;
	char	*dst;

	dst = b;
	i = 0;
	while (len)
	{
		dst[i] = (unsigned char) c;
		i++;
		len--;
	}
	return (b);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int	i;

	if (!n || (!dst && !src))
		return (dst);
	i = 0;
	while (n - i)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if ((!dst && !src) || (!dst && !src && len))
		return (NULL);
	if (dst > src)
	{
		while (len)
		{
			((unsigned char *)dst)[len - 1] = ((unsigned char *)src)[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
