/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:16:15 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/13 17:10:19 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space_tab(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32 && str[i] != 9)
			return (1);
		i++;
	}
	return (0);
}

void	parse(char *str, char **envp)
{
	char	*line_parsed;

	if (!str || !*str || !is_space_tab(str))
		return ;
	add_history(str);
	line_parsed = malloc(sizeof(char));
	if (!line_parsed)
	{
		perror("Error: ");
		return ;
	}
	*line_parsed = '\0';
	if (!check_quotes(str, &line_parsed, envp))
	{
		free(line_parsed);
		return ;
	}
	printf("fin %s\n", line_parsed);
	free(line_parsed);
}
