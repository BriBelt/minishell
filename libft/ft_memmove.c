/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:44:15 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:23:24 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;

	i = 0;
	d = dst;
	if (!src && !dst)
		return (0);
	if (dst >= src)
		while (len--)
			d[len] = ((char *)src)[len];
	else
	{
		while (len > i)
		{
			d[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dst);
}	
/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	src1[] = "string";
	char	dst1[] ="That was a test";

	printf ("Original: %s", memmove(dst1, src1, 5));
	printf ("\nMy own f: %s", ft_memmove(dst1, src1, 5));
	return (0);
}*/
