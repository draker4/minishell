/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/17 17:00:34 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

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
	int				pid_status;
	char			*cmd_path;
	char			**path;
	char			**cmd;
	pid_t			pid;
}					t_pipe;

typedef struct s_spe
{
	int				scom;
	int				dcom;
}					t_spe;

/* ------------------------------  PROTOTYPE   ------------------------------ */

char	**get_path(char **envp);

#endif
