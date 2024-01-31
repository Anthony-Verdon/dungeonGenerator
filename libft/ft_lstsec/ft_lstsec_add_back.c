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

void ft_lstsec_add_back(t_lstsector **lst, t_lstsector *new)
{
    t_lstsector *buffer;

    if (!lst)
        return;
    if (!(*lst))
    {
        *lst = new;
        return;
    }
    buffer = *lst;
    while (buffer->next != NULL)
        buffer = buffer->next;
    buffer->next = new;
}
