#include "minishell.h"

void ft_unset_list(t_env **list_pointer, char *string)
{
	t_env *search_node;
	t_env *previous_node;

	search_node = ft_get_env_node(*list_pointer, string);
	if (search_node == NULL)
		return;
	if (search_node == *list_pointer)
	{
		t_env *tmp;
		tmp = *list_pointer;
		*list_pointer = (*list_pointer)->next;
		ft_free_node(tmp);
	}
	else
	{
		previous_node = ft_find_previous_node(*list_pointer, search_node);
		previous_node->next = search_node->next;
		ft_free_node(search_node);
	}
}

void ft_unset(t_cmds *cmd, t_mVars *list_pointer)
{
	int i;

	i = 0;
	if (!cmd->args)
		return;
	while (cmd->args[i])
	{
		ft_unset_list(&list_pointer->ls_export, cmd->args[i]);
		ft_unset_list(&list_pointer->ls_env, cmd->args[i]);
		ft_unset_list(&list_pointer->ls_buffer, cmd->args[i]);
		i++;
	}
}





