/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:41:21 by estruckm          #+#    #+#             */
/*   Updated: 2023/06/09 21:06:55 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_oldpath(t_mVars *list_pointer)
{
	t_env	*old_path;

	getcwd(list_pointer->cwd, 1000);
	old_path = ft_get_env_node(list_pointer->ls_env, "OLDPWD");
	if (list_pointer->check_oldpwd_path == UNSET_BEFORE)
	{
		ft_create_add_all(list_pointer, "OLDPWD");
		list_pointer->check_oldpwd_path = SET;
	}
	old_path = ft_get_env_node(list_pointer->ls_env, "OLDPWD");
	if (old_path == NULL)
		list_pointer->check_oldpwd_path = UNSET_AFTER;
	if (list_pointer->check_oldpwd_path != UNSET_AFTER)
	{
		ft_update_all(list_pointer, "OLDPWD");
	}
}

void	ft_check_pwd(t_mVars *list_pointer)
{
	t_env	*pwd_path;

	getcwd(list_pointer->cwd, 1000);
	pwd_path = ft_get_env_node(list_pointer->ls_env, "PWD");
	if (list_pointer->check_pwd_path == UNSET_BEFORE)
	{
		ft_create_add_all(list_pointer, "PWD");
		list_pointer->check_pwd_path = SET;
	}
	pwd_path = ft_get_env_node(list_pointer->ls_env, "PWD");
	if (pwd_path == NULL)
		list_pointer->check_pwd_path = UNSET_AFTER;
	if (list_pointer->check_pwd_path != UNSET_AFTER)
	{
		ft_update_all(list_pointer, "PWD");
	}
}

void	ft_tilde_slash(t_cmds *cmd, t_mVars *list_pointer)
{
	char	*path;
	char	*new_path;

	printf("%s\n", list_pointer->home);
	if (list_pointer->home == NULL)
	{
		ft_putstr_fd("HOME_path is unsetted", 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	ft_check_oldpath(list_pointer);
	path = ft_substr(cmd->args[0], 1, ft_strlen(cmd->args[0]));
	new_path = ft_strjoin(list_pointer->home, path);
	free(path);
	ft_cd_pathes(list_pointer, new_path);
	free(new_path);
}

void	ft_cd(t_cmds *cmd, t_mVars *list_pointer)
{
	if (cmd->args == NULL)
		ft_cd_tilde_empty(list_pointer);
	else if (ft_strcmp(cmd->args[0], "-") == 0)
		ft_cd_minus(list_pointer);
	else if (ft_strcmp(cmd->args[0], "..") == 0)
		ft_cd_dots(list_pointer);
	else if (ft_strncmp(cmd->args[0], "~/", 2) == 0)
		ft_tilde_slash(cmd, list_pointer);
	else if (ft_strcmp(cmd->args[0], "~") == 0)
		ft_cd_tilde_empty(list_pointer);
	else if (ft_strcmp(cmd->args[0], "/") == 0)
		ft_cd_slash(list_pointer);
	else
		ft_cd_pathes(list_pointer, cmd->args[0]);
}
