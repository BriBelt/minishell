/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:28:42 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:23:07 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!src && !dst && n > 0)
		return (0);
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return ((char *)dst);
}
/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	src[] = "Copy.from.here";
	char	dst[20] = "Destination"; 

	printf ("Str original: %s\n", dst);  
	printf ("%s\n", ft_memcpy(dst, src, 0));  
	printf ("%s\n", memcpy(dst, src, 0));   
	ft_memcpy(&dst[3], &src[2], 2*sizeof(char));
	printf ("My memcpy: src: %s, dest: %s", src, dst);
	memcpy(&dst[3], &src[2], 2*sizeof(char));
	printf ("\nOriginal memcpy: src: %s, dest: %s", src, dst);
	return (0);
	}*/
