/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:40:23 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 19:14:35 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_validate_cmd(t_cmds *cmd, char **env_path)
{
	char	*cmd_path;
	int		count;

	count = -1;
	cmd_path = NULL;
	while (env_path[++count])
	{
		cmd_path = ft_strjoin(env_path[count], cmd->cmd);
		if (!access(cmd_path, F_OK))
		{
			if (access(cmd_path, X_OK))
				cmd->cmd_error = 126;
			break ;
		}
		free(cmd_path);
		cmd_path = NULL;
	}
	if (!cmd_path)
		cmd->cmd_error = 127;
	return (cmd_path);
}

void	ft_create_fullcmd(t_cmds *cmd)
{
	char	**full_cmd;
	int		count;

	count = 0;
	if (!cmd->cmd)
		return ;
	full_cmd = (char **)ft_calloc(1, sizeof(char *));
	full_cmd[count] = ft_strdup(cmd->cmd);
	full_cmd = ft_double_realloc(full_cmd, count + 1, count + 2);
	while (cmd->args && cmd->args[count])
	{
		full_cmd[count + 1] = ft_strdup(cmd->args[count]);
		count ++;
		full_cmd = ft_double_realloc(full_cmd, count + 1, count + 2);
	}
	cmd->full_cmd = full_cmd;
}

int	ft_add_path(t_cmds *cmd, t_env *env_list)
{
	char	*cmd_path;
	char	**env_path;
	int		count;

	cmd_path = NULL;
	count = -1;
	if (!access(cmd->cmd, F_OK))
	{
		if (access(cmd->cmd, X_OK))
			cmd->cmd_error = 126;
		return (0);
	}
	env_path = ft_split(ft_find_envpath(env_list), ':');
	while (env_path[++count])
		env_path[count] = ft_strjoin_free(env_path[count], "/");
	cmd_path = ft_validate_cmd(cmd, env_path);
	ft_free_dstr(env_path);
	if (!cmd_path)
		return (1);
	free(cmd->cmd);
	cmd->cmd = cmd_path;
	return (0);
}

int	ft_mark_path(t_cmds *cmd, t_mVars *vars_list)
{
	char	*found_path;
	t_cmds	*tmp;

	found_path = ft_find_envpath(vars_list->ls_env);
	if (found_path)
		return (0);
	tmp = cmd;
	while (tmp)
	{
		if (!access(tmp->cmd, F_OK)
			|| (ft_strcmp(tmp->cmd, "env") && ft_is_builtin(tmp->cmd)))
		{
			if (access(tmp->cmd, X_OK) && !ft_is_builtin(tmp->cmd))
				tmp->cmd_error = 126;
			if (!ft_is_builtin(tmp->cmd))
				ft_create_fullcmd(tmp);
			tmp->path_exist = 1;
		}
		else
			tmp->cmd_error = 127;
		tmp = tmp->next;
	}
	return (1);
}

void	ft_validate_path(t_cmds *cmd, t_mVars *vars_list)
{
	t_cmds	*tmp;

	if (ft_mark_path(cmd, vars_list))
		return ;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->cmd && (ft_check_validity(tmp->cmd) == 2
				|| ft_check_validity(tmp->cmd) == 3))
			ft_check_assigning(tmp, vars_list);
		if (tmp->cmd && !ft_is_builtin(tmp->cmd))
			if (!ft_add_path(tmp, vars_list->ls_buffer))
				ft_create_fullcmd(tmp);
		tmp->path_exist = 1;
		tmp = tmp->next;
	}
}
