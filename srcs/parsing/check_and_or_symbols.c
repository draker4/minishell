/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_or_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:32:16 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/17 11:21:16 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_and(char *str, int *i)
{
	if (!str[*i + 1] || str[*i + 1] != '&')
	{
		write(2, "Wrong '&' symbol!\n", 18);
		return (0);
	}
	*i += 2;
	while (str[*i] && str[*i] == ' ')
		*i += 1;
	if (!str[*i] || str[*i] == '|' || str[*i] == '&')
	{
		write(2, "Wrong '|' symbol!\n", 18);
		return (0);
	}
	return (1);
}

static int	check_or(char *str, int *i)
{
	if (!str[*i + 1])
	{
		write(2, "Wrong '&' symbol!\n", 18);
		return (0);
	}
	if (str[*i + 1] == '|')
		*i += 1;
	*i += 1;
	while (str[*i] && str[*i] == ' ')
		*i += 1;
	if (!str[*i] || str[*i] == '|' || str[*i] == '&')
	{
		write(2, "Wrong '|' symbol!\n", 18);
		return (0);
	}
	return (1);
}

static int	begin_and_or_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32)
		i++;
	if (str[i])
	{
		if (str[i] == '&')
			write(2, "Wrong '&' symbol!\n", 18);
		if (str[i] == '|')
			write(2, "Wrong '|' symbol!\n", 18);
		return (0);
	}
	return (1);
}

int	check_and_or(char *str)
{
	int	i;

	i = 0;
	if (begin_and_or_char(str))
		return (0);
	while (str[i])
	{
		if (str[i] == '&' && !is_in_quote(str, i))
		{
			if (!check_and(str, &i))
				return (0);
		}
		else if (str[i] == '|' && !is_in_quote(str, i))
		{
			if (!check_or(str, &i))
				return (0);
		}
		if (str[i])
			i++;
	}
	return (1);
}
