#include "minishell.h"

void ft_check_buffer(t_mVars *list_pointer)
{
	ft_print_list_export(list_pointer->ls_buffer, ft_print_char);
}
