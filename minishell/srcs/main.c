/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:06:18 by melkholy          #+#    #+#             */
/*   Updated: 2023/05/22 02:40:18 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	ft_closing_qoutes(char *in_put)
{
	char	divid;
	int		count;
	int		closing;

	count = -1;
	closing = 0;
	while (in_put[++count])
	{
		if (in_put[count] == '"' || in_put[count] == '\'')
		{
			if (!closing)
			{
				closing = 1;
				divid = in_put[count];
			}
			else if (in_put[count] == divid)
				closing = 0;
		}
	}
	if (closing)
	{
		free(in_put);
		return (printf("minishell: unclosed qoute detected.\n"), 1);
	}
	return (0);
}

void	ft_free_envlist(t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		*env_list = (*env_list)->next;
		if (tmp->var)
			free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = *env_list;
	}
}

void	ft_exit_minihell(char *str, t_cmds *cmd, t_mVars *list_pointers)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_term_attr.save_attr);
	if (!str)
	{
		rl_on_new_line();
		// check this on Mac first before remove it compeletly ;
		// rl_redisplay();
	}
	if (str)
		free(str);
	if (cmd)
		ft_free_cmdlist(&cmd);
	ft_free_envlist(&list_pointers->ls_env);
	ft_free_envlist(&list_pointers->ls_export);
	ft_free_envlist(&list_pointers->ls_buffer);
	free(list_pointers->home);
	free(list_pointers);
	write(1, "exit\n", 5);
	clear_history();
	exit(0);
}

/* Used to display the prompt and read the input from the user */
int	ft_read_prompt(char **envp)
{
	char	*str;
	t_mVars	*vars_list;

	vars_list = ft_create_ls_pointers(envp);
	while (true)
	{
		str = readline(PROMPT);
		if (!str || !ft_strcmp(str, "exit"))
			ft_exit_minihell(str, NULL, vars_list);
		add_history(str);
		if (ft_closing_qoutes(str))
			continue ;
		ft_parse_input(ft_strdup(str), vars_list);
		free(str);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	(void) argc;
	signal(SIGINT, ft_quit_ignore);
	signal(SIGQUIT, SIG_IGN);
	if (ft_set_terminal())
		exit(1);
	ft_read_prompt(envp);
}
