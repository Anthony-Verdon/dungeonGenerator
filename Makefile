SRCS := $(wildcard srcs/*.cpp)
SRCS += $(wildcard srcs/classes/SDL/*.cpp)
SRCS += $(wildcard srcs/classes/Texture/*.cpp)
SRCS += $(wildcard srcs/classes/Utils/*.cpp)
SRCS += $(wildcard srcs/classes/DungeonGenerator/*.cpp)
SRCS += $(wildcard srcs/classes/Tile/*.cpp)

OBJS := $(SRCS:.cpp=.o)

NAME := dungeonGenerator

COMPILER := clang++

RM		:= rm -f

CFLAGS 	:= -Wall -Werror -Wextra -g

LIBRARIES := -lSDL2 -Ljsoncpp_x64-linux/lib -ljsoncpp

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