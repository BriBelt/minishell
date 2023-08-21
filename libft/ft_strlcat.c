/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:46:08 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:25:42 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;
	size_t	copylen;

	copylen = 0;
	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (siz <= dlen)
		return (siz + slen);
	else if (siz - dlen - 1 > slen)
		copylen = slen;
	else
		copylen = siz - dlen - 1;
	while (i < copylen)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	if (!(siz == 0) && !(dlen > siz))
		dst[dlen + i] = '\0';
	return (dlen + slen);
}
/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int	main(void)
{
	char	*src = "a test ";
	char 	*dst = "This is ";	

	printf("Original function: %lu\n", strlcat(dst, src, 7);
	printf ("My function: %zu", ft_strlcat(dst, src, 7));
	return (0);
}*/
