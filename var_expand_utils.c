/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:50:33 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/22 18:07:15 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	symbol_count(char *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (data[++i])
	{
		if (data[i] == '$')
			count++;
	}
	return (count);
}

char	*more_than_one_expand(char *data, t_shell *mini)
{
	char	*quoted_str;
	char	*str_expand;
	char	*expanded;
	char	*new;

	quoted_str = ft_strdup(ft_strchr(data, '\''));
	str_expand = ft_substr(data, 0, ft_strlen(data) - ft_strlen(quoted_str));
	expanded = found_symbol(str_expand, mini);
	new = ft_strjoin(expanded, quoted_str);
	(free(expanded), free(str_expand), free(quoted_str));
	return (new);
}
