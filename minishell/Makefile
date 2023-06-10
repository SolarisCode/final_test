# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 00:02:38 by melkholy          #+#    #+#              #
#    Updated: 2023/06/10 19:30:09 by melkholy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SUCCESS_CLR = \033[32m
RESET_CLR = \033[0m

COLOR	= \033[30m
COLOR_RED = \033[91m
COLOR_BLUE	= \033[94m
RESET	= \033[0m

SOURCES = srcs/main.c \
			srcs/parsing/parsing_utils.c \
			srcs/parsing/assigning_vars.c \
			srcs/parsing/command_path.c \
			srcs/parsing/many_redirection.c \
			srcs/parsing/parsing_redirection.c \
			srcs/lexing/lexer.c \
			srcs/parsing/parser.c \
			srcs/parsing/input_analysis.c \
			srcs/signals/signals.c \
			srcs/execution/cmds_processing.c \
			srcs/execution/error_handling.c \
			srcs/execution/execute_redirection.c \
			srcs/execution/execute_utils.c \
			srcs/execution/execution_analysis.c \
			srcs/execution/heredocs.c \
			srcs/execution/piping.c \
			srcs/link_list_utils/link_list_utils_1.c \
			srcs/link_list_utils/link_list_utils_2.c \
			srcs/link_list_utils/link_list_utils_3.c \
			srcs/builtins/echo.c \
			srcs/builtins/execute_buildins.c \
			srcs/builtins/env.c \
			srcs/builtins/pwd.c \
			srcs/builtins/cd.c \
			srcs/builtins/exit.c \
			srcs/builtins/unset.c \
			srcs/builtins/export.c \
			srcs/builtins/check_buffer.c \
			srcs/builtin_utils/builtins_utils.c \
			srcs/builtin_utils/export_utils_1.c \
			srcs/builtin_utils/cd_utils_1.c \
			srcs/builtin_utils/cd_utils_2.c \

OBJS = $(SOURCES:.c=.o)
NAME = minishell
LIBFT = ./Libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I $(HOME)/goinfre/.brew/opt/readline/include/ -Iincludes
LFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@printf "$(COLOR_BLUE)Compiling $<...$(RESET_CLR)"; \
	$(CC) $(CFLAGS) $(LIBFT) -L$(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline $(OBJS) -o $(NAME) && \
	printf "$(SUCCESS_CLR) Done.$(RESET_CLR)\n" || \
	printf "$(COLOR_RED) Failed.$(RESET_CLR)\n"

# %.o: %.c
# 	@printf "$(COLOR_BLUE)Compiling $<...$(RESET_CLR)"; \
# 	$(CC) $(CFLAGS) -c $< -o $@; \
# 	printf "$(SUCCESS_CLR) Done.$(RESET_CLR)\n"

linux: $(LIBFT) $(SOURCES)
	@printf "$(COLOR_BLUE)Compiling $<...$(RESET_CLR)"; \
	$(CC) $(LFLAGS) $(SOURCES) -L./Libft -Iincludes -lft -L-L/usr/lib/x86_64-linux-gnu/ -lreadline -o $(NAME) && \
	printf "$(SUCCESS_CLR) Done.$(RESET_CLR)\n" || \
	printf "$(COLOR_RED) Failed.$(RESET_CLR)\n"

$(LIBFT):
	make -C Libft
	@echo "$(SUCCESS_CLR)libft - Compiled with success$(RESET_CLR)"

clean:
	@make -C Libft clean
	@echo "$(COLOR_RED)$<clean...$(RESET_CLR)"
	@rm -rf $(OBJS)
	@printf "$(COLOR_LIGHT_RED)"
	@for file in $(OBJS); do \
		echo "$(COLOR_RED) $$file $(RESET_CLR)"; \
	done
	@printf "$(RESET_CLR)"
	@echo "$(SUCCESS_CLR)Object files removed$(RESET_CLR)"

fclean: clean
	@echo "$(COLOR_RED)$<...$(RESET_CLR)"
	@make fclean -C Libft
	@rm -rf $(NAME) minishell.dSYM
	@echo "$(SUCCESS_CLR)$(NAME) - FCleaned with success$(RESET_CLR)"
	@echo "$(COLOR_RED)Removing object files...$(RESET_CLR)"
	@rm -rf $(OBJS)
	@printf "$(COLOR_LIGHT_RED)"
	@ls $(OBJS) 2>/dev/null || true
	@printf "$(RESET_CLR)"
	@echo "$(SUCCESS_CLR)Object files removed$(RESET_CLR)"

re: fclean all

.PHONY: all clean fclean re





# OBJS = $(SOURCES:.c=.o)
# NAME = minishell
# LIBFT = ./Libft/libft.a
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -g -I $(HOME)/goinfre/.brew/opt/readline/include/ -Iincludes

# all: $(NAME)

# $(NAME): $(LIBFT) $(OBJS)
# 	@printf "$(COLOR_BLUE)Compiling $<...$(RESET_CLR)"; \
# 	$(CC) $(CFLAGS) $(LIBFT) -L$(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline $(OBJS) -o $(NAME) && \
# 	printf "$(SUCCESS_CLR) Done.$(RESET_CLR)\n" || \
# 	printf "$(COLOR_RED) Failed.$(RESET_CLR)\n"

# %.o: %.c
# 	@printf "$(COLOR_BLUE)Compiling $<...$(RESET_CLR)"; \
# 	$(CC) $(CFLAGS) -c $< -o $@; \
# 	printf "$(SUCCESS_CLR) Done.$(RESET_CLR)\n"

# $(LIBFT):
# 	make -C Libft
# 	@echo "$(SUCCESS_CLR)libft - Compiled with success$(RESET_CLR)"

# clean:
# 	make -C Libft clean
# 	rm -rf $(OBJS)

# fclean: clean
# 	@printf "$(COLOR_BLUE)Cleaning $<...$(RESET_CLR)"; \
# 	make fclean -C Libft
# 	rm -rf $(NAME) minishell.dSYM
# 	@echo "$(SUCCESS_CLR)$(NAME) - FCleaned with success$(RESET_CLR)"

# re: fclean all

# .PHONY: all clean fclean re
