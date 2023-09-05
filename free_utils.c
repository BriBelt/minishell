/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:36:40 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/05 16:32:57 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_mode(t_shell *mini, char *strerror, int errornum)
{
	mini->exit_status = errornum;
	printf("Errno: %i\n", mini->exit_status);
	ft_putstr_fd(strerror, 2);
}

/* Frees a 2D array. */
void	free_2d_array(char **array)
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
void	free_t_lexer(t_lexer **lst)
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

/* Another function but this one is to free a t_basic linked list and its
 * content. */
void	free_t_basic(t_basic **lst)
{
	t_basic	*aux;

	while (*lst)
	{
		aux = *lst;
		*lst = (*lst)->next;
		free(aux);
	}
	free(lst);
}
