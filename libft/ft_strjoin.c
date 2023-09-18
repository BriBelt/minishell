/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:54:43 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/18 15:06:50 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	char	*ptr;
	size_t	newssize;
	size_t	lens1;
	size_t	lens2;

	if (s1)
		lens1 = ft_strlen(s1);
	else
		lens1 = 0;
	if (s2)
		lens2 = ft_strlen(s2);
	else
		lens2 = 0;
	newssize = lens1 + lens2;
	newstr = malloc((newssize + 1) * sizeof(char));
	ptr = newstr;
	if (!newstr)
		return (0);
	while (*s1)
		*newstr++ = *s1++;
	while (*s2)
		*newstr++ = *s2++;
	*newstr = '\0';
	return (ptr);
}
/*#include <stdio.h>
int	main(void)
{
	char	*s1 = "This is ";
	char	*s2 = "";//"a test";
	
	printf ("%s", ft_strjoin(s1, s2));
	return (0);
}*/
