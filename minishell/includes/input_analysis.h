#ifndef INPUT_ANALYSIS_H
# define INPUT_ANALYSIS_H

/* input_analysis.c */
void	ft_create_fullcmd(t_cmds *cmd);
void	ft_free_cmdlist(t_cmds **cmds);
char	*ft_find_envpath(t_env *env_list);
int		ft_add_path(t_cmds *cmd, t_env *env_list);
void	ft_parse_input(char *in_put, t_mVars *vars_list);

#endif
