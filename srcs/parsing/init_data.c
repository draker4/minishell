/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:46:08 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/29 14:54:52 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_null(t_data *data)
{
	data->env = NULL;
	data->envp = NULL;
	data->pid = NULL;
	data->line = NULL;
	data->exec_begin = NULL;
	data->path = NULL;
}

static int	init_termios(t_data *data)
{
	tcgetattr(STDIN_FILENO, &data->term_original);
	tcgetattr(STDIN_FILENO, &data->term);
	data->term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &data->term);
	return (0);
}

int	init_data(t_data *data, char **envp)
{
	init_null(data);
	if (init_termios(data))
		return (FAIL);
	if (!copy_env(envp, data) || !which_env_add(data) || !manage_shlvl(data))
		return (FAIL);
	if (update_envp(data) || get_path(data))
		return (FAIL);
	if (sigemptyset(&data->sa.sa_mask) == -1)
		return (write(2, "Sigemptyset function error!\n", 28), FAIL);
	if (sigaddset(&data->sa.sa_mask, SIGINT) == -1 || \
	sigaddset(&data->sa.sa_mask, SIGQUIT == -1))
		return (perror("Init data - Sigaddset:"), FAIL);
	data->sa.sa_flags = 0;
	data->sa.sa_handler = &handler;
	if (sigaction(SIGINT, &data->sa, NULL) == -1 || \
	sigaction(SIGQUIT, &data->sa, NULL) == -1)
		return (perror("Init data - Sigaction"), FAIL);
	return (0);
}
