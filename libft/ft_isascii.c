/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:24:49 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:21:10 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*int	main(void)
{
	printf ("%d\n", ft_isascii('\n'));
	printf ("%d\n", ft_isascii('A'));
	printf ("%d\n", ft_isascii('z'));
	printf ("%d\n", ft_isascii('0'));
	printf ("%d\n", ft_isascii('9'));
	printf ("%d\n", ft_isascii(' '));
	printf ("%d\n", ft_isascii('!'));
	printf ("%d\n", ft_isascii(19));
	printf ("%d\n", ft_isascii(128));
	return (0);
}*/
