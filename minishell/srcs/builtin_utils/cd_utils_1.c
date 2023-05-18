#include "minishell.h"

void ft_cd_minus(t_mVars *list_pointer)
{
	t_env *old_path;
	char *save_oldpwd;

	old_path = ft_get_env_node(list_pointer->ls_env, "OLDPWD");
	save_oldpwd = ft_strdup(old_path->value);
	ft_check_oldpath(list_pointer);
	chdir(save_oldpwd);
	ft_putstr_fd(save_oldpwd, 1);
	ft_putstr_fd("\n", 1);
	free(save_oldpwd);
	ft_check_pwd(list_pointer);
}

void ft_cd_dots(t_mVars *list_pointer)
{
	char *new_path;

	ft_check_oldpath(list_pointer);
	new_path = ft_get_new_path(list_pointer->cwd);
	chdir(new_path);
	free(new_path);
	ft_check_pwd(list_pointer);
}

void ft_cd_tilde_empty(t_mVars *list_pointer)
{
	ft_check_oldpath(list_pointer);
	chdir(list_pointer->home);
	ft_check_pwd(list_pointer);
}

void ft_cd_slash(t_mVars *list_pointer)
{
	ft_check_oldpath(list_pointer);
	chdir("/");
	ft_check_pwd(list_pointer);
}

void ft_cd_pathes(t_mVars *list_pointer, char *path)
{
	DIR *directory;

	directory = opendir(path);
	if (directory != NULL)
	{
		ft_check_oldpath(list_pointer);
		chdir(path);
		ft_check_pwd(list_pointer);
		closedir(directory);
	}
	else
	{
		ft_putstr_fd("minihell: cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
}
