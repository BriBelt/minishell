/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:51:02 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/06 14:50:44 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function for the BUILTIN pwd, which, using getcwd(); gives you the current
 * working directory and prints it on the terminal(shell). */
void	ft_pwd(void)
{
	printf("%s\n", global.pwd);
}
