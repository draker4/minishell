/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:52:38 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/15 10:58:10 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_output(char *str, int *i)
{
	if (!str[*i + 1])
	{
		write(2, "Wrong '>' symbol!\n", 18);
		return (0);
	}
	if (str[*i + 1] == '>')
		*i += 1;
	*i += 1;
	while (str[*i] && str[*i] == ' ')
		*i += 1;
	if (!str[*i] || str[*i] == '|' || str[*i] == '&' \
	|| str[*i] == '<' || str[*i] == '>')
	{
		write(2, "Wrong '>' symbol!\n", 18);
		return (0);
	}
	return (1);
}

static int	check_input(char *str, int *i)
{
	if (!str[*i + 1])
	{
		write(2, "Wrong '<' symbol!\n", 18);
		return (0);
	}
	if (str[*i + 1] == '<')
		*i += 1;
	*i += 1;
	while (str[*i] && str[*i] == ' ')
		*i += 1;
	if (!str[*i] || str[*i] == '|' || str[*i] == '&' \
	|| str[*i] == '<' || str[*i] == '>')
	{
		write(2, "Wrong '>' symbol!\n", 18);
		return (0);
	}
	return (1);
}

int	check_redirections(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && !is_in_quote(str, i))
		{
			if (!check_output(str, &i))
				return (0);
		}
		else if (str[i] == '<' && !is_in_quote(str, i))
		{
			if (!check_input(str, &i))
				return (0);
		}
		if (str[i])
			i++;
	}
	return (1);
}
