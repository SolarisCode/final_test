/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:06:58 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 18:40:57 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>

char	**ft_create_env_array(t_env	*env_list)
{
	t_env	*tmp_list;
	char	*str;
	char	**env_array;
	int		index;

	index = -1;
	tmp_list = env_list;
	env_array = (char **)ft_calloc(1, sizeof(char *));
	while (tmp_list)
	{
		str = NULL;
		str = ft_join_free_both(ft_strdup(tmp_list->var), ft_strdup("="));
		str = ft_join_free_both(str, ft_strdup(tmp_list->value));
		env_array[++index] = ft_strdup(str);
		env_array = ft_double_realloc(env_array, index + 1, index + 2);
		tmp_list = tmp_list->next;
		free(str);
	}
	return (env_array);
}

void	ft_cmd_analysis(t_cmds *cmd, t_mVars *vars_list)
{
	int		pid;

	vars_list->env_array = ft_create_env_array(vars_list->ls_buffer);
	if (cmd->next)
	{
		ft_many_cmd_exe(cmd, vars_list);
		ft_free_pipes(vars_list);
		free(vars_list->pids);
		vars_list->pids = 0;
	}
	else if (!ft_is_builtin(cmd->cmd))
	{
		ft_error_handler(cmd);
		pid = fork();
		if (pid == 0)
			ft_execute_cmd(cmd, vars_list->env_array, vars_list->ls_buffer);
		waitpid(pid, NULL, 0);
	}
	else
		ft_execute_buildins(cmd, vars_list);
	if (!access("minhell_tmp.txt", F_OK))
		unlink("minhell_tmp.txt");
	ft_free_dstr(vars_list->env_array);
	ft_exit_status(cmd);
	ft_free_cmdlist(&cmd);
}
