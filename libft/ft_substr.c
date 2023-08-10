/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:07:47 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:29:42 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sbstr;
	size_t	slen;

	slen = ft_strlen(s);
	if (start >= slen)
		start = slen;
	if (len > slen)
		len = slen - start;
	if (s[start] == 0)
		len = 0;
	if (start + len > slen)
		len = ft_strlen(s + start);
	sbstr = malloc((len + 1) * sizeof(char));
	if (!sbstr)
		return (0);
	ft_strlcpy(sbstr, s + start, len + 1);
	return (sbstr);
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*substr;
	char	s[5] = "hola";//"reventar";

	substr = ft_substr(s, 2, 3);
	printf ("%s", substr);
	return (0);
}*/
