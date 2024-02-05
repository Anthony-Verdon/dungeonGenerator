SRCS := $(wildcard srcs/*.cpp)
SRCS += $(wildcard srcs/classes/SDL/*.cpp)
SRCS += $(wildcard srcs/classes/Texture/*.cpp)
SRCS += $(wildcard srcs/classes/Utils/*.cpp)

OBJS := $(SRCS:.cpp=.o)

NAME := dungeonGenerator

COMPILER := clang++

RM		:= rm -f

CFLAGS 	:= -Wall -Werror -Wextra

LIBRARIES := -lSDL2

.c.o:
			${COMPILER} ${CFLAGS} -c $< -o ${<:.c=.o}

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