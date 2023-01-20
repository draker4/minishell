/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:50:37 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/20 02:24:35 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space_tab(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32 && str[i] != 9)
			return (1);
		i++;
	}
	return (0);
}

static int	check_parenthesis(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(' && !is_in_quote(str, i))
		{
			write(2, "Please don't enter parenthesis!\n", 32);
			return (0);
		}
		else if (str[i] == ')' && !is_in_quote(str, i))
		{
			write(2, "Please don't enter parenthesis!\n", 32);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_nb_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
		}
		if (!str[i])
		{
			write(2, "Warning: Unclosed quotes!\n", 26);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_line(char *str)
{
	if (!str || !*str || !is_space_tab(str))
		return (0);
	add_history(str);
	if (!check_nb_quotes(str) || !check_parenthesis(str) \
	|| !check_and_or(str) || !check_redirections(str))
		return (0);
	return (1);
}
