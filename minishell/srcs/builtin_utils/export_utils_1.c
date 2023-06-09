/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:14:57 by estruckm          #+#    #+#             */
/*   Updated: 2023/06/09 21:14:58 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value(char *string)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (string[i])
	{
		if (string[i] == '=')
		{
			while (string[i + j])
			{
				j++;
			}
			break ;
		}
		i++;
	}
	value = ft_substr(string, i + 1, j);
	return (value);
}

char	*get_name(char *string)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	while (string[i] && string[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		name[j] = string[j];
		j++;
	}
	name[i] = '\0';
	return (name);
}

int	ft_check_validity(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '=')
		return (1);
	while (s[i] && s[i] != '=')
	{
		if (ft_isalpha(s[i]) == 0 && ft_isdigit(s[i]) == 0 && s[i] != '_')
			return (1);
		i++;
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == '=' && s[i + 1] != '=' && s[i + 1] != '\0')
			return (2);
		if (s[i] == '=' && !s[i + 1])
			return (3);
		i++;
	}
	return (0);
}

void	ft_update_variable(t_env *node, char *new_value)
{
	free(node->value);
	node->value = NULL;
	node->value = new_value;
}

void	update_or_create(t_env *list_pointer, char *string)
{
	t_env	*search_node;
	char	*value;
	char	*var;

	value = get_value(string);
	var = get_name(string);
	search_node = ft_get_env_node(list_pointer, var);
	if (search_node == NULL)
	{
		search_node = ft_create_newnode(value, var);
		ft_add_back(&list_pointer, search_node);
	}
	else
	{
		if (ft_check_validity(string) != 0)
		{
			ft_update_variable(search_node, value);
			printf("value %s, var %s \n", value, var);
		}
		else
			free(value);
		free(var);
	}
}
