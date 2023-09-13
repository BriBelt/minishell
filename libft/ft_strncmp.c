/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:27:29 by bbeltran          #+#    #+#             */
/*   Updated: 2023/06/13 15:30:42 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && (i < n))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}	
/*int	main(void)
{
	size_t	n;

	n = 4;
	printf ("Same string: %d\n", ft_strncmp("Hello", "Hello", n));
	printf ("Similar string: %d\n", ft_strncmp("Hello", "Help", n));
	printf ("Nothing and string: %d\n", ft_strncmp("", "Hello", n));
	printf ("String and nothing: %d\n", ft_strncmp("Hello", "", n));
	printf ("Nothing and nothing: %d\n", ft_strncmp("", "", n));
	return (0);
}*/
