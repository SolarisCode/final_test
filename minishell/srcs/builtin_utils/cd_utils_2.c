#include "../../includes/minishell.h"

char *ft_get_new_path(char *s)
{
	int len;
	int i;
	char *new_path;
	len = ft_strlen(s) - 1;
	i = 0;
	while (s[len] != '/')
		len--;
	if (len == 0)
		len = 1;
	new_path = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		new_path[i] = s[i];
		i++;
	}
	new_path[len] = '\0';
	return (new_path);
}

void ft_update_variable_cd(t_env *node, char *new_value)
{
	free(node->value);
	node->value = NULL;
	node->value = new_value;
}

void ft_create_add_variable(t_env **head_ref, char *var, char *value)
{
	t_env *new_node;

	new_node = ft_create_newnode(value, var);
	ft_add_back(head_ref, new_node);
}

void ft_update_all(t_mVars *list_pointer, char *var)
{
	ft_update_variable_cd(ft_get_env_node(list_pointer->ls_env, var), ft_strdup(list_pointer->cwd));
	ft_update_variable_cd(ft_get_env_node(list_pointer->ls_export, var), ft_strdup(list_pointer->cwd));
	ft_update_variable_cd(ft_get_env_node(list_pointer->ls_buffer, var), ft_strdup(list_pointer->cwd));
}

void ft_create_add_all(t_mVars *list_pointer, char *var)
{
	ft_create_add_variable(&list_pointer->ls_env, ft_strdup(var), ft_strdup(list_pointer->cwd));
	ft_create_add_variable(&list_pointer->ls_export, ft_strdup(var), ft_strdup(list_pointer->cwd));
	ft_create_add_variable(&list_pointer->ls_buffer, ft_strdup(var), ft_strdup(list_pointer->cwd));
	ft_sort_linked_list(&list_pointer->ls_export);
}
