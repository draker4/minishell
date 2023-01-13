/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/13 17:25:32 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ------------------------------  STRUCTURE  ------------------------------- */

/* ------------------------------  PROTOTYPE   ------------------------------ */

// parsing.c
void	parse(char *str, char **envp);

// quotes and env variables
int		check_quotes(char *str, char **line_parsed, char **envp);

// parsing utils
char	*str_add(char *str, char c);

// check_env
int		check_env(char *str, char **line_parsed, int *i, char **envp);

#endif
