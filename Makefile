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
DIR_LIBFT			=	./libft/
DIR_OBJS			=	.build/
DIR_OBJS_P			=	.build/parsing/
DIR_OBJS_D			=	.build_debug/

# -------------  Files  -------------- #

HEAD			=	minishell.h

SRCS			=	minishell.c

SRCS_P			=	parsing.c				parsing_utils.c			\
					quotes.c				env_var.c			\
					lst_bracket_utils.c		create_bracket.c		\
					get_path_var.c			check_around_par.c		\
					check_and_or_symbols.c	check_redirections.c	\
					free_utils.c			search_char.c			\
					exec_bracket.c			check_line.c			\
					split_words.c			add_bracket.c

OBJS			=	${SRCS:%.c=${DIR_OBJS}%.o}
OBJS_P			=	${SRCS_P:%.c=${DIR_OBJS_P}%.o}
OBJS_D			=	${SRCS:%.c=${DIR_OBJS_D}%.o}

DEPS			=	${OBJS:.o=.d}
DEPS_P			=	${OBJS_P:.o=.d}
DEPS_D			=	${OBJS_D:.o=.d}

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

${NAME}				:	${OBJS} ${OBJS_P}
						${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${OBJS_P} -L ${DIR_LIBFT} ${LIBFT} ${READLINE} 

${DIR_OBJS}%.o		:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} -c $< -o $@

${DIR_OBJS_P}%.o	:	${DIR_SRCS_P}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} ${MMD} -I ${DIR_HEAD} -I ${DIR_LIBFT} -c $< -o $@

${DIR_OBJS}			:
						${MKDIR} ${DIR_OBJS}
						${MKDIR} -p .build/parsing

-include ${DEPS}
-include ${DEPS_P}

# ------  Compiled Rules Debug  ------ #

${DEBUG}			:	${OBJS_D} ${addprefix ${DIR_LIBFT}, ${NAME_LIBFT}}
						${CC} ${CFLAGS} -L ${DIR_LIBFT} ${LIBFT_D} ${READLINE} ${OBJS_D} -g3 ${FSANITIZE} -o ${DEBUG}

${addprefix ${DIR_LIBFT}, ${DEBUG_LIBFT}}	:	
						$(MAKE) ${DEBUG_LIBFT} -C ${DIR_LIBFT}

${DIR_OBJS_D}%.o	:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS_D}
						${CC} ${CFLAGS} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${MMD} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D}		:
						${MKDIR} ${DIR_OBJS_D}

-include ${DEPS_D}

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
