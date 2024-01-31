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

void ft_lstwall_clear(t_lstwall **lst, void (*del)(void *))
{
    t_lstwall *buffer;
    t_lstwall *next;

    if (!lst || !del)
        return;
    if (!(*lst))
        return;
    buffer = *lst;
    do
    {
        next = buffer->next;
        del(buffer);
        buffer = next;
    } while (buffer != *lst);
    *lst = NULL;
}
