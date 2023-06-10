/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 02:05:03 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 19:24:09 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* many_redirection.c */
char	**ft_many_redirect(char **old_files, char *new_file, int len);
char	*ft_add_io_file(char *old_file, char *new_file, int len);

/* parsing_redirection.c */
int		ft_add_redirection(char **table, t_cmds *cmd, int index, int len);
void	ft_arrange_table(char **table, int index, int len);
int		ft_check_redirect(t_cmds *cmd, char **cmd_table);
void	ft_apply_priority(t_cmds *cmd, int redirect);
int		ft_get_redirection(char *in_put);

/* parser.c */
t_cmds	*ft_parser(char **cmd_table);
t_cmds	*ft_many_cmd(t_cmds *cmd, char **full_cmds, t_env *env_list);
char	*ft_cut_input(char *in_put, int *index);
char	**ft_check_pipe_char(char *in_put);
t_cmds	*ft_text_analysis(char *in_put, t_env *env_list);

/* parsing_utils.c */
int		ft_isnspace_indx(char *in_put);
void	ft_free_dstr(char **str);
char	**ft_check_args(char *arg, char **cmd_args);
char	**ft_double_realloc(char **str, int old_size, int new_size);
char	*ft_join_free_both(char *s1, char *s2);

#endif
