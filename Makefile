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
DIR_LIBFT			=	./libft/
DIR_OBJS			=	.build/
DIR_OBJS_P			=	.build/parsing/
DIR_OBJS_E			=	.build/execute/
DIR_OBJS_D			=	.build_debug/
DIR_OBJS_D_P		=	.build_debug/parsing/
DIR_OBJS_D_E		=	.build_debug/execute/

# -------------  Files  -------------- #

HEAD			=	minishell.h

SRCS			=	minishell.c

SRCS_P			=	parsing.c				parsing_utils.c			\
					quotes.c				env_var.c				\
					create_exec.c			get_path_var.c			\
					check_and_or_symbols.c	check_redirections.c	\
					free_utils.c			search_char.c			\
					check_line.c			split_words.c			\
					lst_exec_utils.c		lst_in_out_utils.c		\
					find_redirections.c

SRCS_E			=	change_in_out_put.c	\
					close_file.c		\
					get_delimiter.c		\
					handle_commande.c	

OBJS			=	${SRCS:%.c=${DIR_OBJS}%.o}
OBJS_P			=	${SRCS_P:%.c=${DIR_OBJS_P}%.o}
OBJS_E			=	${SRCS_E:%.c=${DIR_OBJS_E}%.o}
OBJS_D			=	${SRCS:%.c=${DIR_OBJS_D}%.o}
OBJS_D_P		=	${SRCS_P:%.c=${DIR_OBJS_D_P}%.o}
OBJS_D_E		=	${SRCS_E:%.c=${DIR_OBJS_D_E}%.o}

DEPS			=	${OBJS:.o=.d}
DEPS_P			=	${OBJS_P:.o=.d}
DEPS_E			=	${OBJS_E:.o=.d}
DEPS_D			=	${OBJS_D:.o=.d}
DEPS_D_P		=	${OBJS_D_P:.o=.d}
DEPS_D_E		=	${OBJS_D_E:.o=.d}

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

${NAME}				:	${OBJS} ${OBJS_P} ${OBJS_E}
						${CC} ${CFLAGS}  ${OBJS} ${OBJS_P} ${OBJS_E} -L ${DIR_LIBFT} ${LIBFT} ${READLINE} -o ${NAME}

${DIR_OBJS}%.o		:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} -c $< -o $@

${DIR_OBJS_P}%.o	:	${DIR_SRCS_P}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} -c $< -o $@

${DIR_OBJS_E}%.o	:	${DIR_SRCS_E}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} -c $< -o $@

${DIR_OBJS}			:
						${MKDIR} ${DIR_OBJS}
						${MKDIR} ${DIR_OBJS_P}
						${MKDIR} ${DIR_OBJS_E}

-include ${DEPS}
-include ${DEPS_P}
-include ${DEPS_E}

# ------  Compiled Rules Debug  ------ #

${DEBUG}			:	${OBJS_D} ${OBJS_D_P} ${OBJS_D_E}
						${CC} ${CFLAGS} -L ${DIR_LIBFT} ${LIBFT_D} ${READLINE} ${OBJS_D} ${OBJS_D_P} ${OBJS_D_E} -g3 ${FSANITIZE} -o ${DEBUG}

${DIR_OBJS_D}%.o	:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${MMD} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D_P}%.o	:	${DIR_SRCS_P}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} -c $< -o $@

${DIR_OBJS_D_E}%.o	:	${DIR_SRCS_E}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} -c $< -o $@

${DIR_OBJS_D}		:
						${MKDIR} ${DIR_OBJS_D}
						${MKDIR} ${DIR_OBJS_D_P}
						${MKDIR} ${DIR_OBJS_D_E}

-include ${DEPS_D}
-include ${DEPS_D_P}
-include ${DEPS_D_E}

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
