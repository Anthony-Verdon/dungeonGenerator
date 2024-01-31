/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:49:03 by averdon           #+#    #+#             */
/*   Updated: 2022/10/03 12:50:01 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void ft_lstwall_add_back(t_lstwall **lst, t_lstwall *new)
{
    t_lstwall *buffer;

    if (!lst)
        return;
    if (!(*lst))
    {
        *lst = new;
        new->next = *lst;
        return;
    }
    buffer = *lst;
    while (buffer->next != *lst)
        buffer = buffer->next;
    buffer->next = new;
    new->next = *lst;
}
