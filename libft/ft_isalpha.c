/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:17:23 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:19:17 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/*int	main(void)
{
	printf("%d", ft_isalpha('C'));
	printf("\n%d", ft_isalpha('c'));
	printf("\n%d", ft_isalpha(5));
	printf("\n%d", ft_isalpha('0'));
	return (0);
}*/
