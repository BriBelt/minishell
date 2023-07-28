/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:51:02 by bbeltran          #+#    #+#             */
/*   Updated: 2023/07/28 18:39:29 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function for the BUILTIN pwd, which, using getcwd(); gives you the current
 * working directory and prints it on the terminal(shell). */
void	ft_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	printf("%s", dir);
	free(dir);
}

/* BUILTIN function for echo, just prints the given *userinput. */
void	ft_echo(char *userinput)
{
	printf("%s", userinput);

}
