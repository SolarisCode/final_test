/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 00:02:20 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 16:45:07 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <string.h>

char	*ft_realloc(char *str, int old_size, int new_size)
{
	char	*tmp;
	int		count;

	tmp = (char *)ft_calloc(new_size + 1, sizeof(char));
	count = 0;
	while (count < old_size)
	{
		tmp[count] = str[count];
		count ++;
	}
	free(str);
	return (tmp);
}

char	*ft_find_envpath(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (!ft_strcmp("PATH", current->var))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	ft_free_cmdlist(t_cmds **cmds)
{
	t_cmds	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		*cmds = (*cmds)->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			ft_free_dstr(tmp->args);
		if (tmp->full_cmd)
			ft_free_dstr(tmp->full_cmd);
		if ((tmp->redirect & INPUT))
			ft_free_dstr(tmp->from_file);
		if ((tmp->redirect & HEREDOC))
			ft_free_dstr(tmp->hdocs_end);
		if ((tmp->redirect & OUTPUT) || (tmp->redirect & APPEND))
			ft_free_dstr(tmp->to_file);
		if (tmp->priority)
			free(tmp->priority);
		free(tmp);
		tmp = *cmds;
	}
}

/* Used to check the input and pass it to the parsing and cutting
 functions to get back either a linked list with all the command original
 just one command in a node */
void	ft_parse_input(char *in_put, t_mVars *vars_list)
{
	t_cmds	*cmd;
	int		count;

	count = 0;
	count += ft_isnspace_indx(in_put);
	if (!in_put[count])
		return ;
	cmd = ft_text_analysis(&in_put[count], vars_list->ls_buffer);
	free(in_put);
	if (!cmd)
		return ;
	ft_validate_path(cmd, vars_list);
	ft_cmd_analysis(cmd, vars_list);
}
