/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/12 11:42:22 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdio.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	*line_read;

	(void) argc;
	(void) argv;
	(void) envp;
	i = 0;
	// while (envp[i])
	// 	printf("env = %s\n", envp[i++]);
	line_read = readline("> ");
	while (line_read)
	{
		line_read = readline("> ");
		add_history(line_read);
	}
	return (0);
}
