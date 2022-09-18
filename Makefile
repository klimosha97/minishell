NAME = minishell

SRC =			main.c							\
        		src/errors/ft_error.c			\
        		src/utils/create_env.c			\
        		src/utils/init.c 				\
        		src/utils/clean_arrays.c		\
        		src/parser/search_lextype.c 	\
                src/parser/search_lextype1.c 	\
                src/parser/get_cmds.c			\
                src/parser/lexer.c 				\
                src/parser/parse_words.c 		\
                src/parser/start_parse.c		\
                src/parser/get_values.c			\
                src/pipex/gnl_pipex_bonus.c 	\
                src/pipex/here_doc_bonus.c		\
        		src/pipex/main_bonus.c 			\
                src/pipex/pipex_utils_bonus.c 	\
           		src/pipex/pipex_utils.c			\
           		src/pipex/exec_cmd.c			\
				src/build-in/echo_pwd.c			\
                src/build-in/export.c			\
                src/build-in/unset.c			\
                src/build-in/search_builds.c	\
                src/build-in/cd.c				\
                src/build-in/exit.c				\
                src/utils/signals.c				\
                src/utils/print.c				\

OBJ = $(SRC:.c=.o)

LIBFT = include/libft/libft.a

HEADER = -c -I include/minishell.h

W_FLAGS = -Wall -Werror -Wextra

all: libmake $(NAME)

$(OBJ): %.o: %.c
		gcc -c $(W_FLAGS) -I include/libft/ $< -o $@

libmake:
	-@ make -C include/libft

$(NAME): $(LIBFT) $(OBJ) include/minishell.h
	gcc $(W_FLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C include/libft clean

fclean: clean
	rm -f $(NAME)
	make -C include/libft fclean

re: fclean all

.PHONY:		all clean fclean re libmake