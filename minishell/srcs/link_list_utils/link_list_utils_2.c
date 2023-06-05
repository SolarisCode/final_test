#include "../../includes/minishell.h"

t_env	*ft_create_envnode(char *string)
{
	t_env	*node;
	char *value;
	char *var;

	value = get_value(string);
	var = 	get_name(string);
	node = (t_env *)ft_calloc(1, sizeof(t_env));
	node->var = var;
	node->value = value;
	return (node);
}

t_env *ft_create_newnode(char *value, char *var)
{
	t_env *node;

	node = (t_env *)ft_calloc(1, sizeof(t_env));
	node->var = var;
	node->value = value;
	return (node);
}

t_env	*ft_get_envp(char **envp)
{
	int		count;
	t_env	*head;
	t_env	*tmp;

	count = 0;
	head = ft_create_envnode(envp[count]);
	if (!head)
		return (NULL);
	tmp = head;
	while (envp[++count])
	{
		tmp->next = ft_create_envnode(envp[count]);
		if (!tmp)
			return (NULL);
		tmp = tmp->next;
	}
	return (head);
}

t_mVars	*ft_create_ls_pointers(char **envp)
{
	t_mVars	*list_pointer;

	list_pointer = (t_mVars *)ft_calloc(1, sizeof(t_mVars));
	list_pointer->ls_env = ft_get_envp(envp);
	list_pointer->ls_export = ft_get_envp(envp);
	list_pointer->ls_buffer = ft_get_envp(envp);
	ft_unset_list(&list_pointer->ls_export, "OLDPWD");
	ft_unset_list(&list_pointer->ls_env, "OLDPWD");
	ft_unset_list(&list_pointer->ls_buffer, "OLDPWD");
	ft_create_cd_variables(list_pointer);
	ft_sort_linked_list(&list_pointer->ls_export);
	return (list_pointer);
}

void ft_create_cd_variables(t_mVars *list_pointer)
{
	t_env *old_path;
	t_env *pwd_path;

	old_path = ft_get_env_node(list_pointer->ls_env, "OLDPWD");
	pwd_path = ft_get_env_node(list_pointer->ls_env, "PWD");
	if (old_path == NULL)
		list_pointer->check_oldpwd_path = UNSET_BEFORE;
	else
		list_pointer->check_oldpwd_path = SET;
	if (pwd_path == NULL)
		list_pointer->check_pwd_path = UNSET_BEFORE;
	else
		list_pointer->check_pwd_path = SET;
	if (ft_get_env_node(list_pointer->ls_env, "HOME") == NULL)
		list_pointer->home = NULL;
	else
		list_pointer->home = ft_strdup(ft_get_env_node(list_pointer->ls_env, "HOME")->value);
}
