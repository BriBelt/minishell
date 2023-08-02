/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:19:19 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/02 18:03:57 by bbeltran         ###   ########.fr       */
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
			(*i)++;
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
		if (normal && quote_type(rd[*i + 1]))
		{
			(*i)++;
			end = *i;
			break ;
		}
		(*i)++;
	}
	data = ft_substr(rd, start, end - start);
	printf("new = %s, start  = %i, end= %i, i = %zu\n", data, start, end, *i);
//	printf("new = %s\n", data);
//	return (data);
}
/*char	*handle_quotes(char *rd, size_t *i)
{
	int		open;
	int		closed;
	int		normal;
	int		first;
	int		start;
	int		end;
	char	*data;

	open = 0;
	start = 0;
	end = 0;
	closed = 0;
	normal = 1;
	first = 0;
	printf("i before anything: %zu\n", *i);
	while (rd[*i])
	{
		if (quote_type(rd[*i]))
		{
			normal = 0;
			if (!first)
			{
				first = quote_type(rd[*i]);
				open++;
				(*i)++;
				start = *i;
				printf("found first quote at %zu\n", *i);
				printf("first quote value: %i\n", first); 
			}
			else if (first && quote_type(rd[*i]) == first)
			{
				closed++;
				end = *i;
				printf("found end quote at %i\n", end);
			}
		}
		if (normal && !start)
		{
			printf("Normal mode, no quotes\n");
			start = *i;
		}
		while (quote_type(rd[*i]) != first && rd[*i])
		{
			printf("iterating--%c--\n", rd[*i]);
			(*i)++;
		}
		if (closed && open)
			break;
		else
			end = *i;
		(*i)++;
	}
	data = ft_substr(rd, start, end - start - 1);
	printf("original: %s\n", rd + start);
	return (data);
}*/
int	main(void)
{
//	char	*str = "\"\'\'first\'\'\"\"\'second\"third\'four\'\'\'";
	char	*str = "\"no quotes\" \'\"double\"\'nothing \" \"";
	size_t	i = 0;
	
	while (i < ft_strlen(str))
		handle_quotes(str, &i);
//		printf("new= %s\n", handle_quotes(str, &i)); 
}
