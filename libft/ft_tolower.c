/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:12:41 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:26:07 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
/*int	main(void)
{
	printf ("%c\n", ft_tolower('a'));
	printf ("%c\n", ft_tolower('+'));
	printf ("%c", ft_tolower('A'));
	return (0);
}*/
