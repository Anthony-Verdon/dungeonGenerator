/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstadd_front.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:58:27 by averdon           #+#    #+#             */
/*   Updated: 2022/10/20 16:04:46 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_double_list.h"

void	ft_double_lstadd_front(t_double_list **lst, t_double_list *new)
{
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	new->prev = NULL;
	(*lst)->prev = new;
	*lst = new;
}
