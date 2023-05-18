#include "minishell.h"

void ft_env(t_mVars *list_pointer)
{
	ft_print_list(list_pointer->ls_env, ft_print_char);
}
