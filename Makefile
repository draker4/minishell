# **********************  MINISHELL MAKEFILE  ********************** #

.PHONY			:	all clean fclean re debug run runl runs rund

# **************************  VARIABLES  *************************** #

# ---  Final Executable  --- #

NAME			=	minishell
NAME_LIBFT		=	libft.a
DEBUG			=	minishell_debug
DEBUG_LIBFT		=	libft_debug.a

# ----------  Directories  ----------- #

DIR_HEAD			=	./incl/
DIR_SRCS			=	./srcs/
DIR_SRCS_B			=	./srcs/builtins/
DIR_SRCS_E			=	./srcs/execute/
DIR_SRCS_P			=	./srcs/parsing/
DIR_SRCS_S			=	./srcs/signal/
DIR_SRCS_U			=	./srcs/utils/
DIR_LIBFT			=	./libft/
DIR_OBJS			=	.build/
DIR_OBJS_B			=	.build/builtins/
DIR_OBJS_E			=	.build/execute/
DIR_OBJS_P			=	.build/parsing/
DIR_OBJS_S			=	.build/signal/
DIR_OBJS_U			=	.build/utils/
DIR_OBJS_D			=	.build_debug/
DIR_OBJS_D_B		=	.build_debug/builtins/
DIR_OBJS_D_E		=	.build_debug/execute/
DIR_OBJS_D_P		=	.build_debug/parsing/
DIR_OBJS_D_S		=	.build_debug/signal/
DIR_OBJS_D_U		=	.build_debug/utils/
DIR_DEBUG			=	${NAME}.dSYM

# -------------  Files  -------------- #

HEAD			=	minishell.h

SRCS			=	minishell.c

SRCS_B			=	ft_cd.c					\
					ft_echo.c				\
					ft_env.c				\
					ft_exit.c				\
					ft_export_utilis.c		\
					ft_export.c				\
					ft_pwd.c				\
					ft_unset.c

SRCS_E			=	close_file.c			\
					define_file.c			\
					execute_cmd.c			\
					get_delimiter.c			\
					handle_commande.c

SRCS_P			=	add_env.c				\
					add_input_output.c		\
					check_and_or_symbols.c	\
					check_line.c			\
					check_redirections.c	\
					copy_env.c				\
					create_exec.c			\
					create_path_cmd.c		\
					env_var.c				\
					find_redirections.c		\
					init_data.c				\
					is_builtin.c			\
					parse_space.c			\
					parsing.c				\
					quotes.c

SRCS_S			=	handler.c

SRCS_U			=	env_lst_utils.c			\
					env_update.c			\
					exit_status.c			\
					free_utils.c			\
					get_path_var.c			\
					lst_exec_utils.c		\
					lst_in_out_utils.c		\
					parsing_utils.c			\
					print_error.c			\
					search_char.c			\
					split_var.c				\
					split_words.c			\
					wildcard.c

OBJS			=	${SRCS:%.c=${DIR_OBJS}%.o}
OBJS_B			=	${SRCS_B:%.c=${DIR_OBJS_B}%.o}
OBJS_E			=	${SRCS_E:%.c=${DIR_OBJS_E}%.o}
OBJS_P			=	${SRCS_P:%.c=${DIR_OBJS_P}%.o}
OBJS_S			=	${SRCS_S:%.c=${DIR_OBJS_S}%.o}
OBJS_U			=	${SRCS_U:%.c=${DIR_OBJS_U}%.o}
OBJS_D			=	${SRCS:%.c=${DIR_OBJS_D}%.o}
OBJS_D_B		=	${SRCS_B:%.c=${DIR_OBJS_D_B}%.o}
OBJS_D_E		=	${SRCS_E:%.c=${DIR_OBJS_D_E}%.o}
OBJS_D_P		=	${SRCS_P:%.c=${DIR_OBJS_D_P}%.o}
OBJS_D_S		=	${SRCS_S:%.c=${DIR_OBJS_D_S}%.o}
OBJS_D_U		=	${SRCS_U:%.c=${DIR_OBJS_D_U}%.o}

DEPS			=	${OBJS:.o=.d}
DEPS_B			=	${OBJS_B:.o=.d}
DEPS_E			=	${OBJS_E:.o=.d}
DEPS_P			=	${OBJS_P:.o=.d}
DEPS_S			=	${OBJS_S:.o=.d}
DEPS_D			=	${OBJS_D:.o=.d}
DEPS_D_B		=	${OBJS_D_B:.o=.d}
DEPS_D_E		=	${OBJS_D_E:.o=.d}
DEPS_D_P		=	${OBJS_D_P:.o=.d}
DEPS_D_S		=	${OBJS_D_S:.o=.d}
DEPS_D_U		=	${OBJS_D_U:.o=.d}

# --------------  Path  -------------- #

PATH_HEAD		=	${addprefix ${DIR_HEAD}, ${HEAD}}
PATH_LIBFT		=	${addprefix ${DIR_LIBFT}, ${LIBFT_A}}

# ----------  Compilation  ----------- #

CC				=	cc
CFLAGS			= 	-Wall -Wextra -Werror
AR				= 	ar rcs
FSANITIZE		=	-fsanitize=address
OPTI			=	-O3
LIBFT			=	-lft
LIBFT_D			=	-lft_debug
MMD				=	-MMD
READLINE		=	-lreadline
L_READ1			=	-L/Users/bboisson/.brew/opt/readline/lib
I_READ1			=	-I/Users/bboisson/.brew/opt/readline/include
L_READ2			=	-L/Users/bperriol/.brew/opt/readline/lib
I_READ2			=	-I/Users/bperriol/.brew/opt/readline/include
L_READ3			=	-L/opt/homebrew/opt/readline/lib
I_READ3			=	-I/opt/homebrew/opt/readline/include

# ------------  Commands  ------------ #

RM				=	rm -rf
MKDIR			=	mkdir -p
LEAKS			=	leaks -atExit -- 
LLDB			=	lldb
CP				=	cp
VALGRIND		=	valgrind --leak-check=full --track-origins=yes --show-reachable=no

# ****************************  RULES  ***************************** #

all					:	
						${MAKE} -C ${DIR_LIBFT}
						$(MAKE) -j ${NAME}

# ---------  Compiled Rules  --------- #

${NAME}				:	${OBJS} ${OBJS_B} ${OBJS_E} ${OBJS_P} ${OBJS_S} ${OBJS_U}
						${CC} ${CFLAGS} ${OBJS} ${OBJS_B} ${OBJS_E} ${OBJS_P} ${OBJS_S}  ${OBJS_U} -L ${DIR_LIBFT} ${L_READ1} ${L_READ2} ${L_READ3} ${LIBFT} ${READLINE} -o ${NAME}

${DIR_OBJS}%.o		:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -c $< -o $@

${DIR_OBJS_B}%.o	:	${DIR_SRCS_B}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -c $< -o $@

${DIR_OBJS_E}%.o	:	${DIR_SRCS_E}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -c $< -o $@

${DIR_OBJS_P}%.o	:	${DIR_SRCS_P}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -c $< -o $@

${DIR_OBJS_S}%.o	:	${DIR_SRCS_S}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -c $< -o $@

${DIR_OBJS_U}%.o	:	${DIR_SRCS_U}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -c $< -o $@

${DIR_OBJS}			:
						${MKDIR} ${DIR_OBJS}
						${MKDIR} ${DIR_OBJS_B}
						${MKDIR} ${DIR_OBJS_E}
						${MKDIR} ${DIR_OBJS_P}
						${MKDIR} ${DIR_OBJS_S}
						${MKDIR} ${DIR_OBJS_U}

-include ${DEPS}
-include ${DEPS_B}
-include ${DEPS_E}
-include ${DEPS_P}
-include ${DEPS_S}
-include ${DEPS_U}

# ------  Compiled Rules Debug  ------ #

${DEBUG}			:	${OBJS_D} ${OBJS_D_B} ${OBJS_D_E} ${OBJS_D_P} ${OBJS_D_S} ${OBJS_D_U}
						${CC} ${CFLAGS} ${OBJS_D} ${OBJS_D_B} ${OBJS_D_E} ${OBJS_D_P} ${OBJS_D_S} ${OBJS_D_U} -L ${DIR_LIBFT} ${LIBFT_D} ${L_READ1} ${L_READ2} ${L_READ3} ${READLINE} -g3 ${FSANITIZE} -o ${DEBUG}

${DIR_OBJS_D}%.o	:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_B}%.o	:	${DIR_SRCS_B}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_E}%.o	:	${DIR_SRCS_E}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_P}%.o	:	${DIR_SRCS_P}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_S}%.o	:	${DIR_SRCS_S}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_U}%.o	:	${DIR_SRCS_U}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} ${I_READ3} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D}		:
						${MKDIR} ${DIR_OBJS_D}
						${MKDIR} ${DIR_OBJS_D_B}
						${MKDIR} ${DIR_OBJS_D_E}
						${MKDIR} ${DIR_OBJS_D_P}
						${MKDIR} ${DIR_OBJS_D_S}
						${MKDIR} ${DIR_OBJS_D_U}

-include ${DEPS_D}
-include ${DEPS_D_B}
-include ${DEPS_D_E}
-include ${DEPS_D_P}
-include ${DEPS_D_S}
-include ${DEPS_D_U}

# ---------  Usual Commands  --------  #

clean				:	
						${RM} ${DIR_OBJS}
						${RM} ${DIR_OBJS_D}
						${RM} ${DIR_DEBUG}

fclean				:	clean
						${RM} ${NAME}
						${RM} ${DEBUG}
						$(MAKE) fclean -C ${DIR_LIBFT}

re					:
						$(MAKE) fclean
						$(MAKE) all

# ---------  Other Commands  --------- #

debug				:	
						$(MAKE) debug -C ${DIR_LIBFT}
						$(MAKE) -j ${DEBUG}

# -----------  Run Commands  --------- #

run					:	all
						./${NAME}

runl				:	all
						${LEAKS}./${NAME}

runs				:	debug
						./${DEBUG}

rund				:	debug
						${LLDB} ./${DEBUG}

runv				:	all
						${VALGRIND} ./${NAME}