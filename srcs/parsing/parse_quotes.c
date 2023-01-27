/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:58:30 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/27 17:48:26 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_redir(t_exec **exec)
{
	t_redir	*current;
	char	*word_parsed;

	current = (*exec)->redir;
	while (current)
	{
		word_parsed = parse_word_quotes(current->str, \
		(*exec)->data->envp);
		if (!word_parsed)
			return (0);
		free(current->str);
		current->str = word_parsed;
		current = current->next;
	}
	return (1);
}

static int	parse_function(t_exec **exec)
{
	t_exec	*current;
	char	*word_parsed;

	current = *exec;
	while (current)
	{
		if (current->function)
		{
			word_parsed = parse_word_quotes(current->function, \
			(*exec)->data->envp);
			if (!word_parsed)
				return (0);
			free(current->function);
			current->function = word_parsed;
			is_built_in(current);
		}
		current = current->next;
	}
	return (1);
}

static int	parse_arg(t_exec **exec)
{
	t_exec	*current;
	char	*word_parsed;
	int		i;

	current = *exec;
	while (current)
	{
		i = 0;
		while (current->arg[i])
		{
			word_parsed = parse_word_quotes(current->arg[i], \
			(*exec)->data->envp);
			if (!word_parsed)
				return (0);
			free(current->arg[i]);
			current->arg[i++] = word_parsed;
		}
		current = current->next;
	}
	return (1);
}

int	parse_quotes(t_exec **exec)
{
	if (!parse_redir(exec) || !parse_arg(exec)
		|| !parse_function(exec))
		return (0);
	return (1);
}
