/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/13 16:40:39 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	// int		i;
	// int		check = 3;

	(void) argc;
	(void) argv;
	// i = 0;
	// while (envp[i])
	// {
	// 	printf("env[%d] = %s\n", i, envp[i]);
	// 	i++;
	// }
	while (1)
	{
		line = readline("minishell > ");
		// write(1, "Minishell > ", 12);
		// line = get_next_line(0);
		// if (!line)
		// 	write(2, "Error \n", 7);
		parse(line, envp);
		free(line);
	}
	return (0);
}
