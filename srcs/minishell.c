/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:51:38 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/29 14:50:45 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static int	read_line(t_data *data)
{
	int	check;

	data->exec_begin = NULL;
	if (data->modify_env)
		if (update_envp(data) || get_path(data))
			return (FAIL);
	data->line = readline("minishell > ");
	data->term.c_lflag = data->term.c_lflag ^ ECHOCTL;
	tcsetattr(0, TCSANOW, &data->term);
	check = check_line(data->line);
	if (check > 0)
	{
		if (parse(data->line, &data->exec_begin, data))
			execute(data->exec_begin);
	}
	free_readline(data->line, &data->exec_begin);
	if (data->term.c_lflag & ECHOCTL)
		data->term.c_lflag = data->term.c_lflag ^ ECHOCTL;
	tcsetattr(0, TCSANOW, &data->term);
	return (check);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argv;
	(void) argc;
	g_exit_status = 0;
	if (RL_VERSION_MAJOR >= 8)
		rl_variable_bind("enable-bracketed-paste", "off");
	if (argc != 1)
		return (ft_putstr_color(COLOR_RED, ERROR_ARG, 2), FAIL);
	if (init_data(&data, envp))
		return (1);
	while (1)
		if (read_line(&data) == -1)
			break ;
	rl_clear_history();
	free_data(&data);
	tcsetattr(STDIN_FILENO, TCSANOW, &data.term_original);
	return (g_exit_status);
}
