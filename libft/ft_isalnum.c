/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:23:51 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:20:38 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((ft_isalpha(c)) || (ft_isdigit(c)))
		return (1);
	else
		return (0);
}
/*int	main(void)
{
	printf ("%d\n", ft_isalnum('W'));
	printf ("%d\n", ft_isalnum('+'));
	printf ("%d\n", ft_isalnum('w'));
	printf ("%d\n", ft_isalnum(5));
	printf ("%d\n", ft_isalnum('6'));
	return (0);
}*/
