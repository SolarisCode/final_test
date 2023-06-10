/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   many_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:18:35 by melkholy          #+#    #+#             */
/*   Updated: 2023/06/10 19:25:58 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_add_io_file(char *old_file, char *new_file, int len)
{
	if (old_file)
		free(old_file);
	return (ft_substr(new_file, len, ft_strlen(new_file)));
}

char	**ft_many_redirect(char **old_files, char *new_file, int len)
{
	char	**files;
	int		size;

	size = 0;
	if (!old_files)
	{
		files = (char **)ft_calloc(2, sizeof(char *));
		if (!files)
			return (NULL);
		files[0] = ft_substr(new_file, len, ft_strlen(new_file));
		return (files);
	}
	while (old_files[size])
		size ++;
	files = ft_double_realloc(old_files, size, size + 2);
	files[size] = ft_substr(new_file, len, ft_strlen(new_file));
	return (files);
}
