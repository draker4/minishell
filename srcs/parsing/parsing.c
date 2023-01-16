/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:16:15 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/16 16:54:46 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_word_quotes(char *str, char **envp)
{
	char	*word_parsed;

	word_parsed = malloc(sizeof(char));
	if (!word_parsed)
	{
		write(2, "Malloc function error!\n", 23);
		return (NULL);
	}
	word_parsed[0] = '\0';
	if (!parse_quotes_env(str, &word_parsed, envp))
	{
		free(word_parsed);
		return (NULL);
	}
	return (word_parsed);
}

static int	parse_quotes(t_bracket **bracket, char **envp)
{
	t_bracket	*current;
	char		*word_parsed;
	int			i;

	current = *bracket;
	while (current)
	{
		i = 0;
		while (current->words[i])
		{
			word_parsed = parse_word_quotes(current->words[i], envp);
			if (!word_parsed)
				return (0);
			free(current->words[i]);
			current->words[i++] = word_parsed;
		}
		current = current->next;
	}
	return (1);
}

static int	parse_words(t_bracket **bracket)
{
	char		**split_words;
	t_bracket	*current;

	current = *bracket;
	while (current)
	{
		split_words = split_not_quotes(current->str);
		if (!split_words)
			return (0);
		current->words = split_words;
		current = current->next;
	}
	return (1);
}

int	parse(char *str, t_bracket **bracket, char **envp)
{
	t_bracket	*current;

	if (!create_brackets(str, bracket))
		return (0);
	current = *bracket;
	while (current)
	{
		if (has_and_or_symbols(current->str))
		{
			if (!parse(current->str, &current->child, envp))
				return (0);
		}
		current = current->next;
	}
	if (!parse_words(bracket) || !parse_quotes(bracket, envp))
		return (0);
	return (1);
}
