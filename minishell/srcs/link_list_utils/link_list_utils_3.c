#include "minishell.h"

void ft_pushfront_string_env(t_env **head_ref, char *data)
{
	t_env *new_node;

	new_node = ft_create_envnode(data);
	new_node->next = (*head_ref);
	*head_ref = new_node;
}

void ft_print_char(void* data)
{
	ft_putstr_fd((char *)data, 1);
}

void ft_print_list(t_env *head, void (*print)(void*))
{
	t_env *current = head;
	while (current != NULL)
	{
		(*print)(current->var);
		write(1, "=", 1);
		(*print)(current->value);
		write(1, "\n", 1);
		current = current->next;
	}
}

void ft_print_list_export(t_env *head, void (*print)(void*))
{
	t_env *current = head;
	while (current != NULL)
	{
		write(1, "declare -x ", 11);
		(*print)(current->var);
		write(1, "=", 1);
		write(1, "\"", 1);
		(*print)(current->value);
		write(1, "\"", 1);
		write(1, "\n", 1);
		current = current->next;
	}
}

t_env	*ft_find_previous_node(t_env *head_ref, t_env *node)
{
	t_env *current;

	if (!head_ref)
			return NULL;
	if (head_ref == node)
		return (head_ref);
	current = head_ref;
	while (current->next != node)
		current = current->next;
	return (current);
}
