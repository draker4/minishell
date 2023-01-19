/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/19 17:39:13 by bperriol         ###   ########lyon.fr   */
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

enum e_in
{
	in_file,
	delimiter,
};

enum e_out
{
	out_file,
	append,
};

/* ------------------------------  STRUCTURE  ------------------------------- */

// structure used to save a string for the parsing
typedef struct s_parse
{
	char	*str;
	int		i;
	int		save;
}	t_parse;

// structure used to save all inputs
typedef struct s_input
{
	char			*str;
	enum e_in		in;
	struct s_input	*next;
	struct s_input	*prev;
}	t_input;

// structure used to save all outputs
typedef struct s_output
{
	char			*str;
	enum e_out		out;
	struct s_output	*next;
	struct s_output	*prev;
}	t_output;

// structure used for saving every data from minishell
typedef struct s_data
{
	char	**path;
	char	**envp;
	int		exit_status;
}	t_data;

// structure saving each steps on from the read line
typedef struct s_exec
{
	char			*str;
	char			*function;
	char			*delimiter;
	char			**words;
	char			**arg;
	t_input			*input;
	t_output		*output;
	t_data			*data;
	struct s_exec	*next;
	struct s_exec	*prev;
}	t_exec;

/* ------------------------------  PROTOTYPE   ------------------------------ */

// check line
int			check_line(char *str);

// parsing
int			parse(char *str, t_exec **exec, t_data *data);

// quotes
int			parse_quotes_env(char *str, char **line_parsed, char **envp);

// parsing utils
char		*str_add(char *str, char c);
char		*create_copy(char *str, int save, int i);
int			init_data(t_data *data, char **envp);
int			delete_slash_symbol(t_exec *exec, char *str);
int			size_arg(char **arg);

// search character
int			is_in_quote(char *str, int index);

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

// exec list utils
t_exec		*new_exec(char *str, t_data *data);
void		exec_clear_data(t_exec **exec);
void		exec_add_back(t_exec **bracket, t_exec *new);

// input output list utils
t_input		*last_input(t_input *input);
t_output	*last_output(t_output *output);
void		input_clear_data(t_input **input);
void		output_clear_data(t_output **output);

// find redirections
int			find_redirections(t_exec **exec);

// create exec list
int			create_exec(char *str, t_exec **exec, t_data *data);

// free utils
void		free_split(char **split);

// split words
char		**split_not_quotes(char *str);



void	print_exec(t_exec *exec);
#endif
