/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:29:27 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/29 11:39:31 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_star(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' && !is_in_quote(str, i, 0))
			return (1);
		i++;
	}
	return (0);
}

static int	create_new_redir(t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		if (current->type != delimiter && has_star(current->str) != -1)
			current->str = get_wildcard(current->str);
		current = current->next;
	}
	return (1);
}

// static int	delete_star(t_exec *exec, int i, int index_star)
// {
// 	int		j;
// 	char	*word_parsed;

// 	if (index_star != ft_strlen(exec->arg[i]))
// 		return (1);
// 	word_parsed = ft_strdup("\0");
// 	if (!word_parsed)
// 		return (write(2, "Delete star - ft_strdup\n", 24), 0);
// 	word_parsed[0] = '\0';
// 	j = 0;
// 	while (exec->arg[i][j])
// 	{
// 		if (exec->arg[i][j] != '*')
// 		{
// 			word_parsed = str_add(word_parsed, exec->arg[i][j]);
// 			if (!word_parsed)
// 				return (perror("Delete star - Str add"), 0);
// 		}
// 		j++;
// 	}
// 	free(exec->arg[i]);
// 	exec->arg[i] = word_parsed;
// 	return (1);
// }

// static int	check_star(t_exec *exec, int i, int index_star)
// {
// 	char	*copy;
     
// 	copy = ft_strdup(exec->arg[i]);
// 	if (!copy)
// 		return (perror("Parse_star - ft_strdup"), 0);
// 	exec->arg[i] = get_wildcard(exec->arg[i]);
// 	if (!ft_strncmp(copy, exec->arg[i], ft_strlen(copy) + 1)
// 	&& (ft_strncmp(exec->arg[0], "export", 8)
// 	&& ft_strncmp(exec->arg[0], "unset", 7)))
// 		if (!delete_star(exec, i, index_star))
// 			return (free(copy), 0);
// 	free(copy);
// 	return (1);
// }

int	parse_star(t_exec **exec)
{
	t_exec	*tmp;
	int		i;

	tmp = *exec;
	while (tmp)
	{
		i = 0;
		while (tmp->arg && tmp->arg[i])
		{
			if (has_star(tmp->arg[i]))
				tmp->arg[i] = get_wildcard(tmp->arg[i]);
			i++;
		}
		if (!create_new_redir(tmp->redir))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
