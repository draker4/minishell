/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:27:17 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/29 12:31:33 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_new_word(char **old_words, char **split)
{
	int		i;
	int		j;
	char	**new_words;

	i = 0;
	new_words = malloc(sizeof(char *) * \
	(size_arg(old_words) + size_arg(split) + 1));
	if (!new_words)
		return (free_split(split), free_split(old_words), NULL);
	while (old_words && old_words[i])
	{
		new_words[i] = old_words[i];
		i++;
	}
	j = 0;
	while (split && split[j])
		new_words[i++] = split[j++];
	new_words[i] = NULL;
	free(old_words);
	free(split);
	return (new_words);
}

int	parse_new_words(t_exec **exec)
{
	t_exec	*current;
	char	**split;
	char	**new_words;
	int		i;

	current = *exec;
	while (current)
	{
		i = 0;
		new_words = malloc(sizeof(char *));
		new_words[0] = NULL;
		while (current->arg && current->arg[i])
		{
			split = split_spaces(current->arg[i++]);
			if (!split)
				return (free_split(new_words), 0);
			new_words = add_new_word(new_words, split);
			if (!new_words)
				return (0);
		}
		free_split(current->arg);
		current->arg = new_words;
		current = current->next;
	}
	return (1);
}
