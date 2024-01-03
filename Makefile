.SILENT:
.PHONY: all re build post_build pre_build progress-bar update-progress clean fclean
DEFAULT_GOAL: all

#ansi escape codes
UP :=				\033[A
CLEAR :=			\e[2K
CLEAR_TILL_END :=	\e[0K

SET_BOLD_MODE := 			\e[1m
SET_DIM_MODE := 			\e[2m
SET_ITALIC_MODE := 			\e[3m
SET_UNDERLINE_MODE := 		\e[4m
SET_BLINKING_MODE := 		\e[5m
SET_INVERSE_MODE := 		\e[7m
SET_HIDDEN_MODE := 			\e[8m
SET_STRIKETHROUGH_MODE := 	\e[9m

RESET_BOLD_MODE := 			\e[22m
RESET_DIM_MODE := 			\e[22m
RESET_ITALIC_MODE := 		\e[23m
RESET_UNDERLINE_MODE := 	\e[24m
RESET_BLINKING_MODE := 		\e[25m
RESET_INVERSE_MODE := 		\e[27m
RESET_HIDDEN_MODE := 		\e[28m
RESET_STRIKETHROUGH_MODE := \e[29m
RESET_ALL := 				\e[0m

BLACK_BACK := 	\e[40m
RED_BACK := 	\e[101m
GREEN_BACK := 	\e[102m
YELLOW_BACK :=	\e[103m
BLUE_BACK := 	\e[104m
MAGENTA_BACK := \e[105m
CYAN_BACK := 	\e[106m
WHITE_BACK := 	\e[107m
RED :=			\e[91m
GREEN := 		\e[92m
YELLOW := 		\e[93m
BLUE := 		\e[94m
MAGENTA := 		\e[95m
CYAN := 		\e[96m
WHITE := 		\e[97m


#Progress bar rules and generic compilation and build rules

NAME := TEMPLATE

OBJDIR := obj
SRCS := $(shell find src -type f -name "*.c") $(shell find . -maxdepth 1 -type f -name "main.c")
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
TOTAL_TASKS:= $(words $(SRCS))
CURRENT_TASK:= 0
PROGRESS_FILE:= .progress

progress-bar:
	$(eval CURRENT_TASK=$(shell cat $(PROGRESS_FILE)))
	printf "["
	for i in $(shell seq 1 $(CURRENT_TASK)); do \
        printf "="; \
    done
	for i in $(shell seq $(CURRENT_TASK) $(TOTAL_TASKS)); do \
        printf " "; \
    done
	printf "]"
	printf " ($(CURRENT_TASK)/$(TOTAL_TASKS))"

update-progress:
	$(shell touch $(PROGRESS_FILE))
	$(eval CURRENT_TASK=$(shell cat $(PROGRESS_FILE)))
	$(eval CURRENT_TASK=$(shell echo $$(($(CURRENT_TASK)+1))))
	echo "$(CURRENT_TASK)" > $(PROGRESS_FILE)
	$(MAKE) progress-bar

$(OBJDIR)/%.o: %.c $(HEADERS)
				$(MAKE) update-progress
				mkdir -p $(@D) 
				$(CC) $(CFLAGS) -c $< -o $@
				echo  "\t$(CLEAR)compiling $@"
				printf "$(CLEAR)$(UP)"


clean:
				rm -rf $(OBJDIR)
				rm -f $(PROGRESS_FILE)
				echo "$(YELLOW)removed objects from $(NAME)$(WHITE)"

fclean: 	
				make clean
				rm -f $(NAME)
				echo "$(YELLOW)removed $(NAME)$(WHITE)"

re: fclean all

all: build

build:			
	make pre_build 
	make $(NAME)
	make post_build
	
pre_build:
	echo "$(GREEN)Creating $(NAME)$(WHITE)"
	echo "0" > $(PROGRESS_FILE)

$(NAME): $(OBJS)
	cc $(OBJS) -o $(NAME)
	echo "$(RED_BACK)MAKE YOUR OWN (NAME) RULE$(BLACK_BACK)"

post_build:
	echo "$(CLEAR)$(GREEN)Created $(NAME)$(WHITE)"
	$(shell rm -rf $(PROGRESS_FILE))




