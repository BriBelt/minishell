/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:47:55 by bbeltran          #+#    #+#             */
/*   Updated: 2023/07/27 16:13:39 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freearray(char	**arr)
{
	int	str_index;

	str_index = 0;
	while (arr[str_index])
	{
		free(arr[str_index]);
		str_index++;
	}
	free(arr);
	return (0);
}

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	wordcount;
	int	len;
	int	endword;

	i = 0;
	wordcount = 0;
	endword = 0;
	len = 0;
	while (s[len] && s[len] != '\0')
		len++;
	if (!s)
		return (0);
	while (i < len)
	{
		while ((i < len) && s[i] == c)
			i++;
		endword = i;
		while ((i < len) && s[i] != c)
			i++;
		if (i > endword)
			wordcount++;
	}
	return (wordcount);
}

static char	*ft_placestr(char const *s, char c, int *i)
{
	int		startword;
	int		endword;
	char	*newstr;

	endword = 0;
	startword = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	startword = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	endword = *i;
	newstr = ft_substr(s, startword, endword - startword);
	if (!newstr)
		return (0);
	return (newstr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		wordcount;
	int		str_index;
	int		i;
	int		len;

	len = ft_strlen(s);
	i = 0;
	str_index = 0;
	wordcount = ft_word_count(s, c);
	arr = ft_calloc(wordcount + 1, sizeof(char *));
	if (!arr || !s)
		return (0);
	while (str_index < wordcount && i < len)
	{
		arr[str_index] = ft_placestr(s, c, &i);
		if (!arr[str_index])
		{
			ft_freearray(arr);
			return (0);
		}
		str_index++;
	}
	return (arr);
}
