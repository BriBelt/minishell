/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:07:01 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/25 16:06:41 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_type(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

t_quote	*initialize_t_quote(void)
{
	t_quote	*handle;

	handle = malloc(sizeof(t_quote));
	if (!handle)
		return (NULL);
	handle->normal = 1;
	handle->count = 0;
	handle->start = -1;
	handle->end = 0;
	handle->first = 0;
	handle->i = 0;
	return (handle);
}

void	count_quotes(char *rd, int *i, t_quote *h)
{
	if (quote_type(rd[*i]))
	{
		h->normal = 0;
		if (!h->first)
			h->first = quote_type(rd[*i]);
		if (quote_type(rd[*i]) == h->first)
			h->count++;
	}
}
