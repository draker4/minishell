/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptiste <baptiste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:29:27 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/27 00:54:04 by baptiste         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_new_word(t_exec *current, int i)
{
	char	*env_word;
	char	*star_word;

	env_word = parse_word_quotes(current->words[i], current->data->envp);
	if (!env_word)
		return (0);
	//printf("entree = %s\n", env_word);
	star_word = get_wildcard(env_word);
	//printf("sortie = %s\n", star_word);
	if (!star_word)
		return (free(env_word), 0);
	free(current->words[i]);
	current->words[i] = star_word;
	return (1);
}

int	parse_star(t_exec **exec)
{
	t_exec	*tmp;
	int		i;

	tmp = *exec;
	while (tmp)
	{
		i = 0;
		while (tmp->words[i])
		{
			if (has_star(tmp->words[i]))
				if (!create_new_word(tmp, i))
					return (0);
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}
