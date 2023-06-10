/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_analysis.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 02:04:33 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 16:57:45 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_ANALYSIS_H
# define INPUT_ANALYSIS_H

# include "minishell.h"

/* input_analysis.c */
char	*ft_realloc(char *str, int old_size, int new_size);
void	ft_parse_input(char *in_put, t_mVars *vars_list);
char	*ft_find_envpath(t_env *env_list);
void	ft_free_cmdlist(t_cmds **cmds);

/* cmmand_path.c */
void	ft_validate_path(t_cmds *cmd, t_mVars *vars_list);
char	*ft_validate_cmd(t_cmds *cmd, char **env_path);
int		ft_mark_path(t_cmds *cmd, t_mVars *vars_list);
int		ft_add_path(t_cmds *cmd, t_env *env_list);
void	ft_create_fullcmd(t_cmds *cmd);

/* assigning_vars.c */
void	ft_check_assigning(t_cmds *cmd, t_mVars *vars_list);
int		ft_check_in_export(char *str, t_mVars *vars_list);
char	**ft_arrange_args(char **args);

#endif
