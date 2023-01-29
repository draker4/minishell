/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:53:47 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/29 11:45:09 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	free_readline(char *str, t_exec **exec)
{
	if (str)
		free(str);
	str = NULL;
	exec_clear_data(exec);
}

void	free_data(t_data *data)
{
	if (data->path)
		free_split(data->path);
	if (data->envp)
		free_split(data->envp);
	if (data->env)
		env_clear_data(&data->env);
}

void	free_all(t_data *data)
{
	free_readline(data->line, &data->exec_begin);
	free_data(data);
}

unsigned char	free_exit(t_exec *exec, int nb)
{
	free_all(exec->data);
	if (exec->data->pid)
		tcsetattr(STDIN_FILENO, TCSANOW, &exec->data->term_original);
	exit(nb);
}
