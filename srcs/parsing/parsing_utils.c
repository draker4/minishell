/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:18:57 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/15 12:33:37 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_add(char *str, char c)
{
	int		i;
	char	*copy;

	if (!str)
		return (NULL);
	copy = malloc(sizeof(char) * ((int)ft_strlen(str) + 2));
	if (!copy)
	{
		free(str);
		write(2, "Malloc function error!\n", 23);
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i++] = c;
	copy[i] = '\0';
	free(str);
	return (copy);
}

int	is_in_quote(char *str, int index)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				if (i++ == index)
					return (1);
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				if (i++ == index)
					return (1);
		}
		if (str[i])
			i++;
		else
			return (1);
	}
	return (0);
}

void	initialize_data(t_data *data, char*str)
{
	data->i = 0;
	data->save = 0;
	data->str = str;
	data->type = always;
}

char	*create_copy(t_data *data)
{
	char	*copy;

	copy = malloc(sizeof(char) * (data->i - data->save + 1));
	if (!copy)
		return (0);
	copy[0] = '\0';
	if (!copy)
	{
		write(2, "Malloc function error!\n", 23);
		return (0);
	}
	while (data->save != data->i)
	{
		copy = str_add(copy, data->str[data->save]);
		if (!copy)
			return (0);
		data->save += 1;
	}
	copy[data->save] = '\0';
	return (copy);
}

int	is_last_bracket(char *str, int i)
{
	i++;
	while (str[i])
	{
		if (str[i] == ')')
			return (0);
		i++;
	}
	return (1);
}
