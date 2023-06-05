/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 02:00:07 by melkholy          #+#    #+#             */
/*   Updated: 2023/05/22 02:01:20 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/* lexer.c */
char	*ft_expansion(char *str, t_env *env_list);
char	*ft_getenv_var(char *in_put, int *index, t_env *env_list);
char	*ft_inside_qoutes(char *str, char *in_put,
			int *index, t_env *env_list);
char	*ft_tokenize(char *str, char *in_put, int *index, t_env *env_list);
char	**ft_lexer(char *in_put, t_env *env_list);

#endif
