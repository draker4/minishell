/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_around_par.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:35:13 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/15 10:49:42 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_after_left_par(char *str, int *i)
{
	while (str[*i] && (str[*i] == '(' || str[*i] == ' '))
		*i += 1;
	if (str[*i] == '&' || str[*i] == '|' || str[*i] == ')')
	{
		write(2, "Wrong characters after left parenthesis!\n", 41);
		return (0);
	}
	return (1);
}

static int	check_after_right_par(char *str, int *i)
{
	while (str[*i] && (str[*i] == ')' || str[*i] == ' '))
		*i += 1;
	if (str[*i] != '&' && str[*i] != '|' && str[*i] != '\0' && str[*i] != '>' \
	&& str[*i] != '<')
	{
		write(2, "Wrong characters after right parenthesis!\n", 42);
		return (0);
	}
	return (1);
}

static int	check_before_left_par(char *str, int i)
{
	while (str[i - 1] && (str[i] == '(' || str[i] == ' '))
		i--;
	if (i > 0 && str[i] != '&' && str[i] != '|')
	{
		write(2, "Wrong characters before left parenthesis!\n", 42);
		return (0);
	}
	return (1);
}

static int	check_before_right_par(char *str, int i)
{
	while (str[i - 1] && (str[i] == ')' || str[i] == ' '))
		i--;
	if (i > 0 && (str[i] == '&' || str[i] == '|' || str[i] == '>' \
	|| str[i] == '<'))
	{
		write(2, "Wrong characters before right parenthesis!\n", 43);
		return (0);
	}
	return (1);
}

int	check_around_parenthesis(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(' && !is_in_quote(str, i))
		{
			if (!check_before_left_par(str, i))
				return (0);
			if (!check_after_left_par(str, &i))
				return (0);
		}
		else if (str[i] == ')' && !is_in_quote(str, i))
		{
			if (!check_before_right_par(str, i))
				return (0);
			if (!check_after_right_par(str, &i))
				return (0);
		}
		if (str[i])
			i++;
	}
	return (1);
}
