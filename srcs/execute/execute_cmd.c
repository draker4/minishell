/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:49:55 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/24 16:52:46 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_exec *exec)
{
	if (!ft_strncmp(exec->function, "cd", 3))
		return (ft_cd(exec));
	else if (!ft_strncmp(exec->function, "echo", 5))
		return (ft_echo(exec));
	else if (!ft_strncmp(exec->function, "env", 4))
		return (ft_env(exec));
	else if (!ft_strncmp(exec->function, "exit", 6))
		return (ft_exit(exec));
	else if (!ft_strncmp(exec->function, "export", 7))
		return (ft_export(exec));
	else if (!ft_strncmp(exec->function, "pwd", 4))
		return (ft_pwd(exec));
	else if (!ft_strncmp(exec->function, "unset", 6))
		return (ft_unset(exec));
	write(2, "Builtin not found\n", 18);
}

void	execute_commande(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->function == NULL)
		exit(1);
	if (exec->cmd == builtin)
		return (execute_builtin(exec));
	if (ft_strchr(exec->function, '/'))
		execve(exec->function, exec->arg, exec->data->envp);
	else
	{
		while (exec->cmd_path[i])
		{
			if (!access(exec->cmd_path[i], F_OK))
				execve(exec->cmd_path[i], exec->arg, exec->data->envp);
			i++;
		}
	}
	perror("Execute_commande - commande introuvable");
	exit (1);
}

void	execute(t_exec *exec)
{
	if (!exec)
		return ;
	exec->save_stdin = dup(STDIN_FILENO);
	exec->save_stdout = dup(STDOUT_FILENO);
	if (exec->save_stdin == -1 || exec->save_stdout == -1)
		return (perror("Execute - Dup"));
	if (!exec->next)
		handle_cmd(exec);
	else
		handle_cmd_list(exec);
	if (dup2(exec->save_stdin, STDIN_FILENO) == -1 || \
	dup2(exec->save_stdout, STDOUT_FILENO) == -1)
		return (perror("Execute - Dup2"));
}
