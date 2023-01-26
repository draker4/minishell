/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptiste <baptiste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:47:39 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/26 09:37:29 by baptiste         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_cut_value(char *s, char **split, int i)
{
	int	k;

	k = 0;
	split[1] = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!split[1])
		return (free(split[0]), free(split), NULL);
	while (s[i])
		split[1][k++] = s[i++];
	split[1][k] = '\0';
	return (split);
}

static char	**ft_cut_var(char *s, char **split)
{
	int	i;
	int	k;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	split[0] = malloc(sizeof(**split) * (i + 1));
	if (split[0] == NULL)
		return (free(split), perror("Ft_cut_var - Malloc"), NULL);
	k = 0;
	while (k < i)
	{
		split[0][k] = s[k];
		k++;
	}
	split[0][k] = '\0';
	if (!s[i])
	{
		split[1] = NULL;
		return (split);
	}
	else
		return (ft_cut_value(s, split, ++i));
}

char	**split_var(char *s)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = malloc(sizeof(*split) * 3);
	if (split == NULL)
		return (perror("Split_var - Malloc"), NULL);
	split[2] = NULL;
	return (ft_cut_var(s, split));
}
