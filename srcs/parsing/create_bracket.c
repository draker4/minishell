/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bracket.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 07:39:15 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/18 19:55:04 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	choose_which_pipe_add(t_data *data, t_bracket **bracket, \
int *remove)
{
	t_bracket	*last;

	if (data->str[data->i] == '|' && data->str[data->i + 1] && \
	data->str[data->i + 1] == '|')
		data->i += 1;
	else if (data->str[data->i] == '|' && data->str[data->i + 1] && \
	data->str[data->i + 1] != '|')
	{
		if (!add_bracket_pipe(data, bracket, remove))
			return (0);
		last = last_bracket(*bracket);
		if (!has_pipe_child(&last))
			return (0);
	}
	else if (data->str[data->i] == '(')
		move_end_bracket(data);
	return (1);
}

static int	choose_which_bracket_add(t_data *data, t_bracket **bracket, \
int *remove)
{
	t_bracket	*last;

	if (data->str[data->i] == '&' && data->str[data->i + 1] && \
	data->str[data->i + 1] == '&')
	{
		if (!add_bracket_and(data, bracket, remove))
			return (0);
		last = last_bracket(*bracket);
		if (!has_pipe_child(&last))
			return (0);
	}
	else if (data->str[data->i] == '|' && data->str[data->i + 1] && \
	data->str[data->i + 1] == '|')
	{
		if (!add_bracket_or(data, bracket, remove))
			return (0);
		last = last_bracket(*bracket);
		if (!has_pipe_child(&last))
			return (0);
	}
	else if (data->str[data->i] == '(')
		move_end_bracket(data);
	return (1);
}

int	create_brackets(char *str, t_bracket **bracket)
{
	t_data		data;
	int			remove;

	initialize_data(&data, str);
	remove = find_remove(&data);
	while (str[data.i])
	{
		if (!is_in_quote(str, data.i))
		{
			if (!choose_which_bracket_add(&data, bracket, &remove))
				return (0);
		}
		if (str[data.i])
			data.i += 1;
	}
	if (!add_bracket_last(&data, bracket, &remove))
		return (0);
	return (1);
}

int	create_bracket_pipe(char *str, t_bracket **bracket)
{
	t_data		data;
	int			remove;

	initialize_data(&data, str);
	remove = find_remove(&data);
	while (str[data.i])
	{
		if (!is_in_quote(str, data.i))
			if (!choose_which_pipe_add(&data, bracket, &remove))
				return (0);
		if (str[data.i])
			data.i += 1;
	}
	if (!add_bracket_last_pipe(&data, bracket, &remove))
		return (0);
	return (1);
}
