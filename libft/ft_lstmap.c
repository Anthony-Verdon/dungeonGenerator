/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:13:37 by averdon           #+#    #+#             */
/*   Updated: 2022/10/04 09:23:02 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*start_list;

	if (!lst || !del || !f)
		return (NULL);
	new_list = ft_calloc(1, sizeof(t_list));
	if (!new_list)
		return (NULL);
	start_list = new_list;
	while (lst != NULL)
	{
		new_list->next = ft_calloc(1, sizeof(t_list));
		if (!new_list->next)
		{
			ft_lstclear(&start_list, del);
			return (NULL);
		}
		new_list->content = f(lst->content);
		new_list = new_list->next;
		lst = lst->next;
	}
	return (start_list);
}
