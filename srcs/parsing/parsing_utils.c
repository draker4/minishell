/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:18:57 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/18 19:55:28 by bperriol         ###   ########lyon.fr   */
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

void	initialize_data(t_data *data, char*str)
{
	data->i = 0;
	data->save = 0;
	data->str = str;
	data->type = always;
}

char	*create_copy(t_data *data, int remove)
{
	char	*copy;
	int		less_char;

	less_char = 1;
	if (remove != -1)
		less_char = 0;
	copy = malloc(sizeof(char) * (data->i - data->save + less_char));
	if (!copy)
	{
		write(2, "Malloc function error!\n", 23);
		return (0);
	}
	copy[0] = '\0';
	while (data->save != data->i)
	{
		if (data->save != remove)
			copy = str_add(copy, data->str[data->save]);
		if (!copy)
			return (0);
		data->save += 1;
	}
	return (copy);
}

int	init_minishell(t_minishell *minishell, char **envp)
{
	char	**path;

	path = get_path(envp);
	if (envp[0] && !path)
		return (0);
	minishell->path = path;
	minishell->bracket = NULL;
	minishell->envp = envp;
	return (1);
}

int	has_pipe_child(t_bracket **bracket)
{
	int	index_pipe;
	int	index_and_or;

	index_pipe = has_pipe_symbol((*bracket)->str);
	index_and_or = has_and_or_symbols((*bracket)->str);
	if ((index_pipe != -1 && index_and_or == -1) || \
	(index_pipe != -1 && index_and_or != -1 && index_pipe < index_and_or))
	{
		if (!create_bracket_pipe((*bracket)->str, &(*bracket)->pipe))
			return (0);
	}
	else if ((index_pipe == -1 && index_and_or != -1) || \
	(index_pipe != -1 && index_and_or != -1 && index_and_or < index_pipe))
	{
		if (!create_brackets((*bracket)->str, &(*bracket)->child))
			return (0);
	}
	return (1);
}
