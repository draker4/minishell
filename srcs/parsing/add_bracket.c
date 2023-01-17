/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_bracket.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:34:30 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/17 17:33:03 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_bracket_and(t_data *data, t_bracket **bracket, int *remove)
{
	t_bracket	*new;
	char		*copy;

	copy = create_copy(data, *remove);
	if (!copy)
	{
		bracket_clear_data(bracket);
		return (0);
	}
	data->save = data->i + 2;
	data->i = data->i + 2;
	new = new_bracket(copy, data->type);
	if (!new)
	{
		free(copy);
		bracket_clear_data(bracket);
		return (0);
	}
	bracket_add_back(bracket, new);
	data->type = and;
	*remove = find_remove(data);
	data->i = data->i - 1;
	return (1);
}

int	add_bracket_or(t_data *data, t_bracket **bracket, int *remove)
{
	t_bracket	*new;
	char		*copy;

	copy = create_copy(data, *remove);
	if (!copy)
	{
		bracket_clear_data(bracket);
		return (0);
	}
	data->save = data->i + 2;
	data->i = data->i + 2;
	new = new_bracket(copy, data->type);
	if (!new)
	{
		free(copy);
		bracket_clear_data(bracket);
		return (0);
	}
	bracket_add_back(bracket, new);
	data->type = or;
	*remove = find_remove(data);
	data->i = data->i - 1;
	return (1);
}

int	add_bracket_last(t_data *data, t_bracket **bracket, int *remove)
{
	t_bracket	*new;
	char		*copy;

	copy = create_copy(data, *remove);
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
	if (has_pipe_symbol(new->str))
		if (!create_bracket_pipe(new->str, &new->pipe))
			return (0);
	return (1);
}

int	add_bracket_pipe(t_data *data, t_bracket **bracket, int *remove)
{
	t_bracket	*new;
	char		*copy;

	copy = create_copy(data, *remove);
	if (!copy)
	{
		bracket_clear_data(bracket);
		return (0);
	}
	data->i = data->i + 1;
	data->save = data->i;
	new = new_bracket(copy, data->type);
	if (!new)
	{
		free(copy);
		bracket_clear_data(bracket);
		return (0);
	}
	bracket_add_back(bracket, new);
	if (has_and_or_symbols(new->str))
		if (!create_brackets(new->str, &new->child))
			return (0);
	*remove = find_remove(data);
	data->i = data->i - 1;
	return (1);
}

int	add_bracket_last_pipe(t_data *data, t_bracket **bracket, int *remove)
{
	t_bracket	*new;
	char		*copy;

	copy = create_copy(data, *remove);
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
	if (has_and_or_symbols(new->str))
		if (!create_brackets(new->str, &new->child))
			return (0);
	return (1);
}
