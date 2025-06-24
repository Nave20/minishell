SRC_DIR         = src/
OBJ_DIR         = objs/
INC_DIR         = header/

EXEC_DIR        = $(SRC_DIR)exec/
EXEC_OBJDIR     = $(OBJ_DIR)exec/

LIB             = libft/libft.a

BUILTINS_DIR    = $(SRC_DIR)builtins/
BUILTINS_OBJDIR = $(OBJ_DIR)builtins/

EXEC_FILES      =	servo.c				\

SRC_FILES       =	minishell.c			\
					pars_env.c			\
					dev_func.c			\
					terminal.c			\
					main.c				\
					word_count.c		\
					tokenization.c		\
					token_definition.c	\
					is_something.c		\
					put_token.c			\

BUILTINS_FILES  = 	echo.c				\
					cd.c				\
					pwd.c				\
					env.c				\
					export.c			\
					unset.c				\
					exit.c				\
					hub.c				\

SOURCES         = $(addprefix $(SRC_DIR), $(SRC_FILES)) \
                  $(addprefix $(EXEC_DIR), $(EXEC_FILES)) \
                  $(addprefix $(BUILTINS_DIR), $(BUILTINS_FILES))

OBJS            = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o)) \
                  $(addprefix $(EXEC_OBJDIR), $(EXEC_FILES:.c=.o)) \
                  $(addprefix $(BUILTINS_OBJDIR), $(BUILTINS_FILES:.c=.o))

HEADER          = $(INC_DIR)minishell.h
NAME            = minishell

CC              = gcc
FLAGS           = -Wall -Wextra -Werror -I$(INC_DIR)

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(EXEC_OBJDIR)%.o: $(EXEC_DIR)%.c $(HEADER)
	mkdir -p $(EXEC_OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(BUILTINS_OBJDIR)%.o: $(BUILTINS_DIR)%.c $(HEADER)
	mkdir -p $(BUILTINS_OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIB) $(HEADER) Makefile
	$(CC) $(FLAGS) -o $@ $(OBJS) -lreadline $(LIB)

$(LIB):
	make -C libft

clean:
	make clean -C libft/
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re