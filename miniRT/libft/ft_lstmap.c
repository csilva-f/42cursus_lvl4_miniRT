/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:18:22 by csilva-f          #+#    #+#             */
/*   Updated: 2022/11/13 18:08:54 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_first;
	t_list	*new_next;

	if (!f || !del || !lst)
		return (0);
	new_first = (t_list *)malloc(sizeof(t_list));
	if (new_first == NULL)
		return (0);
	new_first->content = f(lst->content);
	new_first->next = NULL;
	lst = lst->next;
	while (lst)
	{
		new_next = (t_list *)malloc(sizeof(t_list));
		if (new_next == NULL)
		{
			ft_lstclear(&new_first, del);
			return (0);
		}
		new_next->content = f(lst->content);
		new_next->next = NULL;
		ft_lstadd_back(&new_first, new_next);
		lst = lst->next;
	}
	return (new_first);
}
