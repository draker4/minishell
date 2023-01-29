# ************************  LIBFT MAKEFILE  ************************ #

.PHONY:		all clean fclean re bonus debug dclean fdclean

# **************************  VARIABLES  *************************** #

# ------------  Library  ------------- #

NAME		=	libft.a
DEBUG		=	libft_debug.a

# ----------  Directories  ----------- #

DIR_HEAD	=	./
DIR_SRCS	=	./
DIR_OBJS	=	.build/
DIR_OBJS_D	=	.build_debug/
DIR_DEBUG	=	${DEBUG}.dSYM

# -------------  Files  -------------- #

HEAD		=	libft.h
SRCS		=	ft_atoi_itoa.c		ft_calloc.c			ft_get_next_line.c	\
				ft_is_alpha.c		ft_is_other.c		ft_lst_apply.c		\
				ft_lst_clear.c		ft_lst_new.c		ft_mem_all.c		\
				ft_print_fd.c		ft_print_number.c	ft_print_other.c	\
				ft_printf.c			ft_split.c			ft_str_add.c		\
				ft_str_apply.c		ft_str_copy.c		ft_str_find.c		\
				ft_to_all.c		
OBJS		=	${SRCS:%.c=${DIR_OBJS}%.o}
OBJS_D		=	${SRCS:%.c=${DIR_OBJS_D}%.o}

DEPS			=	${OBJS:.o=.d}
DEPS_D			=	${OBJS_D:.o=.d}

# --------------  Path  -------------- #

PATH_HEAD	=	${addprefix ${DIR_HEAD}, ${HEAD}}
PATH_SRCS	=	${addprefix ${DIR_SRCS}, ${SRCS}}

# ----------  Compilation  ----------- #

CC			=	cc
CFLAGS		= 	-Wall -Wextra -Werror
AR			= 	ar rcs
FSANITIZE	=	-fsanitize=address
OPTI		=	-O3
MMD			=	-MMD

# ------------  Commands  ------------ #

RM			=	rm -rf
MKDIR		=	mkdir -p
LEAKS		=	leaks -atExit -- 
LLDB		=	lldb

# ****************************  RULES  ***************************** #

all				:
					${MAKE} -j ${NAME}

# ---------  Compiled Rules  --------- #

${NAME}			:	${OBJS} Makefile
					${AR} ${NAME} ${OBJS}

${OBJS}			:	| ${DIR_OBJS}

${DIR_OBJS}%.o	:	${DIR_SRCS}%.c Makefile
					${CC} ${CFLAGS} -I ${DIR_HEAD} ${MMD} -c $< -o $@

${DIR_OBJS}		:
					${MKDIR} ${DIR_OBJS}

-include ${DEPS}

# ------  Compiled Rules Debug  ------ #

${DEBUG}		:	${OBJS_D} Makefile
					${AR} ${DEBUG} ${OBJS_D}

${OBJS_D}		:	| ${DIR_OBJS_D}

${DIR_OBJS_D}%.o:	${DIR_SRCS}%.c ${PATH_HEAD} Makefile
					${CC} ${CFLAGS} -I ${DIR_HEAD} ${MMD} -g3 ${FSANITIZE} -c $< -o $@

${DIR_OBJS_D}	:
					${MKDIR} ${DIR_OBJS_D}

-include ${DEPS_D}

# ---------  Usual Commands  --------  #

clean			:	
					${RM} ${DIR_OBJS}
					${RM} ${DIR_DEBUG}
					${RM} ${DIR_OBJS_D}
					${RM} ${DEBUG}

fclean			:	clean
					${RM} ${NAME}

re				:
					make fclean
					make fdclean
					make all

# ----------  Other Commands ---------- #

debug			:	
					${MAKE} -j ${DEBUG}
