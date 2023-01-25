/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:19:29 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/25 15:32:45 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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
			rl_replace_line("", 0);
			rl_redisplay();
			g_exit_status = 1;
		}
		else
		{
			printf("\n");
			g_exit_status = 130;
		}
	}
	if (sig == SIGQUIT && pid != -1)
	{
		g_exit_status = 131;
		printf("Quit: 3\n");
	}
}
