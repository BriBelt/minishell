/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:11:06 by bbeltran          #+#    #+#             */
/*   Updated: 2023/09/21 15:10:27 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Searches for the specified environment var (*search), inside the whole
 * array of **envars. If *search is found, returns 1, else returns 0. */
int	search_in_envar(char *search, char **envars)
{
	int	i;

	i = 0;
	while (envars[i])
	{
		if (!ft_strncmp(envars[i], search, ft_strlen(search)))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_getenv(t_shell *mini, char *pathname)
{
	int	i;

	i = -1;
	if (mini->envp)
	{
		while (mini->envp[++i])
			if (!ft_strncmp(mini->envp[i], pathname, 5))
				return (mini->envp[i]);
	}
	return (NULL);
}

/* Returns the array (char **) of the sent *pathname. */
char	**get_paths(t_shell *mini, char *pathname)
{
	char	**paths;
	char	*whole;

	whole = ft_getenv(mini, pathname);
	if (!whole)
		return (NULL);
	paths = ft_split(whole, ':');
	return (paths);
}

/* Returns the expanded value of the environment variable given by 
 * getenv(); if it exist, otherwise returns NULL.
 * ONLY FOR lst->type = VAR */
char	*expand_envar(char *data, t_shell *mini)
{
	char	*expanded;
	char	*aux;
	char	*clean_data;
	int		len;

	len = ft_strlen(data) - 1;
	clean_data = ft_substr(data, 1, len);
	if (!ft_strncmp(clean_data, "?", 1))
	{
		aux = ft_itoa(g_global.exit_stat);
		expanded = ft_strjoin(aux, clean_data + 1);
		free(aux);
	}
	else if (mini->envp && search_in_envar(clean_data, mini->envp))
		expanded = ft_strdup(getenv(clean_data));
	else
		expanded = NULL;
	return (free(clean_data), expanded);
}

/* As its name says so, creates a copy of the **envp array and returns it.*/
char	**copy_envp(char **envp)
{
	char	**new;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new = ft_calloc(i + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new);
}
