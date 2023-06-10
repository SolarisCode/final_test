/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:59:08 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 18:39:34 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/* heredocs.c */
void	ft_child_heredoc(t_cmds *cmds, t_mVars *vars_list);
char	*ft_expand_hdoc(char *hdocs_str, t_env *env_list);
int		ft_read_hdocs(char *hdocs_end, t_env *env_list);
int		ft_here_doc(char **hdocs_end, t_env *env_list);

/* error_handling.c */
void	ft_error_handler(t_cmds *cmd);
void	ft_file_errors(t_cmds *cmd);

/* pipeing.c */
void	ft_close_out_pipes(t_mVars *vars_list, int fd);
void	ft_close_in_pipes(t_mVars *vars_list, int fd);
void	ft_close_all_pipes(t_mVars *vars_list);
void	ft_free_pipes(t_mVars *vars_list);
int		**ft_create_pipes(int proc);

/* execute_redirection.c */
int		ft_execute_in_redirect(t_cmds *cmd, t_env *env_list);
void	ft_outfile_fd(char *to_file, int redirect);
int		ft_execute_out_redirect(t_cmds *cmd);
int		ft_infile_fd(char *file);

/* execute_utils.c */
int		ft_strcmp(char *s1, char *s2);
void	ft_exit_status(t_cmds *cmd);
int		ft_cmd_size(t_cmds *cmd);
int		ft_is_builtin(char *cmd);
int		*ft_create_pid(int proc);

/* cmds_processing.c */
void	ft_execute_cmd(t_cmds *cmd, char **env_array, t_env *env_list);
void	ft_child_cmd(t_mVars *vars_list, t_cmds *cmd, int index);
void	ft_cmds_processing(t_cmds *cmds, t_mVars *vars_list);
void	ft_many_cmd_exe(t_cmds *cmds, t_mVars *vars_list);

/* execution_analysis.c */
void	ft_cmd_analysis(t_cmds *cmd, t_mVars *vars_list);
char	**ft_create_env_array(t_env	*env_list);

#endif
