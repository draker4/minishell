/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:19:29 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/26 18:31:05 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	handle_sigint(pid_t pid)
{
	if (pid == -1)
	{
		printf("\n");
		if (g_exit_status != -1)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_exit_status = 1;
	}
	else
	{
		printf("\n");
		g_exit_status = 130;
	}
}

void	handler(int sig)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, 0);
	if (sig == SIGINT)
		handle_sigint(pid);
	if (sig == SIGQUIT && pid != -1)
	{
		g_exit_status = 131;
		printf("Quit: 3\n");
	}
}
