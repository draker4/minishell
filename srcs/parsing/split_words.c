/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:08:33 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/16 13:04:46 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_free_double_words(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free (str);
	return (NULL);
}

/*Separe s par c en comptabiliasant le nombre de mots.*/
static int	ft_divide_words(char *s, char c)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		j = i;
		while (s[i] && (s[i] != c || is_in_quote(s, i)))
			i++;
		if (i - j)
			size++;
		if (s[i])
			i++;
	}	
	return (size);
}

/*Insert chaque string dans le tableau split.*/
static char	**ft_insert_words(char *s, char c, char **split, int i)
{
	int		j;
	int		k;
	int		l;

	k = 0;
	while (s[i])
	{
		j = i;
		while (s[i] && (s[i] != c || is_in_quote(s, i)))
			i++;
		if (i - j)
		{
			split[k] = malloc(sizeof(**split) * (i - j + 1));
			if (split[k] == NULL)
				return (ft_free_double_words(split, k));
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

char	**split_not_quotes(char *s, char c)
{
	int		size;
	char	**split;

	if (s == NULL)
		return (NULL);
	size = ft_divide_words(s, c);
	split = malloc(sizeof(*split) * (size + 1));
	if (split == NULL)
		return (NULL);
	if (ft_insert_words(s, c, split, 0) == NULL)
		return (NULL);
	split[size] = NULL;
	return (split);
}
