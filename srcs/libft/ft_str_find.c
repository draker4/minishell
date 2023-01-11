/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:27:58 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/20 15:07:50 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0' || (haystack == needle))
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (i + j < len && haystack[i + j] == needle[j] && haystack[i + j])
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

char	*ft_strchr(const char *str, int c)
{
	char	*search;
	size_t	i;

	i = 0;
	search = (char *)str;
	while (search[i])
	{
		if (search[i] == (char) c)
			return (&search[i]);
		i++;
	}
	if (c == '\0')
		return (&search[i]);
	return (NULL);
}

char	*ft_strrchr(const char *str, int c)
{
	int	size;
	int	i;

	size = ft_strlen(str);
	i = 0;
	while (i <= size)
	{
		if (str[size - i] == (char) c)
			return ((char *)&str[size - i]);
		i++;
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*(str + i))
		i++;
	return (i);
}
