/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:41:50 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 11:10:20 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_find_next_spaces(char *s, int *i)
{
	while (s[*i])
	{
		if (s[*i] == ' ' && !is_in_quote(s, *i))
		{
			if (s[*i] == ' ')
				return (1);
		}
		*i += 1;
	}
	return (0);
}

static char	**ft_cut_spaces(char *s, char **split)
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
		next = ft_find_next_spaces(s, &i);
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

char	**split_spaces(char *s)
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
		next = ft_find_next_spaces(s, &i);
		if (i - save)
			nb_str++;
		i += next;
	}
	split = malloc(sizeof(*split) * (nb_str + 1));
	if (split == NULL)
		return (NULL);
	split[nb_str] = NULL;
	return (ft_cut_spaces(s, split));
}
