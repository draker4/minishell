/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:12:49 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/18 19:13:10 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_remove(t_data *data)
{
	int	left_bracket;
	int	right_bracket;

	while (data->str[data->i] && data->str[data->i] == ' ')
		data->i += 1;
	if (data->str[data->i] == '(')
	{
		data->i += 1;
		data->save = data->i;
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
		return (data->i - 1);
	}
	return (-1);
}

void	move_end_bracket(t_data *data)
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
