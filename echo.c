/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:58:14 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/01 15:42:35 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_lexer *node, t_shell *mini)
{
	if (node->next)
	{
		if (node->next->type == VAR)
			node->next->data = expand_envar(node->next->data, mini);
		printf("%s\n", node->next->data);
	}
}

/*void	print_quotes(char *str)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(str))
		printf("i: %i, %s\n", i, quote_handle(str, &i));
}

char	*quote_handle(char *str, int *i)
{
	int		start;
	int		end;
	int		found;
	char	*new;

	start = 0;
	end = 0;
	found = 0;
	while (str[*i])
	{
		if (found_quote(str[*i]) && !found_quote(str[(*i) + 1]) && found == 0)
		{
			start = *i;
			found++;
		}
		(*i)++;
		end = *i;
		if (found > 0 && found_quote(str[end]) && str[end] == str[start])
			break;
	}
	new = ft_substr(str, start + 1, end - start + 1);
	return (new);
}*/
/*char	*quote_handle(char *str, int *i)
{
	int		start;
	int		end;
	int		found;
	char	*newstr;

	start = 0;
	end = 0;
	found = 0;
	while (str[*i])
	{
		if (found_quote(str[*i]) && found == 0)
		{
			found = found_quote(str[*i]);
			start = *i + 1;
			printf("found quote start->%i, %c\n", start, str[*i]);
		}
		(*i)++;
		if (found_quote(str[*i]) && str[*i] == str[start - 1])
		{
			end = *i;
			printf("found quote end->%i, %c\n", *i, str[*i]);
			break ;
		}
	}
	if (!found)
		return (str);
	newstr = ft_substr(str, start, end - start);
	return (newstr);
}*/
/*char	*quote_handle(char *str)
{
	int		i;
	int		start;
	int		end;
	int		found;
	char	*newstr;

	i = 0;
	start = 0;
	end = 0;
	found = 0;
	while (str[i])
	{
		if (found_quote(str[i]) && found == 0)
		{
			found = found_quote(str[i]);
			start = i + 1;
		}
		i++;
		if (found_quote(str[i]) && str[i] == str[start - 1])
		{
			end = i;
			break ;
		}
	}
	if (!found ||!end)
		return (str);
	newstr = ft_substr(str, start, end - start);
	return (newstr);
}*/

int	found_quote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}
/*
int	unclosed_quotes(char *str)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (str[i])
	{
		if (found_quote(str[i]))
		{
			if (found_quote(str[i]) == 1)
				single_q++;
			else if (found_quote(str[i]) == 2)
				double_q++;
		}
		i++;
	}
	if (single_q && single_q % 2 == 0)
		return (1);
	if (double_q && double_q % 2 == 0)
		return (2);
	if (!single_q && !double_q)
		return (3);
	if (single_q && single_q % 2 == 0 && double_q && double_q % 2 == 0)
		return (1);
	return (0);
}

char	quote_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (found_quote(str[i]))
			return (str[i]);
		i++;
	}
	return (0);
}

void	check_quotes(char *str)
{
	char	**quote_content;
	int i = 0;

	quote_content = NULL;
	if (!unclosed_quotes(str))
		perror("All quotes must be closed\n");
	quote_content = ft_split(str, quote_type(str));
	while (quote_content[i])
	{
		printf("%i--%s\n", i, quote_content[i]);
		i++;
	}
//	return (quote_content);
}*/

/*char	*space_separated_rd(char *str)
{
	char	*new_rd;
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	while (str[i])
	{
		if (
		i++;
	}
	return (new_rd);
}*/
