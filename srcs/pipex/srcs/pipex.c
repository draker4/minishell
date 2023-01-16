/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:14 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/16 18:08:43 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	(void)env;
	if (argc < 5)
		return (ft_putstr_color(COLOR_RED, ERROR_ARG, 2), 1);
	if (access(argv[1], R_OK))
		perror("Error");
	return (0);
//int pipe_fd[2]

// pipe(pipe_fd);

// if (fork() == 0)
// {
// 	dup2(pipe_fd[1], STDOUT_FILENO);
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// 	execve("/bin/cat", ["cat", "ARG", NULL], envp);
// }

// dup2(pipe_fd[0], STDIN_FILENO);

// close(pipe_fd[0]);
// close(pipe_fd[1]);
}
