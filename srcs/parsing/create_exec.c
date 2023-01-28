/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 07:39:15 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/28 14:41:13 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parse	*init_parse(char *str)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
	{
		perror("Init_parse - parse:");
		return (0);
	}
	parse->i = 0;
	parse->save = 0;
	parse->str = str;
	return (parse);
}

static int	add_exec(t_exec **exec, t_parse *parse, t_data *data, int nb)
{
	t_exec	*new;
	char	*copy;

	copy = create_copy(parse->str, parse->save, parse->i);
	if (!copy)
		return (0);
	new = new_exec(copy, data, nb);
	if (!new)
	{
		free(copy);
		return (0);
	}
	exec_add_back(exec, new);
	return (1);
}

int	create_exec(char *str, t_exec **exec, t_data *data)
{
	int		nb;
	t_parse	*parse;

	parse = init_parse(str);
	nb = 0;
	while (str[parse->i])
	{
		if (str[parse->i] == '|' && !is_in_quote(str, parse->i, 0))
		{
			if (!add_exec(exec, parse, data, nb))
				return (free(parse), 0);
			parse->save = parse->i + 1;
			nb++;
		}
		if (str[parse->i])
			parse->i += 1;
	}
	if (!add_exec(exec, parse, data, nb))
		return (free(parse), 0);
	free(parse);
	return (1);
}
