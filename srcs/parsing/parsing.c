/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:16:15 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/15 12:49:10 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space_tab(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32 && str[i] != 9)
			return (1);
		i++;
	}
	return (0);
}

static int	check_parenthesis(char *str)
{
	int	nb_left;
	int	nb_right;
	int	i;

	nb_left = 0;
	nb_right = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(' && !is_in_quote(str, i))
			nb_left++;
		else if (str[i] == ')' && !is_in_quote(str, i))
			nb_right++;
		i++;
	}
	if (nb_left != nb_right)
	{
		write(2, "Wrong number of parenthesis!\n", 29);
		return (0);
	}
	return (1);
}

static int	check_nb_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
		}
		if (!str[i])
		{
			write(2, "Warning: Unclosed quotes!\n", 26);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	parse_brackets(t_bracket **bracket, char **envp)
{
	t_bracket	*current;
	char		*line_parsed;

	current = *bracket;
	while (current)
	{
		line_parsed = malloc(sizeof(char));
		line_parsed[0] = '\0';
		if (!line_parsed)
		{
			write(2, "Malloc function error!\n", 23);
			bracket_clear_data(bracket);
			return (0);
		}
		if (!parse_quotes(current->str, &line_parsed, envp))
		{
			free(line_parsed);
			bracket_clear_data(bracket);
			return (0);
		}
		free(current->str);
		current->str = line_parsed;
		current = current->next;
	}
	return (1);
}

void	parse(char *str, char **envp, t_bracket **bracket)
{
	if (!str || !*str || !is_space_tab(str))
		return ;
	add_history(str);
	if (!check_nb_quotes(str) || !check_parenthesis(str) \
	|| !check_around_parenthesis(str) || !check_and_or(str) || \
	!check_redirections(str) || !create_brackets(str, bracket))
		return ;
	if (!parse_brackets(bracket, envp))
		return ;
	// while (*bracket)
	// {
	// 	printf("ici bracket = %s et enum=%d\n", 
	// 	(*bracket)->str, (*bracket)->type);
	// 	(*bracket) = (*bracket)->next;
	// }
}
