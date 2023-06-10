/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:33:36 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 18:35:56 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_cmd(t_cmds *cmd, char **env_array, t_env *env_list)
{
	ft_execute_in_redirect(cmd, env_list);
	ft_execute_out_redirect(cmd);
	if (!cmd->path_exist)
	{
		printf("minihell: No such file or directory : %s\n", cmd->cmd);
		exit(1);
	}
	if (!cmd->full_cmd || cmd->file_error || cmd->cmd_error)
		exit(1);
	if (execve(cmd->full_cmd[0], cmd->full_cmd, env_array))
		exit(1);
}

void	ft_child_cmd(t_mVars *vars_list, t_cmds *cmd, int index)
{
	if (ft_execute_in_redirect(cmd, vars_list->ls_buffer) || !index)
		ft_close_in_pipes(vars_list, -1);
	else
		ft_close_in_pipes(vars_list, index);
	if (ft_execute_out_redirect(cmd) || index == vars_list->pipe_count)
		ft_close_out_pipes(vars_list, -1);
	else
		ft_close_out_pipes(vars_list, index);
	if (!cmd->path_exist || (!cmd->full_cmd && !ft_is_builtin(cmd->cmd))
		|| cmd->file_error || cmd->cmd_error)
	{
		ft_close_all_pipes(vars_list);
		exit(1);
	}
	if (ft_is_builtin(cmd->cmd))
		ft_execute_buildins(cmd, vars_list);
	else
		execve(cmd->full_cmd[0], cmd->full_cmd, vars_list->env_array);
	exit(0);
}

void	ft_cmds_processing(t_cmds *cmds, t_mVars *vars_list)
{
	t_cmds	*tmp;
	int		count;

	count = 0;
	tmp = cmds;
	ft_child_heredoc(cmds, vars_list);
	while (tmp)
	{
		ft_error_handler(tmp);
		if (!tmp->path_exist)
			printf("minihell: No such file or directory : %s\n", tmp->cmd);
		if ((tmp->redirect & HEREDOC) == HEREDOC)
		{
			count ++;
			tmp = tmp->next;
			continue ;
		}
		vars_list->pids[count] = fork();
		if (vars_list->pids[count] < 0)
			return ((void)printf("minihell: fork() failed\n"));
		else if (vars_list->pids[count] == 0)
			ft_child_cmd(vars_list, tmp, count);
		count ++;
		tmp = tmp->next;
	}
}

void	ft_many_cmd_exe(t_cmds *cmds, t_mVars *vars_list)
{
	int		cmd_count;
	int		count;

	cmd_count = ft_cmd_size(cmds);
	vars_list->pipefd = ft_create_pipes(cmd_count - 1);
	vars_list->pids = ft_create_pid(cmd_count);
	vars_list->pipe_count = cmd_count - 1;
	ft_cmds_processing(cmds, vars_list);
	count = -1;
	ft_close_all_pipes(vars_list);
	while (++count < cmd_count)
		waitpid(vars_list->pids[count], NULL, 0);
}
