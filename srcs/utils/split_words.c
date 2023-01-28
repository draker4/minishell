/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:08:33 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 14:44:46 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_find_next(char *s, int *i)
{
	if ((s[*i] == '>' || s[*i] == '<') && !is_in_quote(s, *i, 0))
	{
		*i += 1;
		return (0);
	}
	while (s[*i])
	{
		if ((s[*i] == ' ' || s[*i] == '>' || s[*i] == '<') \
		&& !is_in_quote(s, *i, 0))
		{
			if (s[*i] == ' ')
				return (1);
			else
				return (0);
		}
		*i += 1;
	}
	return (0);
}

static char	**ft_cut(char *s, char **split)
{
	int	i;
	int	save;
	int	nb;
	int	k;
	int	next;

	i = 0;
	nb = 0;
	while (s[i])
	{
		save = i;
		next = ft_find_next(s, &i);
		if (i - save)
		{
			split[nb] = malloc(sizeof(**split) * (i - save + 1));
			if (split[nb] == NULL)
				return (free_split(split), NULL);
			k = 0;
			while (save < i)
				split[nb][k++] = s[save++];
			split[nb++][k] = '\0';
		}
		i += next;
	}
	return (split);
}

char	**split_not_quotes(char *s)
{
	char	**split;
	int		i;
	int		save;
	int		nb_str;
	int		next;

	i = 0;
	nb_str = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		save = i;
		next = ft_find_next(s, &i);
		if (i - save)
			nb_str++;
		i += next;
	}
	split = malloc(sizeof(*split) * (nb_str + 1));
	if (split == NULL)
		return (NULL);
	split[nb_str] = NULL;
	return (ft_cut(s, split));
}
