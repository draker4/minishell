/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptiste <baptiste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:05:50 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/27 01:34:06 by baptiste         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	redefine_str(t_check *check, char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (new_str(&new, str[i]))
			return (1);
		if (str[i] == '*')
		{
			while (str[i] == '*')
				i++;
		}
		else
			i++;
	}
	check->str = new;
	return (0);
}

int	check_start_end(t_check *check, int type)
{
	int	i;

	if (!type)
	{
		i = 0;
		while (check->str[i] && check->str[i] != '*')
		{
			if (new_str(&check->start, check->str[i++]))
				return (1);
		}
		return (0);
	}
	i = check->s_str - 1;
	while (i >= 0 && check->str[i] != '*')
		i--;
	i++;
	while (check->str[i])
	{
		if (new_str(&check->end, check->str[i++]))
			return (1);
	}
	return (0);
}

int	define_check(t_check *check, char *str)
{
	check->start = NULL;
	check->end = NULL;
	check->tab = NULL;
	check->nb = nb_wildcard(str);
	if (redefine_str(check, str))
		return (1);
	check->s_str = ft_strlen(check->str);
	if (check_start_end(check, 0) || check_start_end(check, 1))
		return (free_check(check), 1);
	check->s_start = ft_strlen(check->start);
	check->s_end = ft_strlen(check->end);
	check->tab = ft_split(str, '*');
	if (!check->tab)
		return (perror("confirm_middle - malloc"), free_check(check), 1);
	check->s_tab = size_arg(check->tab);
	return (0);
}
