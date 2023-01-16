# ************************  LIBFT MAKEFILE  ************************ #

.PHONY			:	all clean fclean re bonus debug run runl runs rund

# **************************  VARIABLES  *************************** #

# ---  Final Executable  --- #

NAME			=	push_swap
DEBUG			=	push_swap_debug
CHECK			=	checker
C_DEBUG			=	checker_debug

# ----------  Directories  ----------- #

DIR_HEAD		=	./incl/
DIR_SRCS		=	./srcs/
DIR_LIBFT		=	./srcs/libft/
DIR_OBJS		=	.objs/
DIR_OBJS_D		=	.objs_debug/
DIR_OBJS_C		=	.objs_checker/
DIR_OBJS_C_D	=	.objs_checker_debug/

# -------------  Files  -------------- #

HEAD			=	push_swap.h

HEAD_C			=	checker.h	push_swap.h

SRCS			=	ft_arg_list.c			\
					ft_define_next_move.c	\
					ft_define_order.c		\
					ft_parse.c				\
					ft_push.c				\
					ft_realise_move.c		\
					ft_reverse.c			\
					ft_rotate.c				\
					ft_sort_simple.c		\
					ft_swap.c				\
					push_swap.c

SRCS_C			=	checker_lst.c			\
					checker_utils.c			\
					checker.c				\
					ft_arg_list.c			\
					ft_parse.c				\
					ft_push.c				\
					ft_reverse.c			\
					ft_rotate.c				\
					ft_swap.c

OBJS			=	${SRCS:%.c=${DIR_OBJS}%.o}
OBJS_D			=	${SRCS:%.c=${DIR_OBJS_D}%.o}
OBJS_C			=	${SRCS_C:%.c=${DIR_OBJS_C}%.o}
OBJS_C_D		=	${SRCS_C:%.c=${DIR_OBJS_C_D}%.o}

# --------------  Path  -------------- #

PATH_HEAD		=	${addprefix ${DIR_HEAD}, ${HEAD}}
PATH_HEAD_C		=	${addprefix ${DIR_HEAD}, ${HEAD_C}}

# ----------  Compilation  ----------- #

CC				=	cc
CFLAGS			= 	-Wall -Wextra -Werror
AR				= 	ar rcs
FSANITIZE		=	-fsanitize=address
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
						$(MAKE) -C ${DIR_LIBFT}
						$(MAKE) -j ${NAME}

# ---------  Compiled Rules  --------- #

${NAME}				:	${OBJS}
						${CC} ${CFLAGS} -L ${DIR_LIBFT} ${LIBFT} ${OBJS} -o ${NAME} 

${OBJS}				:	| ${DIR_OBJS}

${DIR_OBJS}%.o		:	${DIR_SRCS}%.c ${PATH_HEAD} Makefile
						${CC} ${CFLAGS} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${MMD} -c $< -o $@

${DIR_OBJS}			:
						${MKDIR} ${DIR_OBJS}

-include ${DIR_OBJS}%.d

# ------  Compiled Rules Debug  ------ #

${DEBUG}			:	${OBJS_D}
						${CC} ${CFLAGS} -L ${DIR_LIBFT} ${LIBFT_D} ${OBJS_D} -g3 ${FSANITIZE} -o ${DEBUG}

${OBJS_D}			:	| ${DIR_OBJS_D}

${DIR_OBJS_D}%.o	:	${DIR_SRCS}%.c ${PATH_HEAD} Makefile
						${CC} ${CFLAGS} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${MMD} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D}		:
						${MKDIR} ${DIR_OBJS_D}

-include ${DIR_OBJS_D}%.d

# ------  Compiled Rules Bonus  ------ #

${CHECK}			:	${OBJS_C}
						${CC} ${CFLAGS} -L ${DIR_LIBFT} ${LIBFT} ${OBJS_C} -o ${CHECK} 

${OBJS_C}			:	| ${DIR_OBJS_C}

${DIR_OBJS_C}%.o	:	${DIR_SRCS}%.c ${PATH_HEAD_C} Makefile
						${CC} ${CFLAGS} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${MMD} -c $< -o $@

${DIR_OBJS_C}		:
						${MKDIR} ${DIR_OBJS_C}

-include ${DIR_OBJS_C}%.d

# ---  Compiled Rules Bonus Debug  --- #

${C_DEBUG}			:	${OBJS_C_D}
						${CC} ${CFLAGS} -L ${DIR_LIBFT} ${LIBFT_D} ${OBJS_C_D} -g3 ${FSANITIZE} -o ${C_DEBUG}

${OBJS_C_D}			:	| ${DIR_OBJS_C_D}

${DIR_OBJS_C_D}%.o	:	${DIR_SRCS}%.c ${PATH_HEAD_C} Makefile
						${CC} ${CFLAGS} -I ${DIR_HEAD} -I ${DIR_LIBFT} ${MMD} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_C_D}		:
						${MKDIR} ${DIR_OBJS_C_D}

-include ${DIR_OBJS_C_D}%.d

# ---------  Usual Commands  --------  #

clean				:	
						${RM} ${DIR_OBJS}
						${RM} ${DIR_OBJS_C}
						${RM} ${DIR_OBJS_D}
						${RM} ${DIR_OBJS_C_D}

fclean				:	clean
						${RM} ${NAME}
						${RM} ${DEBUG}
						${RM} ${CHECK}
						${RM} ${C_DEBUG}
						$(MAKE) fclean -C ${DIR_LIBFT}

re					:
						$(MAKE) fclean
						$(MAKE) all

# ---------  Other Commands  --------- #

debug				:	
						$(MAKE) debug -C ${DIR_LIBFT}
						$(MAKE) -j ${DEBUG}

bonus				:	
						$(MAKE) -C ${DIR_LIBFT}
						$(MAKE) -j ${CHECK}

bonus_debug			:	
						$(MAKE) debug -C ${DIR_LIBFT}
						$(MAKE) -j ${C_DEBUG}

# -----------  Run Commands  --------- #

TEST				= "1 0"
TEST2				= "1 0 -1"
TEST100				=  50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4 -5 -6 -7 -8 -9 -10 -11 -12 -13 -14 -15 -16 -17 -18 -19 -20 -21 -22 -23 -24 -25 -26 -27 -28 -29 -30 -31 -32 -33 -34 -35 -36 -37 -38 -39 -40 -41 -42 -43 -44 -45 -46 -47 -48 -49
TEST99				=  50 49 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4 -5 -6 -7 -8 -9 -10 -11 -12 -13 -14 -15 -16 -17 -18 -19 -20 -21 -22 -23 -24 -25 -26 -27 -28 -29 -30 -31 -32 -33 -34 -35 -36 -37 -38 -39 -40 -41 -42 -43 -44 -45 -46 -47 -48 -49

run					:	all
						./${NAME} ${TEST}

runcheck			:	all bonus
						./${NAME} ${TEST} | ./${CHECK} ${TEST}

runl				:	all
						${LEAKS}./${NAME} ${TEST}

runcheckl			:	all bonus
						./${NAME} ${TEST100} | ${LEAKS} ./${CHECK} ${TEST2}

runs				:	debug bonus_debug
						./${DEBUG} ${TEST100} | ./${C_DEBUG} ${TEST100}

rund				:	debug
						${LLDB} ./${DEBUG}
