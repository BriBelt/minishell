/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:06:34 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:24:10 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	slen = ft_strlen(src);
	i = 0;
	if (!src && !dst)
		return (slen);
	if (!dstsize)
		return (slen);
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}
/*int	main(void)
{
	char	*src = "Src test";
	char	*dest = "Dst string";
	char	*dest1 = "Dst string";

	printf ("My strlcpy: %zu\n", ft_strlcpy(dest1, src, 5));
	printf ("My strlcpy: %s\n", dest1);
	printf ("Original strlcpy: %zu\n", strlcpy(dest, src, 5));
	printf ("Original strlcpy: %s\n", dest);
	return (0);
}*/
