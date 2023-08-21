/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:13:15 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:30:27 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkstart(char const *s1, char const *set)
{
	size_t	start;
	size_t	j;

	start = 0;
	while (s1[start])
	{
		j = 0;
		while (set[j] != '\0' && set[j] != s1[start])
			j++;
		if (j == ft_strlen(set))
			break ;
		start++;
	}
	return (start);
}

static int	ft_checkback(char const *s1, char const *set, size_t start)
{
	size_t	j;
	size_t	end;

	j = 0;
	start = ft_checkstart(s1, set);
	end = ft_strlen(s1);
	while (end > start)
	{
		j = 0;
		while (set[j] != '\0' && set[j] != s1[end - 1])
			j++;
		if (j == ft_strlen(set))
			break ;
		end--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;
	char	*sptr;

	start = ft_checkstart(s1, set);
	end = ft_checkback(s1, set, start);
	sptr = malloc((end - start + 1) * sizeof(char));
	if (!sptr)
		return (0);
	ft_strlcpy(sptr, &s1[start], end - start + 1);
	return (sptr);
}
/*#include <stdio.h>
int	main(void)
{
	char	*s1 = ".. this is a test...";
	char	*set = ". t";	

	printf("%s", s1);
	printf("\n%s", ft_strtrim(s1, set));
	return (0);
}*/
