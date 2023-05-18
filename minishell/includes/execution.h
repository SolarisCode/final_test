#ifndef EXECUTION_H
# define EXECUTION_H

/* execution.c */
int		ft_cmd_size(t_cmds *cmd);
int		ft_infile_fd(t_cmds *cmd, char *file);
char	**ft_create_env_array(t_env	*env_list);
void	ft_outfile_fd(char *to_file, int redirect);
char	*ft_expand_hdoc(char *hdocs_str, t_env *env_list);
int		ft_read_hdocs(char *hdocs_end, t_env *env_list);
int		ft_here_doc(char **hdocs_end, t_env *env_list);
int		ft_execute_redirection(t_cmds *cmd, t_env *env_list);
void	ft_execute_cmd(t_cmds *cmd, char **env_array, t_env *env_list);
void	ft_cmd_analysis(t_cmds *cmd, t_mVars *vars_list);
int		ft_is_builtin(char* cmd);
int		ft_strcmp(char *s1, char *s2);
char	*ft_realloc(char *str, int old_size, int new_size);

#endif
