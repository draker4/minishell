/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:51:38 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/27 11:45:02 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

// void	print_exec(t_exec *exec)
// {
// 	t_exec		*current;
// 	t_redir		*redir;
// 	int			i;

// 	current = exec;
// 	while (current)
// 	{
// 		printf("current = %s\n", current->str);
// 		// i = 0;
// 		// while (current->words[i])
// 		// 	printf("detail current = %s et words = %s\n", current->str, current->words[i++]);
// 		redir = current->redir;
// 		while (redir)
// 		{
// 			printf("detail input = %s et type = %u\n", redir->str, redir->type);
// 			redir = redir->next;
// 		}
// 		printf("\n");
// 		if (current->arg)
// 		{
// 			i = 0;
// 			while (current->arg[i])
// 				printf("detail arg = %s\n", current->arg[i++]);
// 		}
// 		printf("\n");
// 		printf("detail function = %s\n", current->function);
// 		printf("is built in = %d\n", exec->cmd);
// 		printf("\n");
// 		current = current->next;
// 	}
// }

static int	read_line(t_data *data)
{
	int	check;

	data->exec_begin = NULL;
	if (data->modify_env)
		if (update_envp(data) || get_path(data))
			return (FAIL);
	data->line = readline("minishell > ");
	data->term.c_lflag = data->term.c_lflag ^ ECHOCTL;
	if (tcsetattr(0, TCSANOW, &data->term))
		return (perror("Read_line - tcsetattr"), -1);
	check = check_line(data->line);
	if (check > 0)
	{
		if (parse(data->line, &data->exec_begin, data))
			execute(data->exec_begin);
	}
	else
		g_exit_status = 0;
	free_readline(data->line, &data->exec_begin);
	if (data->term.c_lflag & ECHOCTL)
		data->term.c_lflag = data->term.c_lflag ^ ECHOCTL;
	if (tcsetattr(0, TCSANOW, &data->term))
		return (perror("Read_line - tcsetattr"), -1);
	return (check);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argv;
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
	if (tcsetattr(STDIN_FILENO, TCSANOW, &data.term_original))
		return (perror("Main - tcsetattr"), FAIL);
	return (0);
}
