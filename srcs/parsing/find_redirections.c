/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:27:05 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 12:03:41 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_current(char **current_arg, char *copy)
{
	char	**new_arg;
	int		i;

	i = -1;
	new_arg = malloc(sizeof(char *) * (size_arg(current_arg) + 2));
	if (!new_arg)
		return (perror("Add_current - Malloc:"), NULL);
	while (current_arg[++i])
		new_arg[i] = current_arg[i];
	free(current_arg);
	new_arg[i++] = copy;
	new_arg[i] = NULL;
	return (new_arg);
}

static int	add_arg(t_exec *current, char *str)
{
	char	**new_arg;
	char	*copy;
	int		i;

	i = -1;
	copy = ft_strdup(str);
	if (!copy)
		return (perror("Add_arg - ft_strdup:"), 0);
	if (current->arg)
	{
		new_arg = add_current(current->arg, copy);
		if (!new_arg)
			return (perror("Add_arg - add_current:"), 0);
	}
	else
	{
		new_arg = malloc(sizeof(char *) * 2);
		if (!new_arg)
			return (perror("Add_arg - Malloc:"), 0);
		new_arg[++i] = str;
		new_arg[++i] = NULL;
	}
	current->arg = new_arg;
	return (1);
}

static int	create_in_out_arg(t_exec *current)
{
	int	i;

	i = 0;
	while (current->words[i])
	{
		if (!ft_strncmp(current->words[i], "<", 1) && current->words[i + 1])
		{
			if (!create_input(current, &i))
				return (0);
		}
		else if (!ft_strncmp(current->words[i], ">", 1) \
		&& current->words[i + 1])
		{
			if (!create_output(current, &i))
				return (0);
		}
		else
		{
			if (!add_arg(current, current->words[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	find_redirections(t_exec **exec)
{
	t_exec	*current;

	current = *exec;
	while (current)
	{
		if (!create_in_out_arg(current))
			return (0);
		current = current->next;
	}
	return (1);
}
