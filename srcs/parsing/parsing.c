/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:16:15 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 14:52:36 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_word_quotes(char *str, char **envp)
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

static int	parse_words(t_exec **exec)
{
	char	**split_words;
	t_exec	*current;

	current = *exec;
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

static int	find_function(t_exec **exec)
{
	t_exec	*current;

	current = *exec;
	while (current)
	{
		if (current->arg && current->arg[0])
		{
			current->function = ft_strdup(current->arg[0]);
			if (!delete_slash_symbol(current, current->arg[0]))
				return (0);
		}
		else
			current->function = NULL;
		current = current->next;
	}
	return (1);
}

int	parse(char *str, t_exec **exec, t_data *data)
{
	if (!create_exec(str, exec, data) || !parse_words(exec)
		|| !find_redirections(exec) || !find_delimiter(exec)
		|| !parse_star(exec) || !change_env(exec)
		|| !parse_new_words(exec) || !find_function(exec)
		|| !change_exit_status(exec) || !parse_quotes(exec)
		|| !create_path_cmd(exec))
		return (0);
	return (1);
}
