/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptiste <baptiste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/20 15:38:53 by baptiste         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_input(t_exec *exec, t_input *input)
{
	if (input->file > 0)
		if (close (input->file))
			perror("Close_in_file - Close");
	if (input->in == delimiter)
		unlink(".delimiter_tmp");
	if (input->next)
		return (close_input(exec, input->next));
}

void	close_output(t_exec *exec, t_output *output)
{
	if (output->file > 0)
	{
		if (close (output->file))
			perror("Close_in_file - Close");
	}
	if (output->next)
		return (close_output(exec, output->next));
}

void	close_file(t_exec *exec)
{
	if (exec->input)
		close_input(exec, exec->input);
	if (exec->output)
		close_output(exec, exec->output);
}
