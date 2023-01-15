/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bracket.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 07:39:15 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/15 13:17:00 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_bracket_and(t_data *data, t_bracket **bracket)
{
	t_bracket	*new;
	char		*copy;

	copy = create_copy(data);
	if (!copy)
	{
		bracket_clear_data(bracket);
		return (0);
	}
	data->save = data->i + 2;
	data->i = data->i + 1;
	new = new_bracket(copy, data->type);
	if (!new)
	{
		free(copy);
		bracket_clear_data(bracket);
		return (0);
	}
	bracket_add_back(bracket, new);
	data->type = and;
	return (1);
}

static int	add_bracket_or(t_data *data, t_bracket **bracket)
{
	t_bracket	*new;
	char		*copy;

	copy = create_copy(data);
	if (!copy)
	{
		bracket_clear_data(bracket);
		return (0);
	}
	data->save = data->i + 2;
	data->i = data->i + 1;
	new = new_bracket(copy, data->type);
	if (!new)
	{
		free(copy);
		bracket_clear_data(bracket);
		return (0);
	}
	bracket_add_back(bracket, new);
	data->type = or;
	return (1);
}

static void	move_end_bracket(t_data *data)
{
	int	left_bracket;
	int	right_bracket;

	data->i += 1;
	left_bracket = 1;
	right_bracket = 0;
	while (data->str[data->i] && left_bracket != right_bracket)
	{
		if (data->str[data->i] == '(')
			left_bracket++;
		if (data->str[data->i] == ')')
			right_bracket++;
		data->i += 1;
	}
}

static int	add_bracket_last(t_data *data, t_bracket **bracket)
{
	t_bracket	*new;
	char		*copy;

	copy = create_copy(data);
	if (!copy)
	{
		bracket_clear_data(bracket);
		return (0);
	}
	new = new_bracket(copy, data->type);
	if (!new)
	{
		free(copy);
		bracket_clear_data(bracket);
		return (0);
	}
	bracket_add_back(bracket, new);
	return (1);
}

int	create_brackets(char *str, t_bracket **bracket)
{
	t_data		data;

	initialize_data(&data, str);
	while (str[data.i])
	{
		if (!is_in_quote(str, data.i))
		{
			if (str[data.i] == '&' && str[data.i + 1] && str[data.i + 1] == '&')
				if (!add_bracket_and(&data, bracket))
					return (0);
			if (str[data.i] == '|' && str[data.i + 1] && str[data.i + 1] == '|')
				if (!add_bracket_or(&data, bracket))
					return (0);
			if (str[data.i] == '(')
				move_end_bracket(&data);
		}
		if (str[data.i])
			data.i += 1;
	}
	if (!add_bracket_last(&data, bracket))
		return (0);
	return (1);
}
