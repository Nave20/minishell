SRC_DIR         = src/
OBJ_DIR         = objs/
INC_DIR         = header/

LIB             = libft/libft.a

BUILTINS_DIR    = $(SRC_DIR)builtins/
BUILTINS_OBJDIR = $(OBJ_DIR)builtins/

SRC_FILES       = main.c word_count.c tokenization.c token_definition.c is_something.c lst_create.c set_heredoc.c set_redir_infile.c set_redir_outfile.c handle_cmd_type.c lst_cmd_utils.c find_env_var.c error_check.c free_utils.c last_split.c utils.c new_token_utils.c remove_quotes.c get_env_var.c token_utils.c

BUILTINS_FILES  =

SOURCES         = $(addprefix $(SRC_DIR), $(SRC_FILES)) \
                  $(addprefix $(BUILTINS_DIR), $(BUILTINS_FILES))

OBJS            = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o)) \
                  $(addprefix $(BUILTINS_OBJDIR), $(BUILTINS_FILES:.c=.o))

HEADER          = $(INC_DIR)minishell.h
NAME            = minishell

CC              = cc
FLAGS           = -g3 -Wall -Wextra -Werror -I$(INC_DIR)

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(BUILTINS_OBJDIR)%.o: $(BUILTINS_DIR)%.c $(HEADER)
	mkdir -p $(BUILTINS_OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIB) $(HEADER) Makefile
	$(CC) $(FLAGS) -o $@ $(OBJS) $(LIB) -lreadline

$(LIB) :
	make -C libft/

clean:
	make clean -C libft/
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
