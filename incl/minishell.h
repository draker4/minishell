/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/18 20:01:38 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERROR_ARG "Please don't enter any argument!\n"
/* -----------------------------  ENUMERATION  ----------------------------- */

enum	e_type
{
	always,
	and,
	or,
};

/* ------------------------------  STRUCTURE  ------------------------------- */

// structure used for saving everything from minishell
typedef struct s_minishell
{
	char				**path;
	char				**envp;
	struct s_bracket	*bracket;
}	t_minishell;

// structure saving each steps separated by && or || or parenthesis 
// on the read line
typedef struct s_bracket
{
	char				*str;
	char				**path;
	char				**words;
	int					prev_exit;
	int					standin;
	int					standout;
	int					standerror;
	enum e_type			type;
	struct s_bracket	*next;
	struct s_bracket	*child;
	struct s_bracket	*pipe;
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

// check line
int			check_line(char *str);

// parsing.c
int			parse(char *str, t_bracket **bracket, char **envp);

// quotes
int			parse_quotes_env(char *str, char **line_parsed, char **envp);

// parsing utils
char		*str_add(char *str, char c);
void		initialize_data(t_data *data, char*str);
char		*create_copy(t_data *data, int remove);
int			init_minishell(t_minishell *minishell, char **envp);
int			has_pipe_child(t_bracket **bracket);

// search character
int			is_in_quote(char *str, int index);
int			is_last_bracket(char *str, int i);
int			has_and_or_symbols(char *str);
int			has_pipe_symbol(char *str);
int			is_in_bracket(char *str, int index);

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
t_bracket	*last_bracket(t_bracket *bracket);

// create bracket list
int			create_brackets(char *str, t_bracket **bracket);
int			create_bracket_pipe(char *str, t_bracket **bracket);

// find bracket
int			find_remove(t_data *data);
void		move_end_bracket(t_data *data);

// add bracket and, or, pipe
int			add_bracket_and(t_data *data, t_bracket **bracket, int *remove);
int			add_bracket_or(t_data *data, t_bracket **bracket, int *remove);
int			add_bracket_last(t_data *data, t_bracket **bracket, int *remove);
int			add_bracket_pipe(t_data *data, t_bracket **bracket, int *remove);
int			add_bracket_last_pipe(t_data *data, \
t_bracket **bracket, int *remove);

// free utils
void		free_split(char **split);

// execute brackets
void		exec_brackets(t_minishell *minishell);

// split words
char		**split_not_quotes(char *str);





void	print_bracket(t_bracket *bracket, int what);
#endif
