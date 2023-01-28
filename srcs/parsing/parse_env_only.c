/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_only.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:55:39 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 11:07:59 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	adapt_line_var(char *str, char **word_parsed, int *i, char **envp)
{
	if (str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] && str[*i] != '\'')
			*i += 1;
		*i -= 1;
	}
	else if (str[*i] == '"')
	{
		*i += 1;
		while (str[*i] && str[*i] != '"')
			*i += 1;
		*i -= 1;
	}
	else if (str[*i] == '$')
	{
		*i += 1;
		if (!check_env(str, word_parsed, i, envp))
			return (0);
	}
	return (1);
}

int	parse_env_var(char *str, char **word_parsed, char **envp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && !is_in_quote(str, i) && \
		(ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '{'))
		{
			if (!adapt_line_var(str, word_parsed, &i, envp))
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

char	*parse_env_only(char *str, char **envp)
{
	char	*word_parsed;

	word_parsed = malloc(sizeof(char));
	if (!word_parsed)
	{
		write(2, "Malloc function error!\n", 23);
		return (NULL);
	}
	word_parsed[0] = '\0';
	if (!parse_env_var(str, &word_parsed, envp))
	{
		free(word_parsed);
		return (NULL);
	}
	return (word_parsed);
}
