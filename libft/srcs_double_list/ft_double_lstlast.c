/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstlast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:47:19 by averdon           #+#    #+#             */
/*   Updated: 2022/10/19 18:45:09 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_double_list.h"

t_double_list	*ft_double_lstlast(t_double_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
