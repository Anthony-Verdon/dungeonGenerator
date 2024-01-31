/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:58:27 by averdon           #+#    #+#             */
/*   Updated: 2022/10/03 12:49:40 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void ft_lstwall_add_front(t_lstwall **lst, t_lstwall *new)
{
    if (!lst)
        return;

    if (!(*lst))
    {
        *lst = new;
        new->next = *lst;
        return;
    }
    t_lstwall *buffer = *lst;
    while (buffer->next != *lst)
        buffer = buffer->next;
    buffer->next = new;
    new->next = *lst;
}