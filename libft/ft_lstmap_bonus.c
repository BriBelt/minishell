/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:21:08 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/01 16:21:25 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;

	if (!lst)
		return (0);
	while (lst)
	{
		newlst = ft_lstnew(f(lst -> content));
		if (!newlst)
		{
			ft_lstclear(&newlst, del);
			return (0);
		}
		lst = lst -> next;
		newlst = newlst -> next;
	}
	return (newlst);
}
