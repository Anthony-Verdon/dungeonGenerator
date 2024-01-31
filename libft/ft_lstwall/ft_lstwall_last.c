/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:47:19 by averdon           #+#    #+#             */
/*   Updated: 2022/10/03 12:50:32 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_lstwall *ft_lstwall_last(t_lstwall *lst)
{
    t_lstwall *head = lst;

    if (!lst)
        return NULL;
    do
    {
        lst = lst->next;
    } while (lst->next != head);
    return lst;
}
