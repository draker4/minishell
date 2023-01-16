/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/16 16:52:00 by bboisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>

# define ERROR_ARG "Missing argument to use pipe\n"

/* ------------------------------  STRUCTURE  ------------------------------- */

typedef struct s_pipe
{
	int				fd[2];
}					t_pipe;

/* ------------------------------  PROTOTYPE   ------------------------------ */

	/* --------- ft_arg_list.c -------- */

#endif
