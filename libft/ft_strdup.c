/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:13:19 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:29:17 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	slen;
	char	*str;

	slen = ft_strlen(s1) + 1;
	str = (char *) malloc(slen * sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, slen);
	return (str);
}
/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char	str[20] = "Strdup test";
	const char	str1[20] = "My strdup test";
	const char	*dstr = strdup(str);
	const char	*mydstr = ft_strdup(str1);

	printf ("%s\n", dstr);
	printf ("%s", mydstr);
	return (0);
}*/
