/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:19:29 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/23 09:28:55 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, 0);
	if (sig == SIGINT)
	{
		if (pid == -1)
		{
			printf("\n");
			rl_on_new_line();
			//rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			printf("\n");
	}
}
