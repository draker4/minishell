/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:50 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/26 20:52:10 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_str(char **str, char c)
{
	int		i;
	char	*copy;

	copy = malloc(sizeof(char) * ((int)ft_strlen(*str) + 2));
	if (!copy)
	{
		if (*str)
			free(*str);
		return (perror("Str_add: "), FAIL);
	}
	i = 0;
	while ((*str) && (*str)[i])
	{
		copy[i] = (*str)[i];
		i++;
	}
	copy[i++] = c;
	copy[i] = '\0';
	if (*str)
		free(*str);
	*str = copy;
	return (0);
}

char	*check_str(char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (new_str(&new, str[i]))
			return (NULL);
		if (str[i] == '*')
		{
			while (str[i] == '*')
				i++;
		}
		else
			i++;
	}
	return (new);
}

int	nb_wildcard(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{	
		if (str[i])
			nb++;
		i++;
	}
	return (nb);
}

int	check_search(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i])
		return (0);
	return (1);
}

int	confirm_middle(t_wild *wild, char **tab)
{
	int		i;
	int		j;

	if (!tab)
		return (perror("confirm_middle - malloc"), 1);
	i = 0;
	j = 0;
	while (tab[i] && wild->arg[j])
	{
		if (!check_search(tab[i], &wild->arg[j]))
			i++;
		j++;
	}
	if (!tab[i])
		return (free_split(tab), 0);
	return (free_split(tab), 1);
}
