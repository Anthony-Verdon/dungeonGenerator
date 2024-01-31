SRCS	= ft_dprintf.c \
		  ft_putnbr_base.c \
		  ft_iterative_power.c \
		  ../ft_putchar_fd.c \
		  ../ft_putstr_fd.c \
		  ../ft_strchr.c \
		  ../ft_strlen.c

OBJS 	= ${SRCS:.c=.o}

NAME 	= libftdprintf.a

COMPILER= clang

RM		= rm -f

CFLAGS 	= -Wall -Werror -Wextra

all: 		${NAME}

.c.o:		${OBJS}
			${COMPILER} ${CFLAGS} -c $< -o ${<:.c=.o}
	
${NAME}:	${OBJS}
			@ar rcs ${NAME} ${OBJS}

clean:	
			${RM} ${OBJS} 

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

.PHONY: 	all clean fclean re
