/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:18:01 by jaimmart          #+#    #+#             */
/*   Updated: 2023/08/02 15:56:43 by jaimmart         ###   ########.fr       */
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

void	handle_quotes(char *rd, size_t	*i)
{
	int		single;
	int		q_double;
	int		normal;
	int		start;
	int		first;
	int		x;
	int		end;
	char	*data;

	normal = 1;
	single = 0;
	q_double = 0;
	start = 0;
	end = 0;
	first = 0;
	x = 0;
	while (rd[*i])
	{
		if (quote_type(rd[*i]))
		{
//			printf("--quote found: %c--\n", rd[*i]);
			normal = 0;
			if (quote_type(rd[*i]) == 1)
				single++;
			else if (quote_type(rd[*i]) == 2)
				q_double++;
			if (single && !first)
				first = 1;
			else if (q_double && !first)
				first = 2;
		}
		if ((single == 2 && first == 1) || (q_double == 2 && first == 2))
		{
			end = *i;
			break ;
		}
		if (normal && !x)
		{
			x = 1;
			start = *i;
		}
		else if (((single == 1 && first == 1) || (q_double == 1 && first == 2)) && !x)
		{
			x = 1;
			start = (*i) + 1;
		}
		(*i)++;
	}
	data = ft_substr(rd, start, end - start);
	printf("new = %s, start  = %i, end= %i, i = %zu\n", data, start, end, *i);
//	printf("new = %s\n", data);
//	return (data);
}

int	main(void)
{
	char	*str = "\"\'first\'\"\"second\"third\'\'";
	size_t	i = 0;
	
	while (i < ft_strlen(str))
		handle_quotes(str, &i);
//		printf("new= %s\n", handle_quotes(str, &i)); 
}