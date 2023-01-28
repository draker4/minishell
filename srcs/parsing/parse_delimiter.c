/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:45:07 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 19:46:32 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	adapt_line_del(char *str, char **word_parsed, int *i, char **envp)
{
	if (str[*i] == '$')
	{
		*i += 1;
		if (str[*i] && (str[*i] == '"' || str[*i] == '\''))
			return (*i -= 1, 1);
		if (!check_env_quotes(str, word_parsed, i, envp))
			return (0);
	}
	return (1);
}

static int	parse_del(char *str, char **word_parsed, char **envp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && \
		(ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '{' \
		|| str[i + 1] == '"' || str[i + 1] == '\''))
		{
			if (!adapt_line_del(str, word_parsed, &i, envp))
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

char	*parse_env_del(char *str, char **envp)
{
	char	*word_parsed;

	word_parsed = malloc(sizeof(char));
	if (!word_parsed)
	{
		write(2, "Parse_env_only - Malloc\n", 24);
		return (NULL);
	}
	word_parsed[0] = '\0';
	if (!parse_del(str, &word_parsed, envp))
	{
		free(word_parsed);
		return (NULL);
	}
	return (word_parsed);
}
