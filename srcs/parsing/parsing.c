/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:16:15 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/16 12:02:05 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	parse_brackets(t_bracket **bracket, char **envp)
// {
// 	t_bracket	*current;
// 	char		*line_parsed;

// 	current = *bracket;
// 	while (current)
// 	{
// 		line_parsed = malloc(sizeof(char));
// 		line_parsed[0] = '\0';
// 		if (!line_parsed)
// 		{
// 			write(2, "Malloc function error!\n", 23);
// 			bracket_clear_data(bracket);
// 			return (0);
// 		}
// 		if (!parse_quotes(current->str, &line_parsed, envp))
// 		{
// 			free(line_parsed);
// 			bracket_clear_data(bracket);
// 			return (0);
// 		}
// 		free(current->str);
// 		current->str = line_parsed;
// 		current = current->next;
// 	}
// 	return (1);
// }

int	parse(char *str, t_bracket **bracket)
{
	t_bracket	*current;

	if (!create_brackets(str, bracket))
		return (0);
	current = *bracket;
	while (current)
	{
		if (has_and_or_symbols(current->str))
		{
			if (!parse(current->str, &current->child))
			{
				bracket_clear_data(bracket);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}
