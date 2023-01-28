/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:27:57 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 15:14:12 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	single_quote(char *str, char **word_parsed, int *i)
{
	while (str[*i] && str[*i] != '\'')
	{
		*word_parsed = str_add(*word_parsed, str[*i]);
		if (!*word_parsed)
			return (0);
		*i += 1;
	}
	return (1);
}

static int	double_quotes(char *str, char **word_parsed, int *i, char **envp)
{
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$' && str[*i + 1] && (ft_isalnum(str[*i + 1]) \
		|| str[*i + 1] == '_' || str[*i + 1] == '{'))
		{
			*i += 1;
			if (!check_env_quotes(str, word_parsed, i, envp))
				return (0);
		}
		else
		{
			*word_parsed = str_add(*word_parsed, str[*i]);
			if (!*word_parsed)
				return (0);
		}
		*i += 1;
	}
	return (1);
}

static int	adapt_line(char *str, char **word_parsed, int *i, char **envp)
{
	if (str[*i] == '\'')
	{
		*i += 1;
		if (!single_quote(str, word_parsed, i))
			return (0);
	}
	else if (str[*i] == '"')
	{
		*i += 1;
		if (!double_quotes(str, word_parsed, i, envp))
			return (0);
	}
	else if (str[*i] == '$')
	{
		*i += 1;
		if (!check_env(str, word_parsed, i, envp))
			return (0);
	}
	return (1);
}

int	parse_quotes_env(char *str, char **word_parsed, char **envp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || (str[i] == '$' \
		&& str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || \
		str[i + 1] == '{')))
		{
			if (!adapt_line(str, word_parsed, &i, envp))
				return (0);
		}
		else
		{
			*word_parsed = str_add(*word_parsed, str[i]);
			if (!*word_parsed)
				return (0);
		}
		if (str[i])
			i++;
	}
	return (1);
}
