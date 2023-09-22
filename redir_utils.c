/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:52:39 by jaimmart          #+#    #+#             */
/*   Updated: 2023/09/22 18:57:19 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_redirects(char *data)
{
	if (!ft_strcmp("<", data) || !ft_strcmp(">", data))
		return (1);
	if (!ft_strcmp("<<", data) || !ft_strcmp(">>", data))
		return (1);
	return (0);
}

void	search_redirect(char *data, int *i, int *redirect)
{
	while (data[++(*i)])
	{
		if (data[*i] == '<' || data[*i] == '>')
		{
			*redirect = *i;
			break ;
		}
	}
}

int	first_redirect(char *data)
{
	int	i;
	int	quote;
	int	redirect;

	i = -1;
	quote = -2;
	redirect = 0;
	search_redirect(data, &i, &redirect);
	i = -1;
	while (data[++i])
	{
		if (quote_type(data[i]))
		{
			quote = i;
			break ;
		}
	}
	if (redirect < quote || quote == -2)
		return (quote);
	return (-1);
}
