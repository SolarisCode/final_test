/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:22:20 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 17:24:21 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_infile_fd(char *file)
{
	int	infile;

	infile = 0;
	if (!file)
		return (-1);
	if (access(file, F_OK | R_OK))
	{
		printf("minihell: %s : %s\n", strerror(errno), file);
		return (-1);
	}
	infile = open(file, O_RDONLY);
	return (infile);
}

void	ft_outfile_fd(char *to_file, int redirect)
{
	int	outfile;
	int	flag;

	flag = 0;
	outfile = 0;
	if (redirect & OUTPUT)
		flag |= O_TRUNC;
	else if (redirect & APPEND)
		flag |= O_APPEND;
	if (!access(to_file, F_OK | W_OK))
		outfile = open(to_file, O_WRONLY | flag);
	else if (!access(to_file, F_OK))
		printf("minihell: %s: %s\n", strerror(errno), to_file);
	else
		outfile = open(to_file, O_RDWR | O_CREAT | flag, 0666);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
}

int	ft_execute_in_redirect(t_cmds *cmd, t_env *env_list)
{
	int	infile_count;
	int	count;
	int	fd;

	count = -1;
	fd = -1;
	infile_count = -1;
	while (cmd->priority && cmd->priority[++count])
	{
		if (fd > 0)
			close(fd);
		if (cmd->priority[count] == '1')
			fd = ft_infile_fd(cmd->from_file[++infile_count]);
		else if (cmd->priority[count] == '2')
			fd = ft_here_doc(cmd->hdocs_end++, env_list);
	}
	if (fd > 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (1);
	}
	return (0);
}

int	ft_execute_out_redirect(t_cmds *cmd)
{
	int	count;

	count = -1;
	if ((cmd->redirect & OUTPUT) || (cmd->redirect & APPEND))
	{
		while (cmd->to_file[++count])
			ft_outfile_fd(cmd->to_file[count], cmd->redirect);
		return (1);
	}
	return (0);
}
