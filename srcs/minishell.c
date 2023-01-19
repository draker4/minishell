/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:51:38 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/19 20:11:13 by bperriol         ###   ########lyon.fr   */
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
		i = 0;
		while (current->arg[i])
			printf("detail arg = %s\n", current->arg[i++]);
		printf("\n");
		printf("detail function = %s\n", current->function);
		printf("\n");
		current = current->next;
	}
}

static void	read_line(t_data *data)
{
	char	*line;
	t_exec	*exec;

	exec = NULL;
	line = readline("minishell > ");
	if (check_line(line))
	{
		parse(line, &exec, data);
		print_exec(exec);
	}
	free(line);
	exec_clear_data(&exec);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	// int		boucle = 1;

	(void) argv;
	if (argc != 1)
		return (ft_putstr_color(COLOR_RED, ERROR_ARG, 2), 1);
	if (!init_data(&data, envp))
		return (1);
	while (1)
		read_line(&data);
	free_split(data.path);
	return (0);
}
