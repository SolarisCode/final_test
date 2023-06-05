/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 00:03:01 by melkholy          #+#    #+#             */
/*   Updated: 2023/05/22 01:58:34 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include "libft.h"
# include "builtins.h"
# include "execution.h"
# include "parsing.h"
# include "signals.h"
# include "lexer.h"
# include "input_analysis.h"
# include "structs.h"

// # include "./builtins.h"
# define PROMPT "\033[35mminihell\033[36m$\033[0m "
# define DIRECTION_ERR "minishell: syntax error near unexpected token"
# define INPUT 1
# define HEREDOC 2
# define OUTPUT 4
# define APPEND 8
# define UNSET_BEFORE 3
# define UNSET_AFTER 4
# define SET 5

/* main.c */
int		ft_read_prompt(char **envp);
void	ft_exit_minihell(char *str, t_cmds *cmd, t_mVars *list_pointers);
void	ft_free_envlist(t_env **env_list);
int		ft_closing_qoutes(char *in_put);

#endif
