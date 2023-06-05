
#include "../../includes/minishell.h"

// int	ft_own_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	if (ft_strlen(s1) != ft_strlen(s2))
// 		return (1);
// 	while (s1[i] && s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

t_env *ft_get_env_node(t_env *head_ref, char *search)
{
	t_env *current;

	if (!(head_ref))
		return NULL;
	current = head_ref;
	while (current != NULL)
	{
		if (ft_strcmp(current->var, search) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}
// NAME = minishell

// CC = cc
// READLINE =
// CCFLAG = -Wall -Werror -Wextra -g
// # -fsanitize=address
// # -fprofile-instr-generate -fcoverage-mapping

/* SRCS =	main.c \
 		./builtins/builtins.c \
 		./builtins/builtins_utils.c \
 		./builtins/change_env.c \
 		./builtins/link_list.c \
 		./builtins/export_utils.c \
 							\
 		./parsing/lex_check_input.c \
 		./parsing/main_run_fcts.c \
 		./parsing/par_clean_up.c \
 		./parsing/par_helpers.c \
 		./parsing/par_init_utils.c \
 									\
 		test_eike.c

// D_SRCS = ./srcs/
// SRC = $(addprefix $(D_SRCS), $(SRCS))

// LIB = libft.a
// D_LIB = ./libft/

// SUCCESS_CLR = \033[32m
// RESET_CLR = \033[0m

// COLOR	= \033[30m
// RESET	= \033[0m

// OBJ = $(SRC:.c=.o)

// all : $(NAME)

// %.o:%.c
// 	@$(CC) $(CCFLAG) -I $(HOME)/goinfre/.brew/opt/readline/include/ -o $@ -c $<

// $(NAME) : $(OBJ) $(LIB)
// 	@$(CC) $(CCFLAG) $(OBJ) $(D_LIB)$(LIB) -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline -o $(NAME)
// 	@echo "$(SUCCESS_CLR)$(NAME) - Compiled with success$(RESET_CLR)"

// $(LIB) :
// 	@make -C $(D_LIB)
// 	@echo "$(SUCCESS_CLR)libft - Compiled with success$(RESET_CLR)"

// clean :
// 	@make clean -C $(D_LIB)
// 	@rm -f $(OBJ)
// 	@echo "$(SUCCESS_CLR)$(NAME) - Cleaned with success$(RESET_CLR)"

// fclean : clean
// 	@make fclean -C $(D_LIB)
// 	@rm -f $(NAME)
// 	@echo "$(SUCCESS_CLR)$(NAME) - FCleaned with success$(RESET_CLR)"

// re : fclean all
// $(shell cd /path/to/directory && command)

// gitbranch :
// #	$(shell bash mgit.sh)
// 	$(shell git add .)

// # Prompt user to enter commit message
// 	$(shell git commit -m)

// # Commit changes with the entered message
// #	$(shell git commit -m "${commit_message}")

// # Push changes to remote repository
// 	$(shell git push)

// # Output success message
// #	$(shell echo "Git auto add & push with message performed.") */
