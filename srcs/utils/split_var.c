/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:47:39 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 14:07:16 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:08:33 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/16 16:50:32 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_find_next_var(char *s, int *i)
{
	while (s[*i])
	{
		if (s[*i] == '=' && !is_in_quote(s, *i))
			return ;
		*i += 1;
	}
	return ;
}

static char	**ft_cut_var(char *s, char **split)
{
	int	i;
	int	save;
	int	nb;
	int	k;

	i = 0;
	nb = 0;
	while (s[i])
	{
		save = i;
		ft_find_next(s, &i);
		if (i - save)
		{
			split[nb] = malloc(sizeof(**split) * (i - save + 1));
			if (split[nb] == NULL)
				return (perror("Ft_cut_var - Malloc"), free_split(split), NULL);
			k = 0;
			while (save < i)
				split[nb][k++] = s[save++];
			split[nb++][k] = '\0';
		}
		i += 1;
	}
	return (split);
}

char	**split_var(char *s)
{
	char	**split;
	int		i;
	int		save;
	int		next;

	i = 0;
	if (s == NULL)
		return (NULL);
	split = malloc(sizeof(*split) * 3);
	if (split == NULL)
		return (perror("Split_var - Malloc"), NULL);
	split[3] = NULL;
	return (ft_cut_var(s, split));
}
