/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:36:40 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/05 11:40:55 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Frees a 2D array. */
void	free_2D_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/* Just a function that frees a linked list and its content. */
void	free_list(t_lexer **lst)
{
	t_lexer	*aux;

	while (*lst)
	{
		aux = *lst;
		*lst = (*lst)->next;
		free(aux);
	}
	free(lst);
}
