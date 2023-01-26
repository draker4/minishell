/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:37:15 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/26 11:08:22 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cut_space(t_exec *current, int i, int nb_spaces)
{
	int		j;
	int		k;
	char	**new_arg;
	char	**split;

	j = 0;
	new_arg = malloc(sizeof(char *) * (size_arg(current->arg) + nb_spaces + 1));
	if (!new_arg)
		return (perror("Cut_space - Malloc"), FAIL);
	split = ft_split(current->arg[i], ' ');
	if (!split)
		return (free(new_arg), perror("Cut_space - ft_split"), FAIL);
	j = 0;
	while (current->arg[j] && j < i)
	{
		new_arg[j] = current->arg[j];
		j++;
	}
	k = 0;
	while (split[k])
		new_arg[j++] = split[k++];
	free(current->arg);
	free(current->arg[i]);
	current->arg = new_arg;
	return (free(split), 0);
}

int	parse_space(t_exec **exec)
{
	t_exec	*current;
	int		i;
	int		nb_spaces;

	current = *exec;
	while (current)
	{
		i = 0;
		while (current->arg[i])
		{
			if (i == 0 && !ft_strncmp(current->arg[0], "export", 7))
				break ;
			nb_spaces = has_space(current->arg[i]);
			if (nb_spaces)
				if (cut_space(current, i, nb_spaces))
					return (FAIL);
			i++;
		}
		current = current->next;
	}
	return (1);
}
