/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/15 12:33:56 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/* -----------------------------  ENUMERATION  ----------------------------- */

enum	e_type
{
	always,
	and,
	or,
};

/* ------------------------------  STRUCTURE  ------------------------------- */

// structure used for the parsing
// typedef struct s_parsing
// {
// 	char	**path;
// 	char	*line;
// }	t_parsing;

// structure saving each steps separated by && or || or parenthesis 
// on the read line
typedef struct s_bracket
{
	char				*str;
	int					prev_exit;
	enum e_type			type;
	struct s_bracket	*next;
}	t_bracket;

// structure used to create the bracket list defined above
typedef struct s_data
{
	char		*str;
	int			i;
	int			save;
	enum e_type	type;
}	t_data;

/* ------------------------------  PROTOTYPE   ------------------------------ */

// parsing.c
void		parse(char *str, char **envp, t_bracket **bfracket);

// quotes
int			parse_quotes(char *str, char **line_parsed, char **envp);

// parsing utils
char		*str_add(char *str, char c);
void		initialize_data(t_data *data, char*str);
char		*create_copy(t_data *data);
int			is_in_quote(char *str, int index);
int			is_last_bracket(char *str, int i);

// check around parenthesis
int			check_around_parenthesis(char *str);

// check and (&&), or (||) symbols
int			check_and_or(char *str);

// check redirections (< and > symbols)
int			check_redirections(char *str);

// get path variable
char		**get_path(char **envp);

// environment variables
int			check_env(char *str, char **line_parsed, int *i, char **envp);

// bracket list utils
t_bracket	*new_bracket(char *str, enum e_type type);
void		bracket_clear_data(t_bracket **bracket);
void		bracket_add_back(t_bracket **bracket, t_bracket *new);

// create bracket list
int			create_brackets(char *str, t_bracket **step);

#endif
