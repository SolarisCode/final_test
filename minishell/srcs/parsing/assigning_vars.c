/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigning_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:43:55 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 19:13:40 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_in_export(char *str, t_mVars *vars_list)
{
	t_env	*in_export;
	char	*name;

	name = get_name(str);
	in_export = ft_get_env_node(vars_list->ls_export, name);
	free(name);
	if (in_export)
	{
		update_or_create(vars_list->ls_export, str);
		update_or_create(vars_list->ls_env, str);
		update_or_create(vars_list->ls_buffer, str);
		return (0);
	}
	return (1);
}

char	**ft_arrange_args(char **args)
{
	char	**new_args;
	int		len;

	if (!args[0] || !args[1])
		return (NULL);
	len = 0;
	while (args[len])
		len ++;
	new_args = (char **)ft_calloc(len, sizeof(char *));
	len = 0;
	while (args[++len])
		new_args[len - 1] = args[len];
	return (new_args);
}

void	ft_check_assigning(t_cmds *cmd, t_mVars *vars_list)
{
	int		count;
	char	**tmp;

	count = -1;
	if (ft_check_in_export(cmd->cmd, vars_list))
		update_or_create(vars_list->ls_buffer, cmd->cmd);
	while (cmd->args && cmd->args[++count])
	{
		if (ft_check_validity(cmd->args[count]) == 2
			|| ft_check_validity(cmd->args[count]) == 3)
		{
			if (ft_check_in_export(cmd->args[count], vars_list))
				update_or_create(vars_list->ls_buffer, cmd->args[count]);
		}
		else
			break ;
	}
	free(cmd->cmd);
	cmd->cmd = NULL;
	if (!cmd->args || cmd->args[count])
		return ;
	cmd ->cmd = cmd->args[count];
	tmp = cmd->args;
	cmd->args = ft_arrange_args(&cmd->args[count]);
	ft_free_dstr(tmp);
}
