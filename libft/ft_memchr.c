/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:37:29 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:28:04 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (&((unsigned char *)s)[i]);
		i++;
	}
	return (0);
}
/*int	main(void)
{
	char str[15] = "This is a test";
	//ft_memchr(str, 'i', 5);
	printf ("My memchr: %s\n", ft_memchr(str, 0, 5));
	printf ("Org memchr: %s\n", memchr(str, 0, 5));
	return (0);
}*/
