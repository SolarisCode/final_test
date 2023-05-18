/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 00:02:20 by melkholy          #+#    #+#             */
/*   Updated: 2023/05/19 01:33:29 by melkholy         ###   ########.fr       */
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

// void	ft_arrange_args(t_cmds *cmd, int index, int len)
// {
// 	if (!cmd->args[index][len])
// 	{
// 		free(cmd->args[index]);
// 		free(cmd->args[index + 1]);
// 		while (cmd->args[index + 2])
// 		{
// 			cmd->args[index] = cmd->args[index + 2];
// 			index ++;
// 		}
// 		cmd->args[index] = NULL;
// 		return ;
// 	}
// 	free(cmd->args[index]);
// 	cmd->args[index] = cmd->args[index + 1];
// 	while (cmd->args[++index])
// 		cmd->args[index] = cmd->args[index + 1];
// }

// char	**ft_cmd_table(char **cmd_table, char *str, int index)
// {
// 	cmd_table[index] = ft_strdup(str);
// 	cmd_table = ft_double_realloc(cmd_table, index + 1, index + 2);
// 	free(str);
// 	return (cmd_table);
// }
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
	return (cmd_path);
}

int	ft_add_path(t_cmds *cmd, t_env *env_list)
{
	char	*cmd_path;
	char	**env_path;
	int		count;

	cmd_path = NULL;
	count = -1;
	env_path = ft_split(ft_find_envpath(env_list), ':');
	while (env_path[++count])
		env_path[count] = ft_strjoin_free(env_path[count], "/");
	// count = -1;
	// while (env_path[++count])
	// {
	// 	cmd_path = ft_strjoin(env_path[count], cmd->cmd);
	// 	if (!access(cmd_path, F_OK | X_OK))
	// 		break ;
	// 	free(cmd_path);
	// 	cmd_path = NULL;
	// }
	cmd_path = ft_validate_cmd(cmd, env_path);
	ft_free_dstr(env_path);
	if (!cmd_path)
	{
		if (cmd->cmd_error != 126)
			cmd->cmd_error = 127;
		return (1);
	}
	free(cmd->cmd);
	cmd->cmd = cmd_path;
	return (0);
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
			break;
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

/* Used to check the input and pass it to the parsing and cutting
 functions to get back either a linked list with all the command original
 just one command in a node */
void	ft_parse_input(char *in_put, t_mVars *vars_list)
{
	t_cmds	*cmd;
	t_cmds	*tmp;
	int		count;

	count = 0;
	count += ft_isnspace_indx(in_put);
	if (!in_put[count])
		return ;
	cmd = ft_text_analysis(&in_put[count], vars_list->ls_buffer);
	free(in_put);
	if (!cmd)
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
		tmp = tmp->next;
	}
	ft_cmd_analysis(cmd, vars_list);
	/* The rest of the function is for demonstration purposes
	  to make sure the lexer is working well*/
	// tmp = cmd;
	// int	cnt = -1;
	//
	// while (tmp)
	// {
	// 	count = 0;
	// 	printf("Command: %s\n", tmp->cmd);
	// 	while (tmp->args && tmp->args[count])
	// 	{
	// 		printf("Arg %d: %s\n", count, tmp->args[count]);
	// 		count ++;
	// 	}
	// 	if ((tmp->redirect & INPUT))
	// 		while (cmd->from_file[++cnt])
	// 			printf("From_file: %s\n", tmp->from_file[cnt]);
	// 	cnt = -1;
	// 	if ((tmp->redirect & HEREDOC))
	// 		while (cmd->hdocs_end[++cnt])
	// 			printf("Heredoc_end: %s\n", tmp->hdocs_end[cnt]);
	// 	cnt = -1;
	// 	if ((tmp->redirect & OUTPUT) || (tmp->redirect & APPEND))
	// 		while (cmd->to_file[++cnt])
	// 			printf("To_file: %s\n", tmp->to_file[cnt]);
	// 	tmp = tmp->next;
	// }
	// ft_execute_buildin(cmd, env_list); //placing this here causes no problems
}
