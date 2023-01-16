/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2022/11/23 15:56:27 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j] != '\0' && j < n)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	orig_dstsize;
	size_t	srcsize;

	srcsize = ft_strlen(src);
	if (!dstsize || (!dst && !src))
		return (dstsize + srcsize);
	orig_dstsize = ft_strlen(dst);
	if (dstsize <= orig_dstsize)
		return (dstsize + srcsize);
	else if (dstsize <= orig_dstsize + srcsize)
	{
		ft_strncat(dst, src, dstsize - orig_dstsize - 1);
		return (orig_dstsize + srcsize);
	}
	else
	{
		ft_strncat(dst, src, srcsize);
		return (orig_dstsize + srcsize);
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	sizenew;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	sizenew = ft_strlen(s1) * sizeof(char) + ft_strlen(s2) * sizeof(char) + 1;
	if (sizenew > SIZE_MAX)
		return (NULL);
	new = malloc(sizenew);
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		new[i++] = s1[j++];
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}
