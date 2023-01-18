# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apigeon <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 16:08:04 by apigeon           #+#    #+#              #
#    Updated: 2023/01/10 16:16:23 by tperes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


### COMPILATION ###
CC		= cc
CFLAGS	= -Wall -Wextra
CFLAGS	+= -Wshadow -Wpedantic -Wuninitialized -Wmissing-include-dirs -Wundef -Winvalid-pch
CFLAGS	+= -Winit-self -Wswitch-enum -Wswitch-default -Wformat-security -Wformat-y2k
CFLAGS	+= -Wdouble-promotion -Wfloat-equal -Wpointer-arith
CFLAGS	+= -MMD -MP
INCLUDE	= -I$(H_DIR) -I$(LIBFT_DIR)/$(H_DIR)
LFLAGS	= -L$(LIBFT_DIR)
LINKS	= -lft -lreadline

### ENV VARIABLES ###
-include .env
DEBUG	?= false
TEST	?= false
NOERROR	?= false
ASAN	?= false

ifeq ($(DEBUG),true)
	CFLAGS	+= -g3
endif

ifeq ($(NOERROR),false)
	CFLAGS	+= -Werror
endif

ifeq ($(ASAN), true)
	CFLAGS	+= -fsanitize=address
endif

ifeq ($(TEST),true)
	SRCS	= test_main.c
else
	SRCS	= main.c
endif

### EXECUTABLE ###
NAME	= minishell

### INCLUDES ###
OBJ_DIR		= bin
SRC_DIR		= src
H_DIR		= incl
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

### SOURCE FILES ###
SRCS	+=	builtins/echo.c \
			builtins/pwd.c \
			builtins/exit.c \
			builtins/cd.c \
			builtins/env.c \
			builtins/export.c \
			builtins/unset.c \
			parser/parse.c \
			parser/lexer.c \
			parser/substitute.c \
			parser/token_utils.c \
			parser/lst_utils.c \
			parser/remove_quotes.c \
			parser/command_utils.c \
			parser/valid_syntax.c \
			parser/tokens_to_commands.c \
			parser/heredoc.c \
			parser/lst_remove_quotes.c \
			parser/create_command.c \
			parser/process_rd.c \
			signal.c \
			signal2.c \
			execution/exec.c \
			execution/pipe.c \
			execution/pipex.c \
			execution/redir.c \
			execution/get_path.c \
			execution/list_to_tab.c \
			utils.c \

### OBJECTS ###
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS	= $(OBJS:.o=.d)

### COLORS ###
RESET	= \033[0m
BLACK	= \034[1;30m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
PURPLE	= \033[1;35m
CYAN	= \033[1;36m
WHITE	= \033[1;37m

### OTHERS ###
UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	VALGRIND = leaks --list --groupByType --atExit --
else
	VALGRIND = valgrind --track-origins=yes --leak-check=full --suppressions=.ignore_readline_leaks
endif

### RULES ###
all:	$(NAME)

$(LIBFT):
	@echo "$(NAME): $(GREEN)Compiling $(LIBFT_DIR)$(RESET)"
	@$(MAKE) addon -C $(LIBFT_DIR)

$(NAME):	$(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(LINKS) -o $(NAME)
	@echo "$(NAME): $(BLUE)Creating program file -> $(WHITE)$(notdir $@)... $(GREEN)[Done]$(RESET)"
	@echo "$(NAME): $(GREEN)Project successfully compiled$(RESET)"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(NAME): $(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(GREEN)[Done]$(RESET)"

run: $(NAME)
	@./$(NAME) $(ARGS)

val: $(NAME)
	@$(VALGRIND) ./$(NAME) $(ARGS)

info:
	@echo "$(BLUE)NAME$(RESET): $(NAME)"
	@echo "$(BLUE)CFLAGS$(RESET): $(CFLAGS)"
	@echo "$(BLUE)INCLUDE$(RESET): $(INCLUDE)"
	@echo "$(BLUE)LFLAGS$(RESET): $(LFLAGS)"
	@echo "$(BLUE)LINKS$(RESET): $(LINKS)"

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(NAME): $(RED)Supressing object files$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(NAME): $(RED)Supressing program file$(RESET)"
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

-include $(DEPS)
