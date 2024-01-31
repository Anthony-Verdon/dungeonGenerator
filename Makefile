SRCS := $(wildcard srcs/*.c)
SRCS += $(wildcard srcs/generateMap/*.c)
SRCS += $(wildcard srcs/parseTexture/*.c)
SRCS += $(wildcard srcs/sdlFunctions/*.c)

OBJS := $(SRCS:.c=.o)

NAME := dungeonGenerator

COMPILER := clang

RM		:= rm -f

CFLAGS 	:= -Wall -Werror -Wextra

LIBRARIES := -lSDL2 -Llibft/ -lft -Llibft/ft_dprintf -lftdprintf

.c.o:
			${COMPILER} ${CFLAGS} -c $< -o ${<:.c=.o}

all: 		${NAME}

${NAME}:	${OBJS}
			make -C libft/
			${COMPILER} ${OBJS} -o ${NAME} ${LIBRARIES}

clean:
			make -C libft/ clean
			${RM} ${OBJS} ${OBJS} 

fclean: 	clean
			make -C libft/ fclean
			${RM} ${NAME} ${NAME}

re:
			make fclean
			make

.PHONY: 	all clean fclean re