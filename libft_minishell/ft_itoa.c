/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:25:00 by bbeltran          #+#    #+#             */
/*   Updated: 2023/07/28 17:05:32 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_findlen(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static size_t	ft_isneg(int n)
{
	size_t	result;

	result = 0;
	if (n < 0)
		result = 1;
	return (result);
}

char	*ft_itoa(int n)
{
	size_t	len;
	size_t	isneg;
	char	*str;

	len = ft_findlen(n);
	isneg = ft_isneg(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	if (n == 0)
		ft_strlcpy(str, "0", 2);
	str[len] = '\0';
	while (n != 0 && len-- && (n != -2147483647 -1))
	{
		if (n < 0)
			n = n * -1;
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	if (isneg == 1)
		str[0] = '-';
	if (n == -2147483647 -1)
		ft_strlcpy(str, "-2147483648", 12);
	return (str);
}
