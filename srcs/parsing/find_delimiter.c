/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_delimiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:52:12 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 14:52:20 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	double_quotes_only(char *str, char **word_parsed, int *i)
{
	while (str[*i] && str[*i] != '"')
	{
		while (str[*i] && str[*i] != '"')
		{
			*word_parsed = str_add(*word_parsed, str[*i]);
			if (!*word_parsed)
				return (0);
			*i += 1;
		}
		*i += 1;
	}
	return (1);
}

static int	adapt_line_quotes(char *str, char **word_parsed, int *i)
{
	if (str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] && str[*i] != '\'')
		{
			*word_parsed = str_add(*word_parsed, str[*i]);
			if (!*word_parsed)
				return (0);
			*i += 1;
		}
		*i -= 1;
	}
	else if (str[*i] == '"')
	{
		*i += 1;
		if (!double_quotes_only(str, word_parsed, i))
			return (0);
	}
	return (1);
}

int	parse_quotes_only(char *str, char **word_parsed)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!adapt_line_quotes(str, word_parsed, &i))
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

static char	*parse_delimiter(char *str)
{
	char	*word_parsed;

	word_parsed = malloc(sizeof(char));
	if (!word_parsed)
	{
		write(2, "Malloc function error!\n", 23);
		return (NULL);
	}
	word_parsed[0] = '\0';
	if (!parse_quotes_only(str, &word_parsed))
	{
		free(word_parsed);
		return (NULL);
	}
	return (word_parsed);
}

int	find_delimiter(t_exec **exec)
{
	t_exec	*current;
	t_redir	*tmp;
	char	*str;

	current = *exec;
	while (current)
	{
		tmp = current->redir;
		while (tmp)
		{
			if (tmp->type == delimiter)
			{
				if (has_quote(tmp->str))
					tmp->modif = 1;
				str = parse_delimiter(tmp->str);
				if (!str)
					return (0);
				tmp->str = str;
			}
			tmp = tmp->next;
		}
		current = current->next;
	}
	return (1);
}
