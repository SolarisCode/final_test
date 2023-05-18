/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:24:17 by estruckm          #+#    #+#             */
/*   Updated: 2023/05/18 14:39:48 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execute_buildins(t_cmds *cmd, t_mVars *list_pointer)
{
	if (!ft_strcmp(cmd->cmd, "echo") || !ft_strcmp(cmd->cmd, "/bin/echo"))
		ft_echo(cmd);
	if (!ft_strcmp(cmd->cmd, "env") || !ft_strcmp(cmd->cmd, "/usr/bin/env"))
		ft_env(list_pointer);
	if (!ft_strcmp(cmd->cmd, "pwd") || !ft_strcmp(cmd->cmd, "/bin/pwd"))
		ft_pwd();
	// if (!ft_strcmp(cmd->cmd, "cd") || !ft_strcmp(cmd->cmd, "/usr/bin/cd"))
	// 	ft_cd(cmd, list_pointer);
	if (!ft_strcmp(cmd->cmd, "export") || !ft_strcmp(cmd->cmd, "/usr/bin/export"))
		ft_export(cmd, list_pointer);
	if (!ft_strcmp(cmd->cmd, "check_buffer"))
		ft_check_buffer(list_pointer);
	if (!ft_strcmp(cmd->cmd, "unset") || !ft_strcmp(cmd->cmd, "/usr/bin/unset"))
		ft_unset(cmd, list_pointer);
	if (!ft_strcmp(cmd->cmd, "exit") || !ft_strcmp(cmd->cmd, "/usr/bin/exit"))
		ft_exit();
	if (!ft_strcmp(cmd->cmd, "cd"))
		ft_cd(cmd, list_pointer);
}
