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
PREP_SRC = $(addprefix $(SRC_DIR)prep/, env_parser.c read_input.c env_utils.c)
TOKENIZER_SRC = $(addprefix $(SRC_DIR)tokenizer/, tokenizer.c tokenizer_handlers.c)
LEXER_SRC = $(addprefix $(SRC_DIR)lexer/, lexer.c syntax_checker.c)
PARSER_SRC = $(addprefix $(SRC_DIR)parser/, parser.c pipes.c redirections.c commands.c arguments.c)
EXECUTOR_SRC = $(addprefix $(SRC_DIR)executor/, executor.c exec_file.c built_in.c utils.c utils_2.c get_cmd_path.c export_builtin.c export_2.c echo_builtin.c redirs.c)
EXPANDER_SRC = $(addprefix $(SRC_DIR)expander/, expander.c)
SIGNALS_SRC = $(SRC_DIR)signals.c
MAIN_SRC = $(SRC_DIR)main.c 
TEST_MAIN_SRC = $(SRC_DIR)test_main.c

# All source files combined
SRC = $(PREP_SRC) $(TOKENIZER_SRC) $(PARSER_SRC) $(LEXER_SRC) $(EXPANDER_SRC) $(EXECUTOR_SRC) $(SIGNALS_SRC) $(MAIN_SRC)
TEST_SRC = $(PREP_SRC) $(TOKENIZER_SRC) $(PARSER_SRC) $(LEXER_SRC) $(EXPANDER_SRC) $(EXECUTOR_SRC) $(TEST_MAIN_SRC)

# Object directory
OBJ_DIR = ./obj/

# Object files
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
TEST_OBJ = $(TEST_SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all : $(NAME) test

$(NAME) : $(LIBFT_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) -lreadline

test : $(LIBFT_LIB) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(LIBFT_LIB) -o test_dir/test -lreadline

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT_INC) -c $< -o $@

$(LIBFT_LIB): FORCE
	@$(MAKE) -C $(LIBFT_DIR)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	$(MAKE) -s fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re : fclean all

FORCE:

.PHONY : all clean fclean re

