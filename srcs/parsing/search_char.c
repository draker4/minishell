/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:12:47 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/19 17:15:07 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
