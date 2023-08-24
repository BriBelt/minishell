/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:51:39 by bbeltran          #+#    #+#             */
/*   Updated: 2023/08/24 10:13:08 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_lexer **lst, char *rd) /*Should receive a SIGNAL?*/
{
	free(rd);
	free_t_lexer(lst);
	printf("exit\n");
	exit(0);
}
