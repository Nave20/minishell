SRC_DIR		= src/
OBJ_DIR		= objs/
INC_DIR		= header/

LIB = libft/libft.a

SRC_FILES	= minishell.c	\

SOURCES		= $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJS		= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

HEADER		= $(INC_DIR)minishell.h

NAME		= minishell

CC			= cc
FLAGS		= -Wall -Wextra -Werror -I$(INC_DIR)

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIB) $(HEADER) Makefile
	$(CC) $(FLAGS) -o $@ $(OBJS)

clean:
	make clean -C libft/
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re