/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:51:38 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 12:16:14 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exec(t_exec *exec)
{
	t_exec		*current;
	t_input		*input;
	t_output	*output;
	int			i;

	current = exec;
	while (current)
	{
		printf("current = %s\n", current->str);
		// i = 0;
		// while (current->words[i])
		// 	printf("detail current = %s et words = %s\n", current->str, current->words[i++]);
		input = current->input;
		while (input)
		{
			printf("detail input = %s et type = %u\n", input->str, input->in);
			input = input->next;
		}
		printf("\n");
		output = current->output;
		while (output)
		{
			printf("detail output = %s et type = %u\n", output->str, output->out);
			output = output->next;
		}
		printf("\n");
		if (current->arg)
		{
			i = 0;
			while (current->arg[i])
				printf("detail arg = %s\n", current->arg[i++]);
		}
		printf("\n");
		printf("detail function = %s\n", current->function);
		printf("is built in = %d\n", exec->cmd);
		printf("\n");
		current = current->next;
	}
}

static int	read_line(t_data *data)
{
	char	*line;
	t_exec	*exec;
	int		check;

	exec = NULL;
	if (get_path(data))
		return (-1);
	line = readline("minishell > ");
	data->term.c_lflag = data->term.c_lflag ^ ECHOCTL;
	if (tcsetattr(0, TCSANOW, &data->term))
		return (perror("Read_line - tcsetattr"), -1);
	check = check_line(line);
	if (check > 0)
	{
		parse(line, &exec, data);
		// print_exec(exec);
		execute(exec);
	}
	free_all(line, data, &exec);
	data->term.c_lflag = data->term.c_lflag ^ ECHOCTL;
	if (tcsetattr(0, TCSANOW, &data->term))
		return (perror("Read_line - tcsetattr"), -1);
	return (check);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argv;
	// if (RL_VERSION_MAJOR >= 8)
	// 	rl_variable_bind("enable-bracketed-paste", "off");
	if (argc != 1)
		return (ft_putstr_color(COLOR_RED, ERROR_ARG, 2), 1);
	if (init_data(&data, envp))
		return (1);
	while (1)
		if (read_line(&data) == -1)
			break ;
	rl_clear_history();
	free_split(data.envp);
	return (0);
}
