/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:51:02 by bbeltran          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/06 12:22:20 by bbeltran         ###   ########.fr       */
=======
/*   Updated: 2023/09/06 12:05:44 by jaimmart         ###   ########.fr       */
>>>>>>> ba37b6b65541737bf881e0bbab280528e60978f9
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function for the BUILTIN pwd, which, using getcwd(); gives you the current
 * working directory and prints it on the terminal(shell). */
void	ft_pwd(void)
{
<<<<<<< HEAD
	char	*dir;

	dir = getcwd(NULL, 0);
	printf("%s\n", dir);
	free(dir);
=======
//	char		*dir;
//	t_command	*curr;

//	curr = node;
//	dir = getcwd(NULL, 0);
	printf("%s\n", global.pwd);
//	free(dir);
>>>>>>> ba37b6b65541737bf881e0bbab280528e60978f9
}
