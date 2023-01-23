/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 05:50:18 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/23 14:51:51 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_cmd_path(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		new[i++] = s1[j++];
	new[i++] = '/';
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

static int	join_all_path(t_exec *exec)
{
	char	**cmd_path;
	int		i;

	cmd_path = malloc(sizeof(char *) * (size_arg(exec->data->path) + 1));
	if (!cmd_path)
		return (perror("Create_path_cmd - Malloc:"), 0);
	i = 0;
	while (exec->data->path[i])
	{
		cmd_path[i] = join_cmd_path(exec->data->path[i], exec->function);
		if (!cmd_path[i++])
			return (perror("Create_path_cmd - Join_cmd_path"), 0);
	}
	cmd_path[i] = NULL;
	exec->cmd_path = cmd_path;
	return (1);
}

int	create_path_cmd(t_exec **exec)
{
	t_exec	*current;

	current = *exec;
	while (current)
	{
		if (current->function)
			if (join_all_path(current))
				return (0);
		current = current->next;
	}
	return (1);
}
