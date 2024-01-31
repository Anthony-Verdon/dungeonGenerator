/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_lstclear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:08:08 by averdon           #+#    #+#             */
/*   Updated: 2022/11/02 16:48:26 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_double_list.h"

void ft_double_lstclear(t_double_list **lst, void (*del)(void *))
{
    t_double_list *buffer;
    t_double_list *next;

    if (!lst || !del)
        return;
    buffer = *lst;
    while (buffer != NULL)
    {
        next = buffer->next;
        ft_double_lstdelone(buffer, del);
        buffer = next;
    }
    (*lst) = NULL;
}
