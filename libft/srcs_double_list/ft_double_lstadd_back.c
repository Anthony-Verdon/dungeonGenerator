/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstadd_back.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:49:03 by averdon           #+#    #+#             */
/*   Updated: 2022/10/19 18:44:13 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_double_list.h"

void	ft_double_lstadd_back(t_double_list **lst, t_double_list *new)
{
	t_double_list	*buffer;

	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	buffer = *lst;
	while (buffer->next != NULL)
		buffer = buffer->next;
	buffer->next = new;
	new->prev = buffer;
}
