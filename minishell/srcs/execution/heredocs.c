/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:03:32 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 17:10:28 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_expand_hdoc(char *hdocs_str, t_env *env_list)
{
	char	*str;
	int		count;

	count = 0;
	str = NULL;
	while (hdocs_str[count])
	{
		if (hdocs_str[count] == '$')
			str = ft_join_free_both(str,
					ft_getenv_var(hdocs_str, &count, env_list));
		else
			str = ft_join_free_both(str, ft_substr(&hdocs_str[count], 0, 1));
		count ++;
	}
	free(hdocs_str);
	return (str);
}

int	ft_read_hdocs(char *hdocs_end, t_env *env_list)
{
	char	*str;
	char	*delimiter;
	int		fd;

	delimiter = ft_strjoin(hdocs_end, "\n");
	fd = open("minhell_tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0666);
	write(1, "heredoc> ", 9);
	str = get_next_line(0);
	while (ft_strcmp(str, delimiter))
	{
		if (ft_strchr(str, '$'))
			str = ft_expand_hdoc(str, env_list);
		write(fd, str, ft_strlen(str));
		free(str);
		write(1, "heredoc> ", 9);
		str = get_next_line(0);
		if (!str)
			break ;
	}
	free(delimiter);
	free(str);
	return (fd);
}

int	ft_here_doc(char **hdocs_end, t_env *env_list)
{
	int		fd;

	if (!access("minhell_tmp.txt", F_OK))
		unlink("minhell_tmp.txt");
	fd = ft_read_hdocs(hdocs_end[0], env_list);
	close(fd);
	if (hdocs_end[1])
		return (-1);
	fd = open("minhell_tmp.txt", O_RDONLY);
	return (fd);
}

void	ft_child_heredoc(t_cmds *cmds, t_mVars *vars_list)
{
	t_cmds	*tmp;
	int		count;

	count = 0;
	tmp = cmds;
	while (tmp)
	{
		if ((tmp->redirect & HEREDOC) == HEREDOC)
		{
			vars_list->pids[count] = fork();
			if (vars_list->pids[count] < 0)
				return ((void)printf("minihell: fork() failed\n"));
			if (vars_list->pids[count] == 0)
				ft_child_cmd(vars_list, tmp, count);
			waitpid(vars_list->pids[count], NULL, 0);
		}
		count ++;
		tmp = tmp->next;
	}
}
