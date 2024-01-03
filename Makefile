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




#This is the start of the testing framework
TEST_DIR := test

.PHONY: test

test: $(OBJS)
	echo "$(GREEN)Starting tests$(WHITE)"
	if [ -d "$(TEST_DIR)" ]; then make -s run_tests;else echo "$(RED)$(TEST_DIR) directory does not exist$(WHITE)"; fi

test_out: $(OBJS)
	echo "$(GREEN)Starting tests$(WHITE)"
	if [ -d "$(TEST_DIR)" ]; then make -s run_tests_output;else echo "$(RED)$(TEST_DIR) directory does not exist$(WHITE)"; fi

TEST_SRCS := $(shell find ./$(TEST_DIR) -name *test.c) 
TEST_OBJS := $(TEST_SRCS:%.c=$(OBJDIR)/%.o)
NEC_OBJS := $(shell find obj/src -name *.o 2> /dev/null)
TOTAL_TESTS := $(words $(TEST_SRCS))

test2: $(TEST_OBJS)
	echo "$(TEST_SRCS)\n$(TEST_OBJS)\n$(NEC_OBJS)\n$(TOTAL_TESTS)"
	make run_tests

VAL_ERR := 42
VAL_OK_MSG := $(GREEN)[VAL_OK]\n$(WHITE)
VAL_KO_MSG := $(RED)[VAL_KO]\n$(WHITE)
COMP_KO_MSG := $(RED)[COMP_KO]$(WHITE)
COMP_OK_MSG	:= $(GREEN)[COMP_OK]$(WHITE)
EXEC_OK_MSG := $(GREEN)[OK]\n$(WHITE)
EXEC_KO_MSG := $(RED)[KO : $$EXIT_STATUS]\n$(WHITE)
DEV_NULL	:= /dev/null
OUTPUT_FILE := $(DEV_NULL)

run_tests: $(TEST_OBJS)
	for file in $(TEST_OBJS); do \
        echo "\ncompiling and running $${file}" && \
		if cc $${file} $(NEC_OBJS) -w -o whoa 2>$(DEV_NULL); then \
			echo "$(COMP_OK_MSG)" && \
			./whoa > $(DEV_NULL) ; \
			EXIT_STATUS=$$?; \
			if [ $$EXIT_STATUS -eq 0 ]; then \
				printf "$(EXEC_OK_MSG)"; \
			else \
				printf "$(EXEC_KO_MSG)"; \
			fi; \
			valgrind --leak-check=full --error-exitcode=$(VAL_ERR) ./whoa > $(DEV_NULL) 2>&1; \
			EXIT_STATUS=$$?; \
			if [ $$EXIT_STATUS -eq $(VAL_ERR) ]; then \
				printf "$(VAL_KO_MSG)"; \
			else \
				printf "$(VAL_OK_MSG)"; \
			fi; \
		else \
			echo "$(COMP_KO_MSG)"; \
		fi; \
	done
	rm whoa


run_tests_output: $(TEST_OBJS)
	$(eval LOG_COUNT := $(words $(shell find ./$(TEST_DIR)/log -name *log*.txt)))
	$(eval OUTPUT_FILE := $(TEST_DIR)/log/test_log_$(LOG_COUNT).txt)
	mkdir -p $(TEST_DIR)/log
	printf "storing log in $(OUTPUT_FILE)\n"
	for file in $(TEST_OBJS); do \
		echo "\n\nlog start $${file}\n" >> $(OUTPUT_FILE); \
        echo "\ncompiling and running $${file}" && \
		if cc $${file} $(NEC_OBJS) -w -o whoa 2>>$(OUTPUT_FILE); then \
			echo "$(COMP_OK_MSG)" && \
			./whoa >> $(OUTPUT_FILE) ; \
			EXIT_STATUS=$$?; \
			if [ $$EXIT_STATUS -eq 0 ]; then \
				printf "$(EXEC_OK_MSG)"; \
			else \
				printf "$(EXEC_KO_MSG)"; \
			fi; \
			valgrind --leak-check=full --error-exitcode=$(VAL_ERR) ./whoa >> $(OUTPUT_FILE) 2>> $(OUTPUT_FILE); \
			EXIT_STATUS=$$?; \
			if [ $$EXIT_STATUS -eq $(VAL_ERR) ]; then \
				printf "$(VAL_KO_MSG)"; \
			else \
				printf "$(VAL_OK_MSG)"; \
			fi; \
		else \
			echo "$(COMP_KO_MSG)"; \
		fi; \
	done
	rm whoa
