/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:23:57 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 18:26:03 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cmd_size(t_cmds *cmd)
{
	int		count;

	count = 0;
	while (cmd)
	{
		cmd = cmd->next;
		count ++;
	}
	return (count);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "/bin/echo")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "/bin/pwd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "/usr/bin/export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "/usr/bin/unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "/usr/bin/env")
		|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "/usr/bin/exit")
		|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "check_buffer"))
		return (1);
	return (0);
}

int	*ft_create_pid(int proc)
{
	int	*pid;

	pid = (int *)ft_calloc(proc, sizeof(int));
	if (!pid)
		return (NULL);
	return (pid);
}

void	ft_exit_status(t_cmds *cmd)
{
	t_cmds	*last_cmd;

	last_cmd = cmd;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	if (last_cmd->cmd_error)
		g_term_attr.status = last_cmd->cmd_error;
	else if (last_cmd->file_error)
	{
		g_term_attr.status = last_cmd->file_error;
	}
	else
		g_term_attr.status = 0;
}
