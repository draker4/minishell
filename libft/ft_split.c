/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:17 by bboisson          #+#    #+#             */
/*   Updated: 2022/12/15 10:00:08 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free (str);
}

static char	**ft_free_double(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free (str);
	return (NULL);
}

/*Separe s par c en comptabiliasant le nombre de mots.*/
int	ft_divide(char const *s, char c)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		j = i;
		while (s[i] != c && s[i])
			i ++;
		if (i - j)
			size++;
		if (s[i])
			i++;
	}	
	return (size);
}

/*Insert chaque string dans le tableau split.*/
static char	**ft_insert(const char *s, char c, char **split, int i)
{
	int		j;
	int		k;
	int		l;

	k = 0;
	while (s[i])
	{
		j = i;
		while (s[i] != c && s[i])
			i++;
		if (i - j)
		{
			split[k] = malloc(sizeof(**split) * (i - j + 1));
			if (split[k] == NULL)
				return (ft_free_double(split, k));
			l = 0;
			while (j < i)
				split[k][l++] = s[j++];
			split[k][l] = '\0';
			k++;
		}
		if (s[i])
			i++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**split;

	if (s == NULL)
		return (NULL);
	size = ft_divide(s, c);
	split = malloc(sizeof(*split) * (size + 1));
	if (split == NULL)
		return (NULL);
	if (ft_insert(s, c, split, 0) == NULL)
		return (NULL);
	split[size] = NULL;
	return (split);
}
