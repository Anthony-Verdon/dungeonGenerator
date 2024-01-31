SRCS := $(wildcard srcs/*.c)

OBJS := $(SRCS:.c=.o)

NAME := dungeonGenerator

COMPILER := clang

RM		:= rm -f

CFLAGS 	:= -Wall -Werror -Wextra

LIBRARIES := -lSDL2

.cpp.o:
			${COMPILER} ${CFLAGS} -c $< -o ${<:.cpp=.o}

all: 		${NAME}

${NAME}:	${OBJS}
			${COMPILER} ${OBJS} -o ${NAME} ${LIBRARIES}

clean:
			${RM} ${OBJS} ${OBJS} 

fclean: 	clean
			${RM} ${NAME} ${NAME}

re:
			make fclean
			make

.PHONY: 	all clean fclean re