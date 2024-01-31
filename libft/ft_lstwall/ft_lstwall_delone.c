/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:53:21 by averdon           #+#    #+#             */
/*   Updated: 2022/10/03 12:50:50 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void ft_lstwall_delone(t_lstwall *lst, void (*del)(void *))
{
    if (!lst || !del)
        return;
    t_lstwall *preceding = lst;
    while (preceding->next != lst)
        preceding = preceding->next;

    preceding->next = lst->next;
    del(lst);
}
