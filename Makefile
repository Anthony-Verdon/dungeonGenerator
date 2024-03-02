SRCS := $(wildcard srcs/*.cpp)
SRCS += $(wildcard srcs/classes/SDL/*.cpp)
SRCS += $(wildcard srcs/classes/Texture/*.cpp)
SRCS += $(wildcard srcs/classes/Utils/*.cpp)
SRCS += $(wildcard srcs/classes/DungeonGenerator/*.cpp)
SRCS += $(wildcard srcs/classes/fileGenerator/*.cpp)
SRCS += $(wildcard srcs/classes/ruleFileParser/*.cpp)
SRCS += $(wildcard srcs/classes/Tile/*.cpp)

OBJS := $(SRCS:.cpp=.o)

NAME := dungeonGenerator

COMPILER := clang++

RM		:= rm -f

CFLAGS 	:= -Wall -Wextra -g $(shell pkg-config gtkmm-3.0 --cflags)
LIBRARIES := -lSDL2 -Llibs/jsoncpp_x64-linux/lib -ljsoncpp -Llibs/SDL2_ttf/build -lSDL2_ttf-2.0 $(shell pkg-config gtkmm-3.0 --libs)

.cpp.o:
			${COMPILER} ${CFLAGS} -c $< -o ${<:.cpp=.o}

all: 		${NAME}

${NAME}:	${OBJS}
			${COMPILER} ${OBJS} -o ${NAME} ${LIBRARIES}

clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re:
			make fclean
			make

.PHONY: 	all clean fclean re