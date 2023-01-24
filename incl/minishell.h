/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/24 18:12:45 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <termios.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define ERROR_ARG "Please don't enter any argument!\n"

# define FAIL 1

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

enum e_cmd
{
	null,
	path,
	builtin,
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
	int				file;
	char			*str;
	enum e_in		in;
	struct s_input	*next;
}	t_input;

// structure used to save all outputs
typedef struct s_output
{
	int				file;
	char			*str;
	enum e_out		out;
	struct s_output	*next;
}	t_output;

// structre saving the environment variables
typedef struct s_env
{
	char			*var;
	char			*value;
	int				has_equal;
	struct s_env	*next;
}	t_env;

// structure used for saving every data from minishell
typedef struct s_data
{
	char				**path;
	char				**envp;
	t_env				*env;
	int					modify_env;
	struct termios		term;
	struct sigaction	sa;
}	t_data;


// structure saving each steps on from the read line
typedef struct s_exec
{
	char			*str;
	char			*function;
	enum e_cmd		cmd;
	char			*delimiter;
	char			**words;
	char			**arg;
	int				fd_pipe[2];
	char			**cmd_path;
	int				save_stdin;
	int				save_stdout;
	pid_t			pid;
	t_input			*input;
	t_output		*output;
	t_data			*data;
	struct s_exec	*next;
}	t_exec;

/* --------------------------  PROTOTYPE BUILTIN  --------------------------- */

// cd builtin
void		ft_cd(t_exec *exec);

// echo builtin
void		ft_echo(t_exec *exec);

// env builtin
void		ft_env(t_exec *exec);

// exit builtin
void		ft_exit(t_exec *exec);

// export builtin utils

void		print_export(t_exec *exec);

// export builtin
void		ft_export(t_exec *exec);

// pwd builtin
void		ft_pwd(t_exec *exec);

// unset builtin
void		ft_unset(t_exec *exec);

/* --------------------------  PROTOTYPE EXECUTE  --------------------------- */

// close file
void		close_file(t_exec *exec);

// define file
int			change_input(t_input *input);
int			change_output(t_output *output);

// handle commande
void		handle_cmd(t_exec *exec);
void		handle_cmd_list(t_exec *exec);

// close file
void		close_file(t_exec *exec);

// execute cmd
void		execute_builtin(t_exec *exec);
void		execute_commande(t_exec *exec);
void		execute(t_exec *exec);

// get delimiter
int			get_delimiter(int fd, char **line);

/* --------------------------  PROTOTYPE PARSING  --------------------------- */

// add_env
int			add_pwd(t_env **env);
int			add_shlvl(t_env **env);
int			shlvl_plus_one(t_env **env);
int			add_last(t_env **env);
int			add_oldpwd(t_env **env);

// check and (&&), or (||) symbols
int			check_and_or(char *str);

// check line
int			check_line(char *str);

// check redirections (< and > symbols)
int			check_redirections(char *str);

// copy_env
int			copy_env(char **envp, t_data *data);
int			manage_shlvl(t_data *data);
int			which_env_add(t_data *data);

// create exec list
int			create_exec(char *str, t_exec **exec, t_data *data);

// create path cmd
int			create_path_cmd(t_exec **exec);

// environment variables
int			check_env(char *str, char **line_parsed, int *i, char **envp);

// find redirections
int			find_redirections(t_exec **exec);

// create exec list
int			create_exec(char *str, t_exec **exec, t_data *data);

// free utils
void		free_split(char **split);
void		free_all(char *str, t_exec **exec);
void		free_data(t_data *data);

// split words
char		**split_not_quotes(char *str);

// init_data
int			init_data(t_data *data, char **envp);

// is_built_in
void		is_built_in(t_exec *exec);

// parsing
int			parse(char *str, t_exec **exec, t_data *data);

// quotes
int			parse_quotes_env(char *str, char **line_parsed, char **envp);

// search character
int			is_in_quote(char *str, int index);
int			has_equal(char *str);

/* --------------------------  PROTOTYPE SIGNAL  --------------------------- */

void		handler(int sig);

/* -------------------------- PROTOTYPE UTILS  --------------------------- */

// prototypes env list utils
t_env		*new_env(char *var, char *value, int has_equal);
void		env_clear_data(t_env **env);
void		env_add_back(t_env **env, t_env *new);

// env_update
t_env		*in_env(t_env *full_env, char *search_var);
int			update_envp(t_data *data);
int			remove_var(t_env **full_env, char *search_var);

// free utils
void		free_split(char **split);
void		free_all(char *str, t_exec **exec);

// get path variable
int			ft_split_data(char ***new, char const *s, char c);
int			get_path(t_data *data);

// exec list utils
t_exec		*new_exec(char *str, t_data *data);
void		exec_clear_data(t_exec **exec);
void		exec_add_back(t_exec **bracket, t_exec *new);

// input output list utils
t_input		*last_input(t_input *input);
t_output	*last_output(t_output *output);
void		input_clear_data(t_input **input);
void		output_clear_data(t_output **output);

// parsing utils
char		*str_add(char *str, char c);
char		*create_copy(char *str, int save, int i);
int			delete_slash_symbol(t_exec *exec, char *str);
int			size_arg(char **arg);

// prototype split environment variable
char		**split_var(char *s);

// split words
char		**split_not_quotes(char *str);

#endif
