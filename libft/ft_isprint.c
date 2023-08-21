/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:30:50 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:21:39 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
/*int	main(void)
{
	printf ("%d\n", ft_isprint(' '));
	printf ("%d\n", ft_isprint('~'));
	printf ("%d\n", ft_isprint('4'));
	printf ("%d\n", ft_isprint('A'));
	printf ("%d\n", ft_isprint('z'));
	printf ("%d\n", ft_isprint(126));
	printf ("%d\n", ft_isprint(32));
	printf ("%d\n", ft_isprint(127));
	return (0);
}*/
