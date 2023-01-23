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
DIR_SRCS_P			=	./srcs/parsing/
DIR_SRCS_E			=	./srcs/parsing/
DIR_SRCS_S			=	./srcs/signal/
DIR_SRCS_B			=	./srcs/builtins/
DIR_LIBFT			=	./libft/
DIR_OBJS			=	.build/
DIR_OBJS_P			=	.build/parsing/
DIR_OBJS_E			=	.build/execute/
DIR_OBJS_S			=	.build/signal/
DIR_OBJS_B			=	.build/builtins/
DIR_OBJS_D			=	.build_debug/
DIR_OBJS_D_P		=	.build_debug/parsing/
DIR_OBJS_D_E		=	.build_debug/execute/
DIR_OBJS_D_S		=	.build_debug/signal/
DIR_OBJS_D_B		=	.build_debug/builtins/

# -------------  Files  -------------- #

HEAD			=	minishell.h

SRCS			=	minishell.c

SRCS_P			=	parsing.c				parsing_utils.c			\
					quotes.c				env_var.c				\
					create_exec.c			ft_split_path.c			\
					check_and_or_symbols.c	check_redirections.c	\
					free_utils.c			search_char.c			\
					check_line.c			split_words.c			\
					lst_exec_utils.c		lst_in_out_utils.c		\
					find_redirections.c		is_builtin.c			\
					create_path_cmd.c		copy_env.c				\
					add_env.c				get_path_var.c

SRCS_E			=	close_file.c			define_file.c			\
					execute_cmd.c			get_delimiter.c			\
					handle_commande.c
					

SRCS_S			=	handler.c

SRCS_B			=	ft_cd.c					ft_echo.c				\
					ft_env.c				ft_exit.c				\
					ft_export.c				ft_pwd.c				\
					ft_unset.c

OBJS			=	${SRCS:%.c=${DIR_OBJS}%.o}
OBJS_P			=	${SRCS_P:%.c=${DIR_OBJS_P}%.o}
OBJS_E			=	${SRCS_E:%.c=${DIR_OBJS_E}%.o}
OBJS_S			=	${SRCS_S:%.c=${DIR_OBJS_S}%.o}
OBJS_B			=	${SRCS_B:%.c=${DIR_OBJS_B}%.o}
OBJS_D			=	${SRCS:%.c=${DIR_OBJS_D}%.o}
OBJS_D_P		=	${SRCS_P:%.c=${DIR_OBJS_D_P}%.o}
OBJS_D_E		=	${SRCS_E:%.c=${DIR_OBJS_D_E}%.o}
OBJS_D_S		=	${SRCS_S:%.c=${DIR_OBJS_D_S}%.o}
OBJS_D_B		=	${SRCS_B:%.c=${DIR_OBJS_D_B}%.o}

DEPS			=	${OBJS:.o=.d}
DEPS_P			=	${OBJS_P:.o=.d}
DEPS_E			=	${OBJS_E:.o=.d}
DEPS_S			=	${OBJS_S:.o=.d}
DEPS_B			=	${OBJS_B:.o=.d}
DEPS_D			=	${OBJS_D:.o=.d}
DEPS_D_P		=	${OBJS_D_P:.o=.d}
DEPS_D_E		=	${OBJS_D_E:.o=.d}
DEPS_D_S		=	${OBJS_D_S:.o=.d}
DEPS_D_B		=	${OBJS_D_B:.o=.d}

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

# ------------  Commands  ------------ #

RM				=	rm -rf
MKDIR			=	mkdir -p
LEAKS			=	leaks -atExit -- 
LLDB			=	lldb
CP				=	cp

# ****************************  RULES  ***************************** #

all					:	
						${MAKE} -C ${DIR_LIBFT}
						$(MAKE) -j ${NAME}

# ---------  Compiled Rules  --------- #

${NAME}				:	${OBJS} ${OBJS_P} ${OBJS_E} ${OBJS_S} ${OBJS_B}
						${CC} ${CFLAGS}  ${OBJS} ${OBJS_P} ${OBJS_E} ${OBJS_S} ${OBJS_B} -L ${DIR_LIBFT} ${L_READ1} ${L_READ2} ${LIBFT} ${READLINE} -o ${NAME}

${DIR_OBJS}%.o		:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} -c $< -o $@

${DIR_OBJS_P}%.o	:	${DIR_SRCS_P}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} -c $< -o $@

${DIR_OBJS_E}%.o	:	${DIR_SRCS_E}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} -c $< -o $@

${DIR_OBJS_S}%.o	:	${DIR_SRCS_S}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} -c $< -o $@

${DIR_OBJS_B}%.o	:	${DIR_SRCS_B}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} -c $< -o $@

${DIR_OBJS}			:
						${MKDIR} ${DIR_OBJS}
						${MKDIR} ${DIR_OBJS_P}
						${MKDIR} ${DIR_OBJS_E}
						${MKDIR} ${DIR_OBJS_S}
						${MKDIR} ${DIR_OBJS_B}

-include ${DEPS}
-include ${DEPS_P}
-include ${DEPS_E}
-include ${DEPS_S}
-include ${DEPS_B}

# ------  Compiled Rules Debug  ------ #

${DEBUG}			:	${OBJS_D} ${OBJS_D_P} ${OBJS_D_E} ${OBJS_D_S} ${OBJS_D_B}
						${CC} ${CFLAGS} -L ${DIR_LIBFT} ${LIBFT_D} ${L_READ1} ${L_READ2} ${READLINE} ${OBJS_D} ${OBJS_D_P} ${OBJS_D_E} ${OBJS_D_S} ${OBJS_D_B} -g3 ${FSANITIZE} -o ${DEBUG}

${DIR_OBJS_D}%.o	:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_P}%.o	:	${DIR_SRCS_P}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_E}%.o	:	${DIR_SRCS_E}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_S}%.o	:	${DIR_SRCS_S}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_B}%.o	:	${DIR_SRCS_B}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${I_READ1} ${I_READ2} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D}		:
						${MKDIR} ${DIR_OBJS_D}
						${MKDIR} ${DIR_OBJS_D_P}
						${MKDIR} ${DIR_OBJS_D_E}
						${MKDIR} ${DIR_OBJS_D_S}
						${MKDIR} ${DIR_OBJS_D_B}

-include ${DEPS_D}
-include ${DEPS_D_P}
-include ${DEPS_D_E}
-include ${DEPS_D_S}
-include ${DEPS_D_B}

# ---------  Usual Commands  --------  #

clean				:	
						${RM} ${DIR_OBJS}
						${RM} ${DIR_OBJS_D}

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
