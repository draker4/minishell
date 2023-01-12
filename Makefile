# **********************  MINISHELL MAKEFILE  ********************** #

.PHONY			:	all clean fclean re debug run runl runs rund

# **************************  VARIABLES  *************************** #

# ---  Final Executable  --- #

NAME			=	minishell
NAME_LIBFT		=	libft.a
DEBUG			=	minishell_debug

# ----------  Directories  ----------- #

DIR_HEAD		=	./incl/
DIR_SRCS		=	./srcs/
DIR_LIBFT		=	./srcs/libft/
DIR_OBJS		=	.build/
DIR_OBJS_D		=	.build_debug/

# -------------  Files  -------------- #

HEAD			=	minishell.h

SRCS			=	minishell.c			parsing.c

OBJS			=	${SRCS:%.c=${DIR_OBJS}%.o}
OBJS_D			=	${SRCS:%.c=${DIR_OBJS_D}%.o}

DEPS			=	${OBJS:.o=.d}
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
						$(MAKE) -j ${NAME}

# ---------  Compiled Rules  --------- #

${NAME}				:	${OBJS} ${addprefix ${DIR_LIBFT}, ${NAME_LIBFT}}
						${CC} ${CFLAGS} -L ${DIR_LIBFT} ${LIBFT} ${READLINE} ${OBJS} -o ${NAME} 

${addprefix ${DIR_LIBFT}, ${NAME_LIBFT}}	:	
						$(MAKE) ${NAME_LIBFT} -C ${DIR_LIBFT}

${DIR_OBJS}%.o		:	${DIR_SRCS}%.c Makefile | ${DIR_OBJS}
						${CC} ${CFLAGS} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${MMD} -c $< -o $@

${DIR_OBJS}			:
						${MKDIR} ${DIR_OBJS}

-include ${DEPS}

# ------  Compiled Rules Debug  ------ #

${DEBUG}			:	${OBJS_D}
						${CC} ${CFLAGS} -L ${DIR_LIBFT} ${LIBFT_D} ${READLINE} ${OBJS_D} -g3 ${FSANITIZE} -o ${DEBUG}

${OBJS_D}			:	| ${DIR_OBJS_C_D}

${DIR_OBJS_D}%.o	:	${DIR_SRCS}%.c ${PATH_HEAD} ${PATH_LIBFT} Makefile
						${CC} ${CFLAGS} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${READLINE} ${MMD} -g3 ${FSANITIZE} -c $< -o $@

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
						${LEAKS}./${NAME} ${TEST}

runcheckl			:	all
						./${NAME}

runs				:	debug
						./${DEBUG} ${TEST}

rund				:	debug
						${LLDB} ./${DEBUG}
