/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:05:23 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 10:29:04 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}
/*#include <stdio.h>
int	main(void)
{
	int	n = 5;
	int	*A = (int *)ft_calloc(n, sizeof(int));

	for (int i = 0; i < n; i++)
		printf ("%d", A[i]);
	return (0);
}*/
