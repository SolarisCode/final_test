/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:12:04 by estruckm          #+#    #+#             */
/*   Updated: 2023/06/09 21:12:05 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_msg(char *string)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	ft_putstr_fd("\n", 2);
}

void	check_export(char *string, t_env *list_pointer)
{
	int	check;

	check = ft_check_validity(string);
	if (check == 2 || check == 3 || check == 0)
	{
		update_or_create(list_pointer, string);
	}
}

void	check_env(char *string, t_env *list_pointer)
{
	int	check;

	check = ft_check_validity(string);
	if (check == 2 || check == 3)
	{
		update_or_create(list_pointer, string);
	}
}

void	check_buffer(char *string, t_env *list_pointer)
{
	int	check;

	check = ft_check_validity(string);
	if (check == 2 || check == 3 || check == 0)
	{
		update_or_create(list_pointer, string);
	}
}

void	ft_export(t_cmds *cmd, t_mVars *list_pointer)
{
	int	i;

	i = 0;
	if (!cmd->args)
	{
		ft_print_list_export(list_pointer->ls_export, ft_print_char);
		return ;
	}
	while (cmd->args[i])
	{
		if (ft_check_validity(cmd->args[i]) == 1)
			error_msg(cmd->args[i]);
		else
		{
			check_export(cmd->args[i], list_pointer->ls_export);
			check_env(cmd->args[i], list_pointer->ls_env);
			check_buffer(cmd->args[i], list_pointer->ls_buffer);
		}
		i++;
	}
	ft_sort_linked_list(&list_pointer->ls_export);
}
