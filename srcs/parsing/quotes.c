/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:27:57 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/13 18:06:32 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	single_quote(char *str, char **line_parsed, int *i)
{
	while (str[*i] && str[*i] != '\'')
	{
		*line_parsed = str_add(*line_parsed, str[*i]);
		if (!*line_parsed)
			return (0);
		*i += 1;
	}
	if (str[*i] == '\0')
	{
		write(2, "Warning: Unclosed quotes!\n", 26);
		return (0);
	}
	return (1);
}

static int	double_quotes(char *str, char **line_parsed, int *i, char **envp)
{
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$' && str[*i + 1] \
		&& str[*i + 1] != 32 && str[*i + 1] != 9)
		{
			*i += 1;
			if (!check_env(str, line_parsed, i, envp))
				return (0);
		}
		else
		{
			*line_parsed = str_add(*line_parsed, str[*i]);
			if (!*line_parsed)
				return (0);
		}
		*i += 1;
	}
	if (str[*i] == '\0')
	{
		write(2, "Warning: Unclosed quotes!\n", 26);
		return (0);
	}
	return (1);
}

static int	adapt_line(char *str, char **line_parsed, int *i, char **envp)
{
	if (str[*i] == '\'')
	{
		*i += 1;
		if (!single_quote(str, line_parsed, i))
			return (0);
	}
	else if (str[*i] == '"')
	{
		*i += 1;
		if (!double_quotes(str, line_parsed, i, envp))
			return (0);
	}
	else if (str[*i] == '$')
	{
		*i += 1;
		if (!check_env(str, line_parsed, i, envp))
			return (0);
	}
	return (1);
}

int	check_quotes(char *str, char **line_parsed, char **envp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || (str[i] == '$' \
		&& str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_')))
		{
			if (!adapt_line(str, line_parsed, &i, envp))
				return (0);
		}
		else
		{
			*line_parsed = str_add(*line_parsed, str[i]);
			if (!*line_parsed)
				return (0);
		}
		if (str[i])
			i++;
	}
	return (1);
}
