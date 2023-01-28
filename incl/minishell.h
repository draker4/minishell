/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisson <bboisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:38:00 by bboisson          #+#    #+#             */
/*   Updated: 2023/01/28 13:29:03 by bboisson         ###   ########lyon.fr   */
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
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>

# define ERROR_ARG "Please don't enter any argument!\n"

# define FAIL 1

/* -----------------------------  ENUMERATION  ------------------------------ */

enum e_type
{
	in_file,
	delimiter,
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

// structure used to save all inputs and outputs (redirections)
typedef struct s_redir
{
	int				modif;
	char			*str;
	enum e_type		type;
	struct s_redir	*next;
}	t_redir;

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
	char				*line;
	int					modify_env;
	t_env				*env;
	pid_t				*pid;
	struct s_exec		*exec_begin;
	struct termios		term;
	struct termios		term_original;
	struct sigaction	sa;
}	t_data;

// structure saving each steps on from the read line
typedef struct s_exec
{
	char			*str;
	char			*function;
	char			*delimiter;
	char			**words;
	char			**arg;
	char			**cmd_path;
	int				save_stdin;
	int				save_stdout;
	int				infile;
	int				outfile;
	int				delimfile;
	int				nb;
	int				file_error;
	int				fd_pipe[2];
	t_redir			*redir;
	t_data			*data;
	enum e_cmd		cmd;
	struct s_exec	*next;
}	t_exec;

// structure used to handle wildcard
typedef struct s_wild
{
	int				keep;
	char			*arg;
	struct s_wild	*next;
}	t_wild;

typedef struct s_index
{
	int				tab;
	int				arg;
}	t_index;
typedef struct s_check
{
	int				nb;
	int				s_str;
	int				s_start;
	int				s_end;
	int				s_tab;
	char			*str;
	char			*start;
	char			*end;
	char			**tab;
}	t_check;

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
void		handle_error(t_exec *exec);
void		print_export(t_exec *exec);

// export builtin
void		ft_export(t_exec *exec);

// pwd builtin
void		ft_pwd(t_exec *exec);

// unset builtin
void		ft_unset(t_exec *exec);

/* --------------------------  PROTOTYPE EXECUTE  --------------------------- */

// define file
void		change_redir(t_exec *exec, t_redir	*redir);

// handle commande
void		handle_cmd(t_exec *exec);
void		handle_cmd_list(t_exec *exec);

// file utils
void		close_infile(t_exec *exec);
void		close_outfile(t_exec *exec);
void		close_file(t_exec *exec);
void		fd_error(t_exec *exec);
void		file_error(t_exec *exec, t_redir *redir);

// execute cmd
void		execute_builtin(t_exec *exec);
void		execute_commande(t_exec *exec);
void		execute(t_exec *exec);

// get delimiter
int			get_delimiter(char **line, t_exec *exec,
				int status, t_redir *redir);
int			confirm_end(char *s1, char *s2);

/* --------------------------  PROTOTYPE PARSING  --------------------------- */

// add_env
int			add_pwd(t_env **env);
int			add_shlvl(t_env **env);
int			shlvl_plus_one(t_env **env);
int			add_last(t_env **env);
int			add_oldpwd(t_env **env);

// add input output list
int			create_redir(t_exec *current, int *index, int type1, int type2);
int			exit_status_redir(t_exec *exec);

// change environment variable
int			change_env(t_exec **exec);

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
int			ft_change_env(char **old_words, char **envp);

// find delimiter
int			find_delimiter(t_exec **exec);

// find redirections
int			find_redirections(t_exec **exec);

// create exec list
int			create_exec(char *str, t_exec **exec, t_data *data);

// split words
char		**split_not_quotes(char *str);

// init_data
int			init_data(t_data *data, char **envp);

// is_built_in
void		is_built_in(t_exec *exec);

// parse env only
char		*parse_env_only(char *str, char **envp);

// parse new words
int			parse_new_words(t_exec **exec);

// parse quotes
int			parse_quotes(t_exec **exec);

// parse star
int			parse_star(t_exec **exec);

// parsing
int			parse(char *str, t_exec **exec, t_data *data);
char		*parse_word_quotes(char *str, char **envp);

// quotes
int			parse_quotes_env(char *str, char **line_parsed, char **envp);

/* --------------------------  PROTOTYPE SIGNAL  ---------------------------- */

void		handler(int sig);

/* ---------------------------  PROTOTYPE UTILS  ---------------------------- */

// prototypes env list utils
t_env		*new_env(char *var, char *value, int has_equal);
void		env_clear_data(t_env **env);
void		env_add_back(t_env **env, t_env *new);
int			exec_size(t_exec *exec);

// env_update
int			update_envp(t_data *data);
int			remove_var(t_env **full_env, char *search_var);
t_env		*in_env(t_env *full_env, char *search_var);
char		*find_var(t_exec *exec, char *search_value);

// exit status
int			change_exit_status(t_exec **exec);
char		*parse_exit_status(char *str, int status);

// free utils
void		free_split(char **split);
void		free_readline(char *str, t_exec **exec);
void		free_data(t_data *data);
void		free_all(t_data *data);
void		free_exit(t_exec *exec, int nb);

// get path variable
int			ft_split_data(char ***new, char const *s, char c);
int			get_path(t_data *data);

// exec list utils
t_exec		*new_exec(char *str, t_data *data, int nb);
void		exec_clear_data(t_exec **exec);
void		exec_add_back(t_exec **bracket, t_exec *new);

// input output list utils
t_redir		*last_redir(t_redir *redir);
void		redir_clear_data(t_redir **redir);

// parsing utils
char		*str_add(char *str, char c);
char		*create_copy(char *str, int save, int i);
int			delete_slash_symbol(t_exec *exec, char *str);
int			size_arg(char **arg);

// search character
int			is_in_quote(char *str, int index);
int			has_equal(char *str);
int			has_exit_status(char *str);
int			has_space(char *str);
int			has_quote(char *str);

// split spaces not in quotes
char		**split_spaces(char *s);

// prototype split environment variable
char		**split_var(char *s);

// split words
char		**split_not_quotes(char *str);

void		ft_auto_perror(char *info, char *ft, char *error);
void		ft_man_perror(char *info, char *ft, char *error);
int			ft_auto_perror_code(char *info, char *ft, char *error);
/* -------------------------- PROTOTYPE WILDCARD  --------------------------- */

// define check
int			define_check(t_check *check, char *str);

// manage wildcard list
t_wild		*new_wild(char *file);
void		wild_clear_data(t_wild **wild);
void		wild_add_back(t_wild **wild, t_wild *new);

// check wildcard
void		wild_check(t_check	*check, t_wild *wild);

// manage wildcard
void		free_check(t_check *check);
char		*get_wildcard(char *search);

#endif
