/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:51:38 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 18:14:43 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

// void	print_exec(t_exec *exec)
// {
// 	t_exec		*current;
// 	t_input		*input;
// 	t_output	*output;
// 	int			i;

// 	current = exec;
// 	while (current)
// 	{
// 		printf("current = %s\n", current->str);
// 		// i = 0;
// 		// while (current->words[i])
// 		// 	printf("detail current = %s et words = %s\n", current->str, current->words[i++]);
// 		input = current->input;
// 		while (input)
// 		{
// 			printf("detail input = %s et type = %u\n", input->str, input->in);
// 			input = input->next;
// 		}
// 		printf("\n");
// 		output = current->output;
// 		while (output)
// 		{
// 			printf("detail output = %s et type = %u\n", output->str, output->out);
// 			output = output->next;
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
	char	*line;
	t_exec	*exec;
	int		check;

	exec = NULL;
	if (data->modify_env)
		if (update_envp(data) || get_path(data))
			return (FAIL);
	line = readline("minishell > ");
	check = check_line(line);
	if (check > 0)
	{
		if (parse(line, &exec, data))
			execute(exec);
	}
	free_all(line, &exec);
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
	return (0);
}
