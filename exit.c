/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:55:36 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/11 17:26:08 by jaimmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_code(char *str)
{
	if (str[0] == '-')
	{
		if (ft_strlen(str) < ft_strlen("-9223372036854775808"))
			return (1);
		else if (ft_strlen(str) > ft_strlen("-9223372036854775808"))
			return (0);
		else if (ft_strcmp(str, "-9223372036854775808") <= 0)
			return (1);
		else if (ft_strcmp(str, "-9223372036854775808") > 0)
			return (0);
	}
	if (ft_strlen(str) < ft_strlen("9223372036854775807"))
		return (1);
	else if (ft_strlen(str) > ft_strlen("9223372036854775807"))
		return (0);
	else if (ft_strcmp(str, "9223372036854775807") <= 0)
		return (1);
	else if (ft_strcmp(str, "9223372036854775807") > 0)
		return (0);
	return (0);
}

long long	ft_atoll(const char *str)
{
	int			i;
	long long	sig;
	long long	res;
	long long	nbr;

	i = 0;
	res = 0;
	sig = 1;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sig = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]) == 1)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	nbr = res * sig;
	return (nbr);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_exit_code(char **args)
{
	int	exit_code;
	int	size;

	size = 0;
	while (args[size])
		size++;
	exit_code = 0;
	if (size == 2)
	{
		if (is_numeric(args[1]) && check_exit_code(args[1]))
			exit_code = ft_atoi(args[1]);
		else
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			exit_code = 255;
		}
	}
	else if (size > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (-1);
	}
	return (exit_code);
}

void	ft_exit(t_shell *mini)
{
//	Not sure if it should print exit to stderror or just stdout.
	ft_putstr_fd("\nexit\n", 2);
//	printf("exit\n");
	if (!mini)
		exit(0);
	g_global.exit_stat = get_exit_code((*mini->cmds)->args);
	exit(g_global.exit_stat);
}
