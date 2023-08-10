/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:46:38 by bbeltran          #+#    #+#             */
/*   Updated: 2023/02/17 10:29:41 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sig;
	int	res;

	i = 0;
	res = 0;
	sig = 1;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sig = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while ((str[i] != '\0') && (str[i] >= '0') && (str[i] <= '9'))
	{		
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sig * res);
}	
/*#include <stdio.h>
#include <stdlib.h>
int	main(void)
{
	char str[] = "012345";
	char str1[] = "+--2345";
	char str2[] = "9 01";
	char str3[] = "+29";
	char str4[] = "";
	//char *n = "\t\v\f\r\n \f-06050";
  	//int i1 = atoi(n);
  	//int i2 = ft_atoi(n);

	printf("Org atoi: %d\n", atoi(str1));
	printf("My atoi: %d\n", ft_atoi(str1));
	//printf("Original atoi: %d\n", i1);
	//printf("My own atoi: %d\n", i2);
}*/
