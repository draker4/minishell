/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/19 17:38:36 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <fcntl.h>

# define ERROR_ARG "Missing argument to use pipe\n"

# define INFILE 0
# define OUTFILE 1
# define FAIL 1

/* ------------------------------  STRUCTURE  ------------------------------- */

typedef struct s_pipe
{
	int				fd_pipe[2];
	int				infile;
	int				outfile;
	char			*cmd_path;
	char			**path;
	char			**cmd;
	pid_t			pid;
}					t_pipe;

/* ------------------------------  PROTOTYPE   ------------------------------ */

// strjoin with the s1 being free at the end;
char	*gnl_strjoin(char *s1, char *s2);
// get_next_line which update directly the line and handle perror
int		get_delimiter(int fd, char *line);

int		change_input(t_exec *exec, t_input input);
int		change_output(t_exec *exec, t_output output);
#endif
