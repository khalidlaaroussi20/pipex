CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = pipex.c srcs/command_helper.c srcs/pipex_errors.c srcs/pipex_utils.c srcs/pipes_helper.c \
	includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c \
	includes/libft/libft.a 
NAME = pipex
RM = rm -f

ALL:${NAME}

${NAME}:
	cd includes/libft/ && make && cd ../..
	${CC} ${CFLAGS} ${SRC} -o ${NAME}
clean:
	${RM} /includes/libft/*.o
fclean:clean
	${RM} ${NAME} includes/libft/libft.a
re: fclean ALL