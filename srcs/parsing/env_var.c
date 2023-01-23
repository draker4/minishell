/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:09:09 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/23 16:21:40 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_env(char *str, char **word_parsed)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		*word_parsed = str_add(*word_parsed, str[i++]);
		if (!*word_parsed)
			return (0);
	}
	return (1);
}

int	check_env(char *str, char **word_parsed, int *i)
{
	int		save;
	char	*var;

	if (ft_isdigit(str[*i]))
		return (1);
	if (str[*i] == '{')
		*i += 1;
	save = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	var = create_copy(str, save, *i);
	if (!var)
		return (0);
	if (str[*i] == '}')
		*i += 1;
	*i -= 1;
	if (!add_env(getenv(var), word_parsed))
		return (free(var), 0);
	free(var);
	return (1);
}
