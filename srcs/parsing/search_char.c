/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:12:47 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/16 18:35:47 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_last_bracket(char *str, int i)
{
	i++;
	while (str[i])
	{
		if (str[i] == ')')
			return (0);
		i++;
	}
	return (1);
}

int	is_in_quote(char *str, int index)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				if (i++ == index)
					return (1);
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				if (i++ == index)
					return (1);
		}
		if (str[i])
			i++;
		else
			return (1);
	}
	return (0);
}

int	has_and_or_symbols(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '&' && !is_in_quote(str, i) && str[i + 1] && \
		str[i + 1] == '&')
			return (1);
		if (str[i] == '|' && !is_in_quote(str, i) && str[i + 1] && \
		str[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	has_pipe_symbol(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && !is_in_quote(str, i))
			return (1);
		i++;
	}
	return (0);
}
