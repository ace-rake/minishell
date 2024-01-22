CC = cc
CFLAGS = -Wall -Werror -Wextra -g
NAME = minishell

# Header files directory
INC_DIR = ./inc/
INCLUDES = -I $(INC_DIR)

# Libft settings
LIBFT_DIR = ./libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
LIBFT_INC = -I $(LIBFT_DIR)inc/

# Source files
SRC_DIR = ./src/
PREP_SRC = $(addprefix $(SRC_DIR)prep/, env_parser.c read_input.c)
TOKENIZER_SRC = $(addprefix $(SRC_DIR)tokenizer/, tokenizer.c tokenizer_handlers.c)
LEXER_SRC = $(addprefix $(SRC_DIR)lexer/, lexer.c syntax_checker.c)
PARSER_SRC = $(addprefix $(SRC_DIR)parser/, parser.c pipes.c redirections.c commands.c arguments.c)
EXECUTOR_SRC = $(addprefix $(SRC_DIR)executor/, executor.c exec_file.c built_in.c utils.c)
MAIN_SRC = $(SRC_DIR)main.c

# All source files combined
SRC = $(TOKENIZER_SRC) $(PARSER_SRC) $(LEXER_SRC) $(EXECUTOR_SRC) $(MAIN_SRC)

# Object files
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(LIBFT_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) -lreadline

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT_INC) -c $< -o $@

$(LIBFT_LIB): FORCE
	@$(MAKE) -C $(LIBFT_DIR)

clean :
	rm -f $(OBJ)

fclean : clean
	$(MAKE) -s fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re : fclean all

FORCE:

.PHONY : all clean fclean re

