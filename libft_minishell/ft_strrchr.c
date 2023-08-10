/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:08:20 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:26:54 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i--;
	}
	return (0);
}
/*#include <stdio.h>
#include <string.h>
 * int	main(void)
{
	char	s[] = "Here's an example";
	int	c = 'l';

//	printf ("%s\n", ft_strrchr("This is a string", 't'));
//	printf ("%s\n", ft_strrchr("Just testing", '0'));
//	printf ("%s\n", ft_strrchr(s, c));
	printf ("%s\n", strrchr(s, c));
	printf ("%s\n", ft_strrchr(s, c));
	return (0);
}*/
