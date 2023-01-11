# ************************  PHILO MAKEFILE  ************************ #

.PHONY			:	all clean fclean re debug run runl runs rund

# **************************  VARIABLES  *************************** #

# ---  Final Executable  --- #

NAME			=	philo
DEBUG			=	philo_debug

# ----------  Directories  ----------- #

DIR_HEAD		=	./incl/
DIR_SRCS		=	./srcs/
DIR_OBJS		=	.objs/
DIR_OBJS_D		=	.objs_debug/

# -------------  Files  -------------- #

HEAD			=	philo.h

SRCS			=	ft_check_arg.c	\
					ft_check_run.c	\
					ft_init.c		\
					ft_process.c	\
					ft_utilis.c		\
					philo.c

OBJS			=	${SRCS:%.c=${DIR_OBJS}%.o}
OBJS_D			=	${SRCS:%.c=${DIR_OBJS_D}%.o}

# --------------  Path  -------------- #

PATH_HEAD		=	${addprefix ${DIR_HEAD}, ${HEAD}}
PATH_LIBFT		=	${addprefix ${DIR_LIBFT}, ${LIBFT_A}}

# ----------  Compilation  ----------- #

CC				=	cc
CFLAGS			= 	-Wall -Wextra -Werror
AR				= 	ar rcs
FSANITIZE		=	-fsanitize=pthread
OPTI			=	-O3
LIBFT			=	-lft
LIBFT_D			=	-lft_debug
MMD				=	-MMD

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

${NAME}				:	${OBJS}
						${CC} ${CFLAGS} -pthread ${OBJS} -o ${NAME} 

${OBJS}				:	| ${DIR_OBJS}

${DIR_OBJS}%.o		:	${DIR_SRCS}%.c ${PATH_HEAD} Makefile
						${CC} ${CFLAGS} -pthread -I ${DIR_HEAD} ${MMD} -c $< -o $@

${DIR_OBJS}			:
						${MKDIR} ${DIR_OBJS}

-include ${DIR_OBJS}%.d

# ------  Compiled Rules Debug  ------ #

${DEBUG}			:	${OBJS_D}
						${CC} ${CFLAGS} -pthread ${OBJS_D} -g3 ${FSANITIZE} -o ${DEBUG}

${OBJS_D}			:	| ${DIR_OBJS_D}

${DIR_OBJS_D}%.o	:	${DIR_SRCS}%.c ${PATH_HEAD} Makefile
						${CC} ${CFLAGS} -pthread -I ${DIR_HEAD} ${MMD} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D}		:
						${MKDIR} ${DIR_OBJS_D}

-include ${DIR_OBJS_D}%.d

# ---------  Usual Commands  --------  #

clean				:	
						${RM} ${DIR_OBJS}
						${RM} ${DIR_OBJS_D}

fclean				:	clean
						${RM} ${NAME}
						${RM} ${DEBUG}

re					:
						$(MAKE) fclean
						$(MAKE) all

# ---------  Other Commands  --------- #

debug				:	
						$(MAKE) -j ${DEBUG}

# -----------  Run Commands  --------- #

TEST				=	 4 410 200 200

run					:	all
						./${NAME} ${TEST}

runl				:	all
						${LEAKS}./${NAME} ${TEST}

runcheckl			:	all
						./${NAME}

runs				:	debug
						./${DEBUG} ${TEST}

rund				:	debug
						${LLDB} ./${DEBUG}
