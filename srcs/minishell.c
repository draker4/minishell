/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/15 13:28:03 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_split(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**path;
	t_bracket	*bracket;
	int			boucle = 4;

	if (argc != 1)
	{
		write(2, "Please don't enter any argument!\n", 33);
		return (0);
	}
	(void) argv;
	bracket = NULL;
	path = get_path(envp);
	if (!path)
		return (0);
	while (boucle--)
	{
		line = readline("minishell > ");
		parse(line, envp, &bracket);
		free(line);
		bracket_clear_data(&bracket);
	}
	free_split(path);
	return (0);
}
