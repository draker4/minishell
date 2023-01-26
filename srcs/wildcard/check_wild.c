/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wild.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:50 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/26 19:01:48 by bboisson         ###   ########lyon.fr   */
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


int	confirm_char(char *str, t_wild *tmp, int *i, int *j)
{
	if (str[*i] != '*' && str[*i] != tmp->arg[*j])
		return (1);
	else if (str[*i] != '*' && str[*i] == tmp->arg[*j])
	{
		*i += 1;
		*j += 1;
		if (!str[*i] && !tmp->arg[*j])
			return (tmp->keep = 1, 1);
		return (0);
	}
	else if (str[*i] == '*' && str[*i + 1] && tmp->arg[*j])
	{
		*i += 1;
		while (tmp->arg[*j] && str[*i] != tmp->arg[*j])
			*j += 1;
		if (str[*i] == tmp->arg[*j])
		{	
			*i += 1;
			*j += 1;
		}
		if (!tmp->arg[*j] && (!str[*i] || (str[*i] == '*' && !str[*i + 1])))
			return (tmp->keep = 1, 1);
		return (0);
	}
	return (tmp->keep = 1, 1);
}

void	check_wildcard(char *str, t_wild *wild)
{
	int		i;
	int		j;
	t_wild	*tmp;

	tmp = wild;
	while (tmp)
	{
		i = 0;
		j = 0;
		while (str[i] && tmp->arg[j])
		{
			if (confirm_char(str, tmp, &i, &j))
				break ;
		}
		tmp = tmp->next;
	}
}
