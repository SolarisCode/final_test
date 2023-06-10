/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:15:01 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 18:48:59 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	**ft_create_pipes(int proc)
{
	int	**pipes;
	int	*pip;
	int	count;

	pipes = (int **)ft_calloc(proc, sizeof(int *));
	if (!pipes)
		return (NULL);
	count = 0;
	while (count < proc)
	{
		pip = (int *)ft_calloc(2, sizeof(int));
		if (!pip)
			return (NULL);
		if (pipe(pip) < 0)
			perror("Pipe creation failed");
		pipes[count] = pip;
		count ++;
	}
	return (pipes);
}

void	ft_close_out_pipes(t_mVars *vars_list, int fd)
{
	int	count;

	count = -1;
	if (fd < 0)
	{
		while (++count < vars_list->pipe_count)
			close(vars_list->pipefd[count][1]);
		return ;
	}
	count = -1;
	while (++count < vars_list->pipe_count)
	{
		if (count == fd)
		{
			dup2(vars_list->pipefd[count][1], STDOUT_FILENO);
			close(vars_list->pipefd[count][1]);
			continue ;
		}
		close(vars_list->pipefd[count][1]);
	}
}

void	ft_close_in_pipes(t_mVars *vars_list, int fd)
{
	int	count;

	count = -1;
	if (fd < 0)
	{
		while (++count < vars_list->pipe_count)
			close(vars_list->pipefd[count][0]);
		return ;
	}
	count = -1;
	while (++count < vars_list->pipe_count)
	{
		if (count + 1 == fd)
		{
			dup2(vars_list->pipefd[count][0], STDIN_FILENO);
			close(vars_list->pipefd[count][0]);
			continue ;
		}
		close(vars_list->pipefd[count][0]);
	}
}

void	ft_close_all_pipes(t_mVars *vars_list)
{
	int	count;

	count = -1;
	while (++count < vars_list->pipe_count)
	{
		close(vars_list->pipefd[count][0]);
		close(vars_list->pipefd[count][1]);
	}
}

void	ft_free_pipes(t_mVars *vars_list)
{
	int	count;

	count = 0;
	while (count < vars_list->pipe_count)
	{
		free(vars_list->pipefd[count]);
		count ++;
	}
	free(vars_list->pipefd);
	vars_list->pipefd = NULL;
}
