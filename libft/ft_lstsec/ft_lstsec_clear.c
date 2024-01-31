/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:08:08 by averdon           #+#    #+#             */
/*   Updated: 2022/11/04 04:47:33 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void ft_lstsec_clear(t_lstsector **lst, void (*del)(void *))
{
    t_lstsector *buffer;
    t_lstsector *next;

    if (!lst || !del)
        return;
    buffer = *lst;
    while (buffer != NULL)
    {
        next = buffer->next;
        ft_lstwall_clear(&buffer->walls, free);
        ft_lstsec_delone(buffer, del);
        buffer = next;
    }
    (*lst) = NULL;
}
