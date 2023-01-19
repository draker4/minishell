/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/19 23:18:03 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_input(t_exec *exec, t_input *input)
{
	if (input->file > 0)
		if (close (input->file))
			perror("Close_in_file - Close");
	if (input->next)
		return (close_input(exec, input->next));
}

void	close_output(t_exec *exec, t_output *output)
{
	if (output->file > 0)
		if (close (output->file))
			perror("Close_in_file - Close");
	if (output->next)
		return (close_output(exec, output->next));
}

void	close_file(t_exec *exec)
{
	if (exec->input)
		close_input(exec, exec->input);
	if (exec->output)
		close_output(exec, exec->output);
	dup2(1, STDOUT_FILENO);
}
