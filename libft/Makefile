SRCS 	= ft_atoi.c \
		ft_atoi_base.c \
		  ft_free_array.c \
		  ft_bzero.c \
		  ft_isalnum.c \
		  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memset.c \
		  ft_strchr.c \
		  ft_strlcat.c \
		  ft_strlcpy.c \
		  ft_strlen.c \
		  ft_strncmp.c \
		  ft_strnstr.c \
		  ft_strrchr.c \
		  ft_tolower.c \
		  ft_toupper.c \
		  ft_calloc.c \
		  ft_strdup.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_itoa.c \
		  ft_strmapi.c \
		  ft_striteri.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_lstnew.c \
		  ft_lstadd_front.c \
		  ft_lstsize.c \
		  ft_lstlast.c \
		  ft_lstadd_back.c \
		  ft_lstdelone.c \
		  ft_lstclear.c \
		  ft_lstiter.c \
		  ft_lstmap.c \
		  gnl/get_next_line.c \
		  gnl/get_next_line_utils.c \
		  ft_strcmp.c \
		  ft_split_multiple_arg.c \
		  ft_strtrim_start.c \
		  ft_strcut.c \
		  ft_strcut_end.c \
		  ft_split_quotes.c \
		  ft_atoll.c \
		  ft_lltoa.c \
		  extension.c \
		  ft_split_parenthesis.c \
		  ft_split_quotes_parenthesis.c \
		  ft_strdup_suppress_quotes.c \
		  ft_lstwall/ft_lstwall_new.c \
		  ft_lstwall/ft_lstwall_add_front.c \
		  ft_lstwall/ft_lstwall_size.c \
		  ft_lstwall/ft_lstwall_last.c \
		  ft_lstwall/ft_lstwall_add_back.c \
		  ft_lstwall/ft_lstwall_delone.c \
		  ft_lstwall/ft_lstwall_clear.c \
		  ft_lstsec/ft_lstsec_new.c \
		  ft_lstsec/ft_lstsec_add_front.c \
		  ft_lstsec/ft_lstsec_size.c \
		  ft_lstsec/ft_lstsec_last.c \
		  ft_lstsec/ft_lstsec_add_back.c \
		  ft_lstsec/ft_lstsec_delone.c \
		  ft_lstsec/ft_lstsec_clear.c \
		  append_to_tab.c \
		  srcs_double_list/ft_double_lstadd_back.c \
		  srcs_double_list/ft_double_lstadd_front.c \
		  srcs_double_list/ft_double_lstclear.c \
		  srcs_double_list/ft_double_lstdelone.c \
		  srcs_double_list/ft_double_lstlast.c \
		  srcs_double_list/ft_double_lstnew.c \
		  srcs_double_list/ft_double_lstsize.c

OBJS 	= ${SRCS:.c=.o}

NAME 	= libft.a

COMPILER= clang

RM		= rm -f

CFLAGS 	= -Wall -Werror -Wextra

LIBRARY = ft_dprintf/libftdprintf.a

all: 		${NAME}

.c.o:		${OBJS}
			${COMPILER} ${CFLAGS} -c $< -o ${<:.c=.o}
	
${NAME}:	${OBJS}
			make -C ft_dprintf
			ar rcs ${NAME} ${OBJS} ${LIBRARY}

clean: 	
			${RM} ${OBJS} 
			make -C ft_dprintf clean

fclean: 	clean
			${RM} ${NAME}
			make -C ft_dprintf fclean
	
re: 		fclean all

.PHONY: 	all clean fclean re
