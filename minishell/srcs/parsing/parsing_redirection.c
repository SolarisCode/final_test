/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:48:07 by melkholy          #+#    #+#             */
/*   Updated: 2023/05/22 01:47:30 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_add_io_file(char *old_file, char *new_file, int len)
{
	if (old_file)
		free(old_file);
	return (ft_substr(new_file, len, ft_strlen(new_file)));
}

char	**ft_many_redirect(char **old_files, char *new_file, int len)
{
	char	**files;
	int		size;

	size = 0;
	if (!old_files)
	{
		files = (char **)ft_calloc(2, sizeof(char *));
		if (!files)
			return (NULL);
		files[0] = ft_substr(new_file, len, ft_strlen(new_file));
		return (files);
	}
	while (old_files[size])
		size ++;
	files = ft_double_realloc(old_files, size, size + 2);
	files[size] = ft_substr(new_file, len, ft_strlen(new_file));
	return (files);
}

void	ft_arrange_table(char **table, int index, int len)
{
	if (!table[index][len])
	{
		free(table[index]);
		free(table[index + 1]);
		table[index] = NULL;
		table[index + 1] = NULL;
		while (table[index + 2])
		{
			table[index] = table[index + 2];
			index ++;
		}
		table[index] = NULL;
		return ;
	}
	free(table[index]);
	table[index] = table[index + 1];
	while (table[++index])
		table[index] = table[index + 1];
}

int	ft_add_redirection(char **table, t_cmds *cmd, int index, int len)
{
	int	count;
	int	redirect;

	count = 0;
	redirect = ft_get_redirection(table[index]);
	while (table[index][count] && (table[index][count] == '<'
		|| table[index][count] == '>'))
		count ++;
	if (count != len)
		return (printf("%s `%c'\n", DIRECTION_ERR, table[index][0]), 1);
	if (!table[index][len])
	{
		len = 0;
		index ++;
	}
	if (!table[index])
		return (printf("%s `newline'\n", DIRECTION_ERR), 1);
	if (redirect == INPUT)
		cmd->from_file = ft_many_redirect(cmd->from_file, table[index], len);
	else if ((redirect & HEREDOC) == HEREDOC)
		cmd->hdocs_end = ft_many_redirect(cmd->hdocs_end, table[index], len);
	else if ((redirect & OUTPUT) == OUTPUT || (redirect & APPEND) == APPEND)
		cmd->to_file = ft_many_redirect(cmd->to_file, table[index], len);
	return (0);
}

int	ft_get_redirection(char *in_put)
{
	int	count;
	int	result;

	count = 0;
	result = 0;
	while (in_put[count] && in_put[count] == '<')
		count ++;
	result |= count;
	count = 0;
	while (in_put[count] && in_put[count] == '>')
		count ++;
	result |= count << 2;
	return (result);
}

void	ft_apply_priority(t_cmds *cmd, int redirect)
{
	int		len;

	if (redirect > 2)
		return ;
	len = 0;
	if (!cmd->priority)
	{
		cmd->priority = (char *)ft_calloc(2, sizeof(char));
		cmd->priority[0] = (char)(redirect + 48);
		return ;
	}
	len = ft_strlen(cmd->priority);
	cmd->priority = ft_realloc(cmd->priority, len, len + 1);
	cmd->priority[len] = (char)(redirect + 48);
}

int	ft_check_redirect(t_cmds *cmd, char **cmd_table)
{
	int		count;
	int		len;
	int		redirect;

	count = -1;
	while (cmd_table && cmd_table[++count])
	{
		len = 0;
		if (ft_get_redirection(cmd_table[count]))
		{
			redirect = ft_get_redirection(cmd_table[count]);
			len ++;
			if ((redirect & HEREDOC) || (redirect & APPEND))
				len ++;
			cmd->redirect |= redirect;
			if (ft_add_redirection(cmd_table, cmd, count, len))
				return (free(cmd_table), 1);
			ft_apply_priority(cmd, redirect);
			ft_arrange_table(cmd_table, count, len);
			count --;
		}
	}
	return (0);
}
