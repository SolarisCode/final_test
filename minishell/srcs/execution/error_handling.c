/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:10:09 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 19:15:50 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_file_errors(t_cmds *cmd)
{
	int	count;

	count = -1;
	if (cmd->redirect == INPUT)
		while (cmd->from_file[++count])
			if (access(cmd->from_file[count], F_OK | R_OK))
				cmd->file_error = 1;
	count = -1;
	if ((cmd->redirect & OUTPUT) == OUTPUT
		|| (cmd->redirect & APPEND) == APPEND)
	{
		while (cmd->to_file[++count])
		{
			if (!access(cmd->to_file[count], F_OK | W_OK))
				continue ;
			else if (!access(cmd->to_file[count], F_OK))
				cmd->file_error = 1;
		}
	}
}

void	ft_error_handler(t_cmds *cmd)
{
	char	*error_str;

	error_str = NULL;
	ft_file_errors(cmd);
	if (cmd->file_error)
		g_term_attr.status = 1;
	if (cmd->cmd_error == 126)
	{
		error_str = ft_strjoin("minihell: Permission denied : ", cmd->cmd);
		g_term_attr.status = 126;
	}
	else if (cmd->cmd_error == 127 && cmd->path_exist)
	{
		error_str = ft_strjoin("minihell: Command not found : ", cmd->cmd);
		g_term_attr.status = 127;
	}
	if (error_str)
	{
		write(2, error_str, ft_strlen(error_str));
		write(2, "\n", 1);
		free(error_str);
		error_str = NULL;
	}
}
